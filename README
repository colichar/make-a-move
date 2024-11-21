# Make A Move

## Connect to Arduino

Install command-line utility `avrdude` for managing the flash memory of AVR microcontrollers, including those used in Arduino boards.

For Arch-based Linux run:
```bash
sudo pacman -S avrdude
```

Then connect to your Arduino via USB and run
```bash
ls /dev/tty*
```

with the USB plugged in and out in order to identify which port is your Arduino connected to. Look for something like `/dev/ttyUSB0` or `/dev/ttyACM0`.


If there are any existing programs on the Arduino you wish to back up  use `avrdude` to download the program as a binary (HEX file) by running
```bash
avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:r:/home/your_user/backup.hex:i```
```
In this command:
- `-c arduino`: Specifies the programmer type (Arduino bootloader).
- `-p atmega328p`: Specifies the microcontroller model. Most Arduino Uno boards use atmega328p. You can check your Arduino to determine which model you have and search the documentation to determine the used microcontroller.
- `-P /dev/ttyUSB0`: Specifies the port your Arduino is connected to.
- `-U flash:r:/home/your_user/backup.hex:i`: Tells avrdude to read the flash memory (`flash:r`) and save it as `/home/your_user/backup.hex` in Intel HEX format (`:i`).


To reupload your backup to Arduino run
```bash
avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:/home/your_user/backup.hex:i
```
with thee difference that you usee `flash:w` to write to the flash memory of your Arduino.