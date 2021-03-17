#!/bin/bash
export PATH=$PATH:$HOME/esp/xtensa-esp32-elf/bin
export ESP32_SDK_DIR=$HOME/esp/esp-idf
make clean flash BOARD=esp32-wroom-32 ESP32_SDK_DIR=$HOME/esp/esp-idf RAIN=1 PORT=/dev/ttyUSB1