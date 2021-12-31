#!/bin/sh
echo "Building MKXP for PSVita..."

mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake -DBINDING=MRI18

make -j5 && {
	echo "Built mkxp."
} || {
	echo "Build Failed."
	exit
}

echo "vita-elf-create mkxp mkxp.velf"
vita-elf-create mkxp mkxp.velf
echo "vita-make-fself -c mkxp.velf ../vpk/eboot.bin"
vita-make-fself -c mkxp.velf ../vpk/eboot.bin


cd ../fixgpu/src

mkdir build
cd build
cmake ..
make && {
   	echo "Built gpu_fix."
} || {
	echo "Build gpu_fix failed."
	exit
}

cp gpu_fix.skprx ../../../vpk/module/gpu_fix.skprx

cd ../../../build

cd ../vpk

if [ -f "soundfont.sf2" ]; then
    echo "soundfont.sf2 already downloaded."
else 
    echo "Downloading soundfont.sf2..."
    wget https://www.dropbox.com/s/qxdvoxxcexsvn43/GMGSx.sf2?dl=1 -O soundfont.sf2
fi

chmod 777 -R .
 
echo "Build complete."

cd ..
