# Miller FPGA Remote Lab Guide 🚀

Willkommen im remote-gestützten FPGA-Labor für das **Miller-Projekt**!
Dieses Labor läuft 24/7 auf dem TrueNAS Server in einem isolierten Docker-Container mit direktem Hardware-Zugriff auf das **MillerV1 Cologne Chip GateMate A1** Board.

---

## 1. Zugangsdaten für das gesamte Team

Für das Team stehen zwei bequeme Wege bereit – beide nutzen dasselbe Team-Passwort:

> **Team-Passwort:** `MillerFPGA2026!`

---

### Option A: Web-IDE im Browser (code-server)
- **URL:** [https://miller-fpga.timoto.de](https://miller-fpga.timoto.de)
- **Passwort:** `MillerFPGA2026!`
- **Features:** Vollständiges VS Code direkt im Browser inklusive integriertem Terminal, Git, Syntax-Highlighting und Editor. Keine Installation auf dem eigenen Laptop erforderlich!

---

### Option B: Direkter SSH-Zugang (Terminal / VS Code Remote-SSH)
- **Host:** `10.50.50.1` (oder eure externe Domain/IP, falls Port 22022 im Router weitergeleitet ist)
- **Port:** `22022`
- **Benutzer:** `miller`
- **Passwort:** `MillerFPGA2026!`
- *(Optional: Wer möchte, kann natürlich weiterhin seinen SSH-Public-Key in `~/.ssh/authorized_keys` hinterlegen).*

#### Direktverbindung im Terminal:
```bash
ssh -p 22022 miller@10.50.50.1
```
*(Bei Abfrage einfach das Passwort `MillerFPGA2026!` eingeben).*

#### Konfiguration für VS Code (Remote - SSH Erweiterung):
In eurer lokalen `~/.ssh/config` Datei hinzufügen:
```ssh-config
Host miller-fpga
    HostName 10.50.50.1
    Port 22022
    User miller
```
Anschließend in VS Code: `Strg+Shift+P` -> `Remote-SSH: Connect to Host...` -> `miller-fpga` auswählen und das Passwort eingeben.

---

## 2. FPGA Flashen mit Hardware-Schutz (`flash-fpga`)

Auf dem System ist das Hilfsskript `flash-fpga` im systemweiten Pfad hinterlegt. Es nutzt intern `flock`, sodass gleichzeitige Flash-Versuche von mehreren Teammitgliedern sicher abgefangen werden.

### SRAM Flashen (flüchtig, für schnelle Tests)
```bash
flash-fpga /workspace/MillerProject/software/blinking-led-bit-source/top_00.cfg.bit
```

### SPI-Flash programmieren (dauerhaft nach Power-Cycle)
```bash
flash-fpga -f /workspace/MillerProject/software/blinking-led-bit-source/top_00.cfg.bit
```

### FPGA JTAG Chain erkennen
```bash
openFPGALoader -c dirtyJtag --detect
```
*(Gibt `idcode 0x20000001 (GateMate Series GM1Ax)` aus).*

---

## 3. Serielle Kommunikation / UART (Konsole)

Der RP2040 stellt neben JTAG auch zwei CDC-ACM serielle Schnittstellen bereit:
- `/dev/ttyACM0`: Verbunden mit FPGA Pin `T9` (FPGA RX) und Pin `R9` (FPGA TX).
- `/dev/ttyACM1`: Zweite Hilfsschnittstelle.

### Konsole öffnen:
```bash
read-uart
```
oder
```bash
tio /dev/ttyACM0 -b 115200
```
oder
```bash
picocom -b 115200 /dev/ttyACM0
```
*(Beenden mit `Ctrl+C` bei read-uart, `Ctrl+t q` bei tio bzw. `Ctrl+a Ctrl+x` bei picocom).*

---

## 4. RIGSoC bauen und flashen (RISC-V Ibex SoC)

Das RISC-V SoC aus dem Repository `software/RIGSoC` kann komplett im Container gebaut werden:

```bash
cd /workspace/MillerProject/software/RIGSoC

# 1. RISC-V Firmware kompilieren (erzeugt rtl/firmware_mem_init.svh):
make firmware

# 2. GateMate Synthese (Yosys) & Place & Route (nextpnr-himbaechel) durchführen:
make soc

# 3. Bitstream Impl/impl.bit auf das FPGA laden:
make flash

# 4. Serielle Ausgabe ansehen:
read-uart
```
Nach dem Flashen gibt der Ibex-Prozessor über UART mit 115200 Baud aus:
```text
STARTE IBEX DU KEK
ES WIRD ERNST
ICH HASSE IBEX
...
```
