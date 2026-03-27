This design is a TOP SECRET Miller Project.

Arbeits Aufteilung:
-  Ibex-Port (Handl)
- PCB, Schematic + Layout (Gewiese)
- USB PHY, ISO7816 Interface / Card VCC-Switching, Power Domains (Belm)
- Pin Assignment, Constraints, Bringup-Testinfrastruktur - Bindeglied zwischen Hardware und HDL (Drüen)

ToDo Redesign:
- USB-Phy reindesignen (voraussichtlich TUSB1106)
- zusätzlicher USB-Connector für Device-Mode-USB und Routing zum
TUSB1106. Also Referenzimplementierung kann hier das Sonata-Board
(lowRISC) dienen
- ISO7816-Interface: Das sind nur FPGA-Pins die an PIN-Header geroutet
werden. Ggf. noch Level-Shifter
- Alles raus was wir nicht brauchen
- Bissl hübscher machen

References
- [colone chips gatemate](https://colognechip.com/programmable-logic/gatemate/)
- [reference board GateMateA1-EVB](https://github.com/OLIMEX/GateMateA1-EVB)
