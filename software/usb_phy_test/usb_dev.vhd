-- usb_dev.vhd: Transaktionslogik des USB-PHY-Testmoduls.
-- Nach einem IN-Token an die eigene Adresse antwortet das Modul nach
-- Ablauf der Turnaround-Zeit mit einem 8-Byte-HID-Tastatur-Report
-- (Taste 'a' per Board-Taster) oder mit NAK; ein Bus-Reset (SE0 laenger
-- als 2,5 us) setzt die Device-Adresse auf 0 zurueck.
library ieee;
use ieee.std_logic_1164.all;

entity usb_dev is
    port (
        clk        : in  std_logic;
        rst        : in  std_logic;
        bit_en     : in  std_logic;
        se0        : in  std_logic;            -- vom usb_rx
        tx_done    : in  std_logic;            -- von usb_tx
        token_in   : in  std_logic;
        token_addr : in  natural range 0 to 127;
        token_endp : in  natural range 0 to 15;
        btn        : in  std_logic;            -- Taster (2FF-synchronisiert)
        start      : out std_logic;
        pid        : out std_logic_vector(7 downto 0);
        payload    : out std_logic_vector(63 downto 0);
        plen       : out natural range 0 to 8;
        send_crc   : out std_logic
    );
end entity;

architecture rtl of usb_dev is
    -- HID-Report: Modifier, reserviert, 6 Keycodes (0x04 = Taste 'a')
    constant KEY_A : std_logic_vector(63 downto 0) := x"0000000000040000";
    signal dev_addr : natural range 0 to 127 := 0;
    signal pend     : std_logic := '0';
    signal gap      : natural range 0 to 4 := 4;
    signal se0_cnt  : natural range 0 to 31 := 0;
begin

    process (clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                dev_addr <= 0;
                pend     <= '0';
                gap      <= 4;
                se0_cnt  <= 0;
                start    <= '0';
            elsif bit_en = '1' then
                start <= '0';
                -- Bus-Reset: SE0 laenger als 2,5 us = 30 Bitzeiten
                if se0 = '1' then
                    if se0_cnt = 30 then
                        dev_addr <= 0;
                        pend     <= '0';
                    else
                        se0_cnt <= se0_cnt + 1;
                    end if;
                else
                    se0_cnt <= 0;
                end if;

                -- IN-Token am Tastatur-Endpoint (EP1): Turnaround abwarten
                if token_in = '1' and token_addr = dev_addr
                   and token_endp = 1 then
                    gap <= 0;
                elsif gap /= 4 then
                    if gap = 3 then
                        start <= '1';           -- Antwortpaket senden
                        gap   <= 4;
                    else
                        gap <= gap + 1;
                    end if;
                end if;

                -- Tastendruck vormerken, nach gesendeter Antwort freigeben
                if btn = '1' then
                    pend <= '1';
                elsif tx_done = '1' then
                    pend <= '0';
                end if;
            end if;
        end if;
    end process;

    -- ausstehender Tastendruck: DATA1 + Report (mit CRC16), sonst NAK
    pid      <= x"4B" when pend = '1' else x"5A";
    payload  <= KEY_A when pend = '1' else x"0000000000000000";
    plen     <= 8 when pend = '1' else 0;
    send_crc <= pend;

end architecture;