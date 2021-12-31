#!/bin/sh

echo "removing build folder"
rm -rf build
echo "removing fixgpu build folder"
rm -rf fixgpu/src/build

echo "removing eboot.bin"
rm -rf vpk/eboot.bin
echo "removing soundfont.sf2"
rm -rf vpk/soundfont.sf2
echo "removing gpu_fix.skprx"
rm -rf vpk/module/gpu_fix.skprx

echo "Cleaned."
