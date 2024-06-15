Firmware designed for the pico of the IDC project

# Building:
  
1. create your build directory `mkdir build`
2. run `cmake -DPICO_BOARD=pico_w  -DWIFI_SSID='SSID' -DWIFI_PASSWORD='PASS' ..`
> You must set your Wi-Fi SSID in 'SSID' and your Wi-Fi password in 'PASS'
3. run `make` inside your build directory

# Flashing with picotool:

1. build [picotool](https://github.com/raspberrypi/picotool)
2. run `picotool load -f PicoMeasure.uf2` 

# Flahsing without picotool
  
move PicoMeasure.uf2 to the pico in BOOTSEL mode

# See USB output
```bash
sudo minicom -b 115200 -o -D /dev/ttyACM0
```
