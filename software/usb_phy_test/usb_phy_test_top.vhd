-- usb_phy_test_top.vhd: Top-Level fuer den Bringup des TUSB1106.
-- Die PHY-Ports entsprechen 1:1 den Constraints in usb_phy_test.ccf
-- (Peri-BUS des Olimex-Boards). Der 48-MHz-Takt muss extern eingespeist
-- werden, da der onboard-Oszillator fehlt (siehe Report, Clock-Problem).
library ieee;
use ieee.std_logic_1164.all;

entity usb_phy_test_top is
    port (
        clk48     : in  std_logic;     -- 48 MHz, extern einzuspeisen
        rst       : in  std_logic;     -- z. B. CPU-Reset-Button
        btn       : in  std_logic;     -- Taster fuer den HID-Report
        usb_rcv   : in  std_logic;     -- RCV
        usb_vp    : in  std_logic;     -- VP
        usb_vm    : in  std_logic;     -- VM
        usb_vpo   : out std_logic;     -- VPO
        usb_vmo   : out std_logic;     -- VMO
        usb_oe    : out std_logic;     -- OE
        usb_speed : out std_logic;     -- SPEED
        usb_susp  : out std_logic      -- SUSPND
    );
end entity;

architecture rtl of usb_phy_test_top is
    signal div_cnt  : natural range 0 to 3 := 0;
    signal bit_en   : std_logic;
    signal tx_start : std_logic;
    signal tx_pid   : std_logic_vector(7 downto 0);
    signal tx_data  : std_logic_vector(63 downto 0);
    signal tx_len   : natural range 0 to 8;
    signal tx_crc   : std_logic;
    signal tx_done  : std_logic;
    signal se0      : std_logic;
    signal tok_in   : std_logic;
    signal tok_addr : natural range 0 to 127;
    signal tok_endp : natural range 0 to 15;
begin

    usb_speed <= '1';                       -- Full-Speed (Datenblatt: SPEED = H)
    usb_susp  <= '0';                       -- PHY aktiv (SUSPND = L)

    -- Bittakt-Teiler: 48 MHz / 4 = 12 Mbit/s (Full-Speed)
    process (clk48)
    begin
        if rising_edge(clk48) then
            if div_cnt = 3 then
                div_cnt <= 0;
                bit_en  <= '1';
            else
                div_cnt <= div_cnt + 1;
                bit_en  <= '0';
            end if;
        end if;
    end process;

    u_tx : entity work.usb_tx
        port map (
            clk => clk48, rst => rst, bit_en => bit_en,
            start => tx_start, pid => tx_pid, payload => tx_data,
            plen => tx_len, send_crc => tx_crc, done => tx_done,
            phy_oe => usb_oe, phy_vpo => usb_vpo, phy_vmo => usb_vmo);

    u_rx : entity work.usb_rx
        port map (
            clk => clk48, rst => rst, bit_en => bit_en,
            phy_rcv => usb_rcv, phy_vp => usb_vp, phy_vm => usb_vm,
            se0 => se0, token_in => tok_in,
            token_addr => tok_addr, token_endp => tok_endp);

    u_dev : entity work.usb_dev
        port map (
            clk => clk48, rst => rst, bit_en => bit_en,
            se0 => se0, tx_done => tx_done,
            token_in => tok_in, token_addr => tok_addr, token_endp => tok_endp,
            btn => btn,
            start => tx_start, pid => tx_pid, payload => tx_data,
            plen => tx_len, send_crc => tx_crc);

end architecture;