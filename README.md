Firmware designed for the pico int the IDC project

to build:
  -create build directory
  -run cmake ..
  -run make

to flash:
  -run picotool load -f PicoMeasure.uf2 (you can clone and build picotool at https://github.com/raspberrypi/picotool)

  or
  
  -move PicoMeasure.uf2 to the pico in BOOTSEL mode
