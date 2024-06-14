Firmware designed for the pico int the IDC project

# Building:
  
1. create build directory
2. run `cmake ..`
3. run `make`

# Flashing wiht picotool:

1. build [picotool](https://github.com/raspberrypi/picotool))
2. run `picotool load -f PicoMeasure.uf2` 

# Flahsing without picotool
  
move PicoMeasure.uf2 to the pico in BOOTSEL mode
