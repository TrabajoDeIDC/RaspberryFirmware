Firmware designed for the pico int the IDC project

#to build:
  
1. create build directory
2. run `cmake ..`
3. run `make`

#flashing wiht picotool:

1. build [picotool](https://github.com/raspberrypi/picotool))
2. run `picotool load -f PicoMeasure.uf2` 

#flahsing without picotool
  
move PicoMeasure.uf2 to the pico in BOOTSEL mode
