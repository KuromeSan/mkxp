#!/bin/sh
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake
make -j30

vita-elf-create mkxp mkxp.velf
vita-make-fself -c mkxp.velf mkxp.self
mv mkxp.self /home/silica/eboot.bin
chmod 777 /home/silica/eboot.bin
