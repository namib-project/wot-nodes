#!/bin/bash
export PATH="$PATH:$HOME/esp/xtensa-esp32-elf/bin"
export ESP32_SDK_DIR=$HOME/esp/esp-idf
make $1 BOARD=esp32-wroom-32 $2
