-- usb_rx.vhd: Empfangsrichtung des USB-PHY-Testmoduls (Full-Speed, 12 Mbit/s)
-- RCV liefert den NRZI-Strom, VP/VM die Single-Ended-Pegel zur SE0-Erkennung
-- (Datenblatt Tab. 5). Die Bitphase wird am SYNC-Muster eingenommen;
-- token_in wird nur fuer gueltige IN-Token erzeugt (PID-Komplement prueft
-- die Synchronisation, CRC5 wird im Testmodul nicht geprueft).
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity usb_rx is
    port (
        clk        : in  std_logic;
        rst        : in  std_logic;
        bit_en     : in  std_logic;
        phy_rcv    : in  std_logic;          -- RCV: NRZI-Bitstrom (Idle = J)
        phy_vp     : in  std_logic;          -- VP: Single-ended D+
        phy_vm     : in  std_logic;          -- VM: Single-ended D-
        se0        : out std_logic;
        token_in   : out std_logic;          -- gueltiger IN-Token empfangen
        token_addr : out natural range 0 to 127;
        token_endp : out natural range 0 to 15
    );
end entity;

architecture rtl of usb_rx is
    type state_t is (HUNT, PID, TOKEN);
    signal state : state_t := HUNT;
    signal prev  : std_logic := '1';
    signal sreg  : std_logic_vector(15 downto 0) := (others => '0');
    signal pid_l : std_logic_vector(7 downto 0);
    signal cnt   : natural range 0 to 15 := 0;
    signal ones  : natural range 0 to 6 := 0;
begin

    se0 <= '1' when phy_vp = '0' and phy_vm = '0' else '0';

    process (clk)
        variable dbit : std_logic;             -- decodiertes Datenbit
        variable v    : std_logic_vector(15 downto 0);
    begin
        if rising_edge(clk) then
            if rst = '1' then
                state <= HUNT;
                prev  <= '1';
                pid_l <= x"00";
            elsif bit_en = '1' then
                token_in <= '0';
                -- NRZI-Decodierung: Pegelwechsel = '0', kein Wechsel = '1'
                if phy_rcv /= prev then
                    dbit := '0';
                else
                    dbit := '1';
                end if;
                prev := phy_rcv;

                case state is

                    when HUNT =>               -- SYNC-Datenbits 0x80, LSB zuerst
                        v    := dbit & sreg(15 downto 1);
                        sreg <= v;
                        if v(15 downto 8) = x"80" then
                            cnt   <= 0;
                            ones  <= 1;        -- Sync-Eins zaehlt mit (Spec 7.1.9)
                            state <= PID;
                        end if;

                    when PID =>
                        if ones = 6 then       -- Stuff-Bit verwerfen
                            ones <= 0;
                        else
                            v    := dbit & sreg(15 downto 1);
                            sreg <= v;
                            ones <= ones + 1 when dbit = '1' else 0;
                            if cnt = 7 then
                                if v(11 downto 8) = not v(15 downto 12) then
                                    pid_l <= v(15 downto 8);  -- PID-Byte merken
                                    cnt   <= 0;   -- PID-Komplement ok
                                    state <= TOKEN;
                                else
                                    state <= HUNT;
                                end if;
                            else
                                cnt <= cnt + 1;
                            end if;
                        end if;

                    when TOKEN =>
                        if ones = 6 then
                            ones <= 0;
                        else
                            v    := dbit & sreg(15 downto 1);
                            sreg <= v;
                            ones <= ones + 1 when dbit = '1' else 0;
                            if cnt = 15 then     -- 7 Adresse + 4 EP + 5 CRC5
                                if pid_l = x"69" then          -- IN-Token
                                    token_addr <= to_integer(unsigned(v(6 downto 0)));
                                    token_endp <= to_integer(unsigned(v(10 downto 7)));
                                    token_in   <= '1';
                                end if;        -- CRC5 im Testmodul ungeprueft
                                cnt   <= 0;
                                state <= HUNT;
                            else
                                cnt <= cnt + 1;
                            end if;
                        end if;
                end case;
            end if;
        end if;
    end process;

end architecture;