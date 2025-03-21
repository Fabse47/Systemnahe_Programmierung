# Arm Cortex-M0 Base Project

Dies ist unser Hangman-Projekt für Systemnahe Programmierung. Im Folgenden wird das Spiel und der Aufbau der Dokumente erklärt. 
Bei Rückfragen wenden Sie sich gerne an: johler.tim-it23@it.dhbw-ravensburg.de

## Projektüberblick und Spielweise
Das Programm startet mit einem Menü, in dem man entweder direkt das Spiel
beginnen (`s`) oder ein neues Wort hinzufügen (`a`) kann. Anschließend läuft
das eigentliche Hangman-Spiel:
- Ein zufälliges (oder vom Benutzer hinzugefügtes) Wort wird aus einer Liste
  ausgewählt.
- Der Spieler gibt Buchstaben über die serielle UART-Schnittstelle ein.
- Für jeden falschen Buchstaben wird die Fehleranzahl erhöht und das Männchen
  weitergezeichnet.
- Sobald das Wort vollständig erraten ist, oder die maximale Fehlerzahl erreicht
  wurde, wird das Spiel beendet und eine kurze Statistik ausgegeben.

## Aufbau der Files
- **main.c/h**: Enthält die `hangman()`-Funktion und zentrale Initialisierungen.
- **game_logic.c/h**: Kernlogik des Hangman-Spiels (Erfassung von Fehlern, Wortprüfung, Spielende).
- **input.c/h**: Liest Zeichen vom Spieler (UART) ein; mit/ohne Timeout.
- **output.c/h**: Gibt Spielzustände (Hangman-Grafik), Gewinner-/Verlierermeldungen und Statistiken aus.
- **wordlist.c/h**: Speicherung und Verwaltung einer Wortliste (vordefiniert + benutzerdefiniert). Zufallsauswahl eines Rateworts.
- **hangman_timer.c/h**: Verwaltet die beiden genutzten Timer (Timeout und Gesamtspielzeit).
- **devices**: Enthält z. B. `uart.c/h`, `timer.c/h`, `random.c/h` zur direkten Ansteuerung bzw. Simulation der Hardware-Funktionen.

## Arm Documentation
- [Cortex M0 Startseite](https://developer.arm.com/Processors/Cortex-M0)
   - [Armv6-M Architecture Reference Manual](https://developer.arm.com/documentation/ddi0419/latest/)
   - [Arm Cortex-M0 Processor Datasheet](https://developer.arm.com/documentation/102834/0100/?lang=en)
   - [Cortex-M0 Devices Generic User Guide](https://developer.arm.com/documentation/dui0497/a/?lang=en)
   - [Cortex-M0 Technical Reference Manual r0p0](https://developer.arm.com/documentation/ddi0432/c/?lang=en)
- [Arm Application Binary Interface](https://github.com/ARM-software/abi-aa)
- [GNU Assembler Documentation](https://sourceware.org/binutils/docs-2.40/as/index.html)
- [GNU Linker Documentation](https://sourceware.org/binutils/docs-2.40/ld/index.html)

## Simuliertes Board Info
- [Nordic nRF boards (microbit)](https://www.qemu.org/docs/master/system/arm/nrf.html)
- [Nordic nRF51822](https://www.nordicsemi.com/products/nrf51822)
- [nRF51822 Product Specification v3.4](https://infocenter.nordicsemi.com/pdf/nRF51822_PS_v3.4.pdf)

## Prerequisites
- Arm Cross Compiler Paket: _gcc-arm-none-eabi_
- QEMU Arm Paket: _qemu-system-arm_
- GDB (Multi-Arch) Paket: _gdb-multiarch_
- CMake

Hinweis:
Unteranderem bei SUSE, Arch, NixOs scheint der standard GDB ein GDB-Multiarch zu sein.

### Windows
Installation von CMake über Download des Installers (https://cmake.org/download/)
oder Paketmanager winget install CMake.CMake.

Installation der ARM GCC Toolchain [Website](https://gnutoolchains.com/arm-eabi/)
Nach z.B. C:\Toolchains\
**WICHTIG:** zu PATH hinzufügen (lassen)

### Linux
Über Paketmanager Installieren:

**Ubuntu/ Debian**:
sudo apt install gcc-arm-none-eabi cmake

**Arch**:
yay -S gcc-arm-none-eabi-bin
sudo pacman -S cmake

### macOS
brew install gcc-arm-embedded

## Building
Auschecken des Quellcodes:
git clone https://github.com/infohoschie/arm-cortex-m0-cmake-start.git

Erstellen des Build Mittels CMake Presets:
cmake --preset arm-cortex-m0-unix

oder
cmake --preset arm-cortex-m0-mingw

Bauen Mittels CMake Presets:
cmake --build --preset arm-cortex-m0-unix

oder
cmake --build --preset arm-cortex-m0-mingw

## Generiertes Output analysieren (optional)
- ELF-Sections anzeige:
  arm-none-eabi-objdump -x build-cortex-m0/testApp.elf
- ELF-File disassemblieren (mit Quellcode-Verknüpfung):
  arm-none-eabi-objdump -d build-cortex-m0/testApp.elf
  arm-none-eabi-objdump -d -S build-cortex-m0/testApp.elf

## QEMU Emulator starten und mit GDB verbinden
QEMU und GDB müssen in unterschiedlichen Konsolen (Shells) gestartet werden.
### - QEMU Emulation Starten:
qemu-system-arm -M microbit -device loader,file=build-cortex-m0/testApp.elf -nographic -S -s -serial mon:stdio
### - GDB zu QEMU verbinden:
gdb-multiarch build-cortex-m0/testApp.elf -ex "target extended-remote localhost:1234" -ex "load"
#### MacOS on Apple Silicon:
arm-none-eabi-gdb build-cortex-m0/testApp.elf -ex "target extended-remote localhost:1234" -ex "load"

Um QEMU zu beenden die Tastenkombination <strg> + a und anschließend x nutzen.

## IDEs
### Jetbrains CLion
Das Projekt kann direkt in der IDE geöffnet (ausgecheckt) werden.
Die CMake Presets werden direkt als build-target angeboten

Der integrierte Debugger kann direkt genutzt werden.
Unter der Run-Configuration kann der QEMU Aufruf als "Native Application" hinzugefügt werden.
Unter debug Configuration kann eine "Remote Debug" Konfiguration angelegt werden, bei der unter "target remote args" die Verbindungsdetails angeben und als *symbol file* die *testApp.elf* referenziert werden kann.

### Visual Studio Code

VS-Code kann über einen Workspace konfiguriert werden, welcher über die Datei "linux.code-workspace" bzw "windows.code-workspace" geöffnet werden kann.

Folgende Extensions werden benötigt:
- jkearins.action-buttons-ext
- webfreak.debug
- ms-vscode.cmake-tools
- dan-c-underwood.arm

Diese sind ebenfalls als empfohlene Extensions im Workspace definiert.

Nach Installation erkennt VScode die CMake Presets und bietet diese gleich an.
Ebenfalls werden in der Statusleiste Knöpfe um das CMake Projekt zu *konfigurieren* und zu *bauen*,
die qemu-Instanz (neu) zu *starten* und gdb zu starten hinzugefügt.

Nach Änderungen am Code muss das CMake Projekt neugebaut und die qemu-Instanz neugestartet werden.
