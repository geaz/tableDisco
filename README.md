[![3D2P](https://img.shields.io/badge/3D2P-TableDisco-orange.svg)](https://3d2p.net/Project/CX0TQMEKNKIA2N85FOFMDW)
[![Github](https://img.shields.io/badge/Github-TableDisco-brightgreen.svg)](https://github.com/geaz/tableDisco)

# TableDisco
**TableDisco** is a connected and music reactive table light. Each light is self operating and you can add as many lights as you want.

[TODO Video - Single Light, Connected Light (light mdoe, disco mode)]

The first powered **TableDisco** will start a naive *WiFi-Mesh* and is the *root* of the new **TableDisco** mesh. The *root disco* acts as the *sound analyzer* for the whole mesh. Each addtional powered **TableDisco** will automatically connect to the mesh.

On activation the **TableDiscos** are *"only"* pretty table lights. But as soon as
the *mode switcher* on the *root disco* is pressed, all **TableDiscos** will switch to the **Disco Mode**.

In **Disco Mode** the *root disco* will analyze the surrounding sound. By taking the volume and frequency into account, it will calculate a color and brightness. The *root disco* will then broadcast this color to the **TableDisco** mesh. Doing so, all **TableDiscos** will simultaneously react to the surrounding sound of the *root disco*.

Furthermore the **TableDisco** includes an OTA update mechanism (an additional *update server device* is necessary - *OTA Update* chapter for details).

## 3D Model
The model was designed in Fusion360. The STLs are included in the Thingiverse downloads and the Github repository. Furthermore there is an exported Fusion360 Archive File ready to download.

## BOM (for one TableDisco)

- 3D Printed Parts (STL folder for models)
- Wemos D1 Mini
- Resistor 100k
- Capacitor 680uF
- [Momentary Switch](https://ebay.us/w5SPS8)
- [SPST Switch](https://www.amazon.de/dp/B076GXD7XN)
- MAX4466
- TP4056 charging board (make sure you buy one rated for 1A and with integrated load protection)
- [Battery Case](https://www.amazon.de/dp/B077XW1F9C) 
- [Li-Ion 18650 (I used a 3350mAh one)](https://ebay.us/9vmIsS)
- [4x WS2812B LEDs (I used a strip and cut it)](https://www.amazon.de/dp/B01CDTED80)
- 4x M2x12mm screws
- [Stripboard](https://www.amazon.com/dp/B00C9NXP94)
- Wire
- Double-faced adhesive tape

## Firmware

Before building the **TableDisco** you should flash the firmware onto the Wemos D1 Mini. This way you are able to make sure that it is functional.

Open the *src/firmware* folder in [Visual Studio Code](https://code.visualstudio.com/). This project uses [PlatformIO](https://platformio.org/platformio-ide) to develop the firmware. Install the PlatformIO extension into Visual Studio Code.

To flash the firmware onto the Wemos connect it to your PC and press the *Upload* button in the status bar.

![TableDisco - Flash](https://raw.githubusercontent.com/geaz/tableDisco/master/images/flash.png)

Aftererwards start the *Serial Monitor* and you should see some outputs like in the screenshot below. If you are able to see the output, the device is working and you are ready to build the **TableDisco**.

![TableDisco - Serial](https://raw.githubusercontent.com/geaz/tableDisco/master/images/serial.png)

## Build

For the first step take the printed *Base* and *Battery Indicator*. The *Battery Indicator* has to be inserted, hollow side to the bottom, into the little hole at the side of the *Base*. Use a pliers and a bit of force. It is a pretty tight fit.

![TableDisco - 1](https://raw.githubusercontent.com/geaz/tableDisco/master/images/1.jpg)

Prepare eleven ~5cm long wires and three ~10cm wires. This will be enough for the whole build. Take the three long wires and solder them onto the led strip.

![TableDisco - 2](https://raw.githubusercontent.com/geaz/tableDisco/master/images/2.jpg)

A piece of the stripboard (5x7 holes - in the picture below it is 5x9 for display pusposes - a 5x7 hole piece is sufficient for the build), the resistor and the capacitor are needed for the next step. Please use the next two pictures as a reference how to solder the stripboard. I recommend to solder the resistor first, then the wires and as a last step the capacitor (keep the polarity of the capacitor in mind).

![TableDisco - VeroBoard](https://raw.githubusercontent.com/geaz/tableDisco/master/images/VeroBoard.png)

![TableDisco - 3](https://raw.githubusercontent.com/geaz/tableDisco/master/images/3.jpg)

Now solder the battery case onto the battery pins of the TP4056. Solder the wire labeled *Power Ground*, in the strip board picture above, to the *OUT-* pin and a single ~5cm wire to te *OUT+* pin.

Take a pliers and grab the *battery indicator* and lift it up. Carefully slide the charging board into its position. **The LEDs are very easy to break. Be careful!** Use double-faced adhesive tape to mount the battery case into the *Base*.

![TableDisco - 4](https://raw.githubusercontent.com/geaz/tableDisco/master/images/4.jpg)

Insert the SPST switch into the case and solder the single wire of the *OUT+* pin to one end and the *Power VCC* of the stripboard to the other end.

![TableDisco - 5](https://raw.githubusercontent.com/geaz/tableDisco/master/images/5.jpg)

Now solder the two *Button* wires of the stripboard to the momentary switch and insert it into the case.
Solder the last ~5cm wire to the *OUT* pin of the microphone (MAX4466) and additionaly the two *Mic* wires of the stripboard to the *VCC* and *GND*. Insert the MAX4466 into the last whole of the *Base*.

![TableDisco - 5.1](https://raw.githubusercontent.com/geaz/tableDisco/master/images/5.1.jpg)

Take the *Middle*, the *Transparent* part and the *Top*. First use the *Middle* and tape the LEDs on it.

![TableDisco - 6](https://raw.githubusercontent.com/geaz/tableDisco/master/images/6.jpg)

Place the *Transparent* and finally the *Top* on it. Insert the *Bolts* and use the screws to lock the **TableDisco**.

Your **TableDisco** is done!

![TableDisco - 7](https://raw.githubusercontent.com/geaz/tableDisco/master/images/7.jpg)

## OTA Update

The **TableDisco** firmware provides the functionality for OTA (over the air) updates. To update the firmware on all **TableDiscos** you have to flash a spare *Wemos D1 Mini* device with the *updater firmware*.

Open the *src/updater* folder in Visual Studio Code and connect the spare device to your PC. Flash the *updater firmware* (same procedure as uploading the firmware for the **TableDisco**) and copy the **TableDisco** *firmware.bin update* file to the *src/updater/data* folder.

Press the *Upload File System image* task button in Visual Studio Code. This will copy the new firmware to the update device.

![TableDisco - FSTask](https://raw.githubusercontent.com/geaz/tableDisco/master/images/fsupload.png)

To update the **TableDiscos** switch on your *update device* (connect it to USB for example). This will create a WiFi Access Point to which the **TableDiscos** are able to connect.

On the **TableDiscos** hold the *mode switcher* button and switch it on. The light of the **TableDisco** will be *Cyan*. This indicates, that the **TableDisco** is in update mode and is scanning for the *update device*. The light will switch to *Yellow*, if the updater was found and that the **TableDisco** is connecting to it. The *Blue* light indicates, that the device is connected to the updater and is downloading and installing the new firmware. **Do not switch off the devices during this step!**

Afterwards the **TableDisco** will automatically restart with the new firmware installed.

[![TableDisco - OTA](https://img.youtube.com/vi/ygwx93fGblA/hqdefault.jpg)](https://youtu.be/ygwx93fGblA)  
> Click picture to play video of the process on YouTube.