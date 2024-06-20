video: https://drive.google.com/file/d/1o7DREmWxKpv8F1eTCW6poKYjO5VHU0gB/view?usp=sharing

Firmware designed for the pico of the IDC project

<img width="601" alt="pinout" src="https://github.com/TrabajoDeIDC/RaspberryFirmware/assets/98914819/b32fcf81-e67c-49e7-bd70-5c9649401aa7">


# Building:
  
1. create your build directory `mkdir build`
2. run `cmake -DPICO_BOARD=pico_w  -DWIFI_SSID='SSID' -DWIFI_PASSWORD='PASS' ..`
> You must set your Wi-Fi SSID in 'SSID' and your Wi-Fi password in 'PASS'
3. run `make` inside your build directory

# Flashing 

## With picotool:

1. build [picotool](https://github.com/raspberrypi/picotool)
2. run `picotool load -f PicoMeasure.uf2` 

## Without picotool
  
move PicoMeasure.uf2 to the pico in BOOTSEL mode

# See USB output
```bash
sudo minicom -b 115200 -o -D /dev/ttyACM0
```

# Circuits

## DHT22

<img width="601" alt="Captura de pantalla 2024-06-14 a las 18 03 58" src="https://github.com/TrabajoDeIDC/RaspberryFirmware/assets/98914819/51c17bdb-49fb-4bc8-8990-3191de1c298a">

## KY-038

<img width="601" alt="Captura de pantalla 2024-06-15 a las 11 09 31" src="https://github.com/TrabajoDeIDC/RaspberryFirmware/assets/98914819/e1e413ed-b686-47af-9984-750c077e802e">

## MQ-135

<img width="601" alt="Captura de pantalla 2024-06-15 a las 11 09 51" src="https://github.com/TrabajoDeIDC/RaspberryFirmware/assets/98914819/e1b672cc-c873-4e10-99b9-c259d8549810">

# TROUBLESHOOTING

Both KY-038 and MQ-135 sensors have a high voltage of 5V, meanwhile the pico only has 3.3V. For the proper functioning of the circuit, you'll have to use either a level shifter or a  voltage divider. The pico does have a 5V output pin, so you can use that as a source.
