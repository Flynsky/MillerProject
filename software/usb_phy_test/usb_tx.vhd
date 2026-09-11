-- usb_tx.vhd: Sendeteil des USB-PHY-Testmoduls (Full-Speed, 12 Mbit/s)
-- Ansteuerung des TUSB1106 gemaess Datenblatt Tab. 4: OE = '0' aktiviert
-- den Treiber, VPO = D+, VMO = D-; VPO = VMO = '0' erzeugt SE0 (EOP)
library ieee;
use ieee.std_logic_1164.all;

entity usb_tx is
    port (
        clk      : in  std_logic;                    -- 48-MHz-Systemtakt
        rst      : in  std_logic;
        bit_en   : in  std_logic;                    -- Bittakt-Enable (12 MHz)
        start    : in  std_logic;                    -- Uebertragung starten
        pid      : in  std_logic_vector(7 downto 0); -- z. B. DATA1 = 0x4B
        payload  : in  std_logic_vector(63 downto 0);
        plen     : in  natural range 0 to 8;         -- Nutzlaenge in Byte
        send_crc : in  std_logic;                    -- '1' = CRC16 anhaengen
        done     : out std_logic;
        phy_oe   : out std_logic;
        phy_vpo  : out std_logic;                    -- VPO = D+
        phy_vmo  : out std_logic                     -- VMO = D-
    );
end entity;

architecture rtl of usb_tx is
    type state_t is (IDLE, SYNC, PKT, SE0_A, SE0_B, GAP);
    signal state : state_t := IDLE;
    signal nbits : natural range 8 to 88;
    signal idx   : natural range 0 to 87 := 0;
    signal ones  : natural range 0 to 6 := 0;      -- Stuffing-Zaehler
    signal stuff : std_logic := '0';               -- naechstes Bit: Stuff-Bit
    signal nrzi  : std_logic := '1';               -- Buspegel (1 = J, 0 = K)
    signal crc   : std_logic_vector(15 downto 0);

    -- CRC16 der USB-Spezifikation: G(x) = x^16 + x^15 + x^2 + 1,
    -- Initialwert FFFF, LSB zuerst, Pruefbits werden invertiert gesendet
    function crc16_next(c : std_logic_vector(15 downto 0);
                        d : std_logic) return std_logic_vector is
        variable fb : std_logic;
        variable n  : std_logic_vector(15 downto 0);
    begin
        fb    := c(0) xor d;
        n(0)  := c(1) xor fb;
        n(1)  := c(2);
        n(2)  := c(3);
        n(3)  := c(4);
        n(4)  := c(5);
        n(5)  := c(6);
        n(6)  := c(7);
        n(7)  := c(8);
        n(8)  := c(9);
        n(9)  := c(10);
        n(10) := c(11);
        n(11) := c(12);
        n(12) := c(13);
        n(13) := c(14) xor fb;
        n(14) := c(15);
        n(15) := fb;
        return n;
    end function;
begin

    done <= '1' when state = GAP else '0';

    -- Treiberansteuerung: Idle = J (VPO = '1', VMO = '0'), SE0 im EOP
    phy_oe  <= '0' when state /= IDLE else '1';
    phy_vpo <= '0' when state = SE0_A or state = SE0_B else nrzi;
    phy_vmo <= '0' when state = SE0_A or state = SE0_B else not nrzi;

    process (clk)
        variable bitv : std_logic;
    begin
        if rising_edge(clk) then
            if rst = '1' then
                state <= IDLE;
                nrzi  <= '1';
                idx   <= 0;
                ones  <= 0;
                stuff <= '0';
                crc   <= (others => '0');
            elsif bit_en = '1' then
                case state is

                    when IDLE =>
                        if start = '1' then
                            nbits <= 8 + plen * 8 + 16 when send_crc = '1'
                                     else 8 + plen * 8;
                            idx   <= 0;
                            ones  <= 0;
                            stuff <= '0';
                            crc   <= x"FFFF";
                            state <= SYNC;
                        end if;

                    when SYNC =>                  -- SOP: 00000001 -> KJKJKJKK
                        if idx < 7 then
                            bitv := '0';
                        else
                            bitv := '1';
                        end if;
                        if bitv = '0' then
                            nrzi <= not nrzi;
                        end if;
                        if idx = 7 then
                            idx   <= 0;
                            ones  <= 1;           -- Sync-Eins zaehlt mit (Spec 7.1.9)
                            stuff <= '0';
                            state <= PKT;
                        else
                            idx <= idx + 1;
                        end if;

                    when PKT =>                   -- PID, Nutzdaten, CRC16
                        if stuff = '1' then       -- erzwungenes Stuff-Bit '0'
                            bitv  := '0';
                            stuff <= '0';
                            ones  <= 0;
                            if idx = nbits - 1 then   -- Stuff-Bit war letztes Bit
                                state <= SE0_A;
                            end if;
                        else
                            if idx < 8 then
                                bitv := pid(idx);
                            elsif idx < 8 + plen * 8 then
                                bitv := payload(idx - 8);
                                crc  <= crc16_next(crc, bitv);
                            else
                                bitv := not crc(idx - 8 - plen * 8);
                            end if;
                            if bitv = '1' then
                                if ones = 5 then
                                    stuff <= '1';  -- 6 Einsen -> Stuff-Bit
                                    ones  <= 6;
                                else
                                    ones <= ones + 1;
                                end if;
                            else
                                ones <= 0;
                            end if;
                            if idx = nbits - 1 then
                                if not (bitv = '1' and ones = 5) then
                                    state <= SE0_A;
                                end if;           -- sonst folgt erst das Stuff-Bit
                            else
                                idx <= idx + 1;
                            end if;
                        end if;
                        if bitv = '0' then
                            nrzi <= not nrzi;
                        end if;

                    when SE0_A =>                 -- EOP: 2 Bitzeiten SE0
                        state <= SE0_B;

                    when SE0_B =>
                        nrzi  <= '1';             -- Rueckkehr nach J (Idle)
                        state <= GAP;

                    when GAP =>                   -- 1 Bitzeit J, dann frei
                        state <= IDLE;
                end case;
            end if;
        end if;
    end process;

end architecture;