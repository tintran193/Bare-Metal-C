# BARE-METAL-C 
## Toolchains
| Tool | version|
|--|--|
|Git|git version 2.43.0|
|Make|GNU Make 4.3 Built for x86_64-pc-linux-gnu License GPLv3+|
|Cmake|cmake version 3.28.3|
|OpenOCD|Open On-Chip Debugger 0.11.0+dev-00837-gde99836cf-dirty (2022-09-09-03:18) Licensed under GNU GPL v2|
|ARM GCC|arm-none-eabi-gcc (15:13.2.rel1-2) 13.2.1 20231009|

## Install USB to WSL2
### Powershell (Run as Administrator)
1. `usbipd list`
2. `winget install dorssel.usbipd-win`
3. `usbipd list`

Connected:

|BUSID|  VID:PID|    DEVICE|                                                        STATE|
|--|--|--|--|
|1-3|    0483:374b|  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  |Not shared|
|1-4|    260d:1099|  USB Input Device                                              |Not shared|
|1-6|    04f2:b7b4|  Integrated Camera, Integrated IR Camera, Camera DFU Device    |Not shared|
|1-9|    27c6:550a|  Goodix fingerprint                                            |Not shared|
|1-10|   0bda:5852|  Realtek Bluetooth Adapter                                     |Not shared|

4. `usbipd bind --busid 1-3`

Connected:

|BUSID|  VID:PID|    DEVICE|                                                        STATE|
|--|--|--|--|
|1-3|    0483:374b|  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  |Shared|
|1-4|    260d:1099|  USB Input Device                                              |Not shared|
|1-6|    04f2:b7b4|  Integrated Camera, Integrated IR Camera, Camera DFU Device    |Not shared|
|1-9|    27c6:550a|  Goodix fingerprint                                            |Not shared|
|1-10|   0bda:5852|  Realtek Bluetooth Adapter                                     |Not shared|

5. `wsl -l -v`
6. `usbipd attach --wsl --busid 1-3`

Connected:

|BUSID|  VID:PID|    DEVICE|                                                        STATE|
|--|--|--|--|
|1-3|    0483:374b|  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  |Attached|
|1-4|    260d:1099|  USB Input Device                                              |Not shared|
|1-6|    04f2:b7b4|  Integrated Camera, Integrated IR Camera, Camera DFU Device    |Not shared|
|1-9|    27c6:550a|  Goodix fingerprint                                            |Not shared|
|1-10|   0bda:5852|  Realtek Bluetooth Adapter                                     |Not shared|
### Wsl2
1. `lsusb`

|_|_|
|--|--|
|1d6b:0003| (bus 2, device 1)|
|0483:374b| (bus 1, device 2) path: 1|
|1d6b:0002| (bus 1, device 1)|

### Project
1. `chmod +x build_and_flash.sh`
2. `./build_and_flash.sh`