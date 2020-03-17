[![Thingiverse](https://img.shields.io/badge/Thingiverse-TableDisco-blue.svg)](https://www.thingiverse.com/thing:3671784)
[![Thingiverse](https://img.shields.io/badge/Github-TableDisco-brightgreen.svg)](https://github.com/geaz/tableDisco)

# TableDisco
**TableDisco** is a connected and music reactive table light. Each light is self operating and you can add as many lights as you want.

The first powered **TableDisco** will start a naive *WiFi-Mesh* and is the *root* of the new **TableDisco** mesh. The *root disco* acts as the *sound analyzer* for the whole mesh. Each addtional powered **TableDisco** will automatically connect to the mesh.

On activation the **TableDiscos** are *"only"* pretty table lights. As soon as
the *mode switcher* on the *root disco* is pressed, all **TableDiscos** will switch to the **Disco Mode**.

In **Disco Mode** the *root disco* will analyze the surrounding sound. By taking the volume and frequency into account, it will calculate a color and brightness. The *root disco* will then broadcast this color to the **TableDisco** mesh. Doing so, all **TableDiscos** will simultaneously react to the surrounding sound of the *root disco*.

Furthermore the **TableDisco** includes an OTA update mechanism.

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
- TP4056 charging board (make sure you buy one rated for 1A and with integrated load protector)
- [Li-Ion 18650 (I used a 3350mAh one)](https://ebay.us/9vmIsS)
- [4x WS2812B LEDs (I used a strip and cut it)](https://www.amazon.de/dp/B01CDTED80)
- 4x M2x12mm screws
- [Stripboard](https://www.amazon.com/dp/B00C9NXP94)
- Wire

## Build

WIP

![TableDisco - Schematics](https://raw.githubusercontent.com/geaz/tableDisco/master/images/Schematics.png)

![TableDisco - VeroBoard](https://raw.githubusercontent.com/geaz/tableDisco/master/images/VeroBoard.png)

![TableDisco - 1](https://raw.githubusercontent.com/geaz/tableDisco/master/images/1.jpg)

![TableDisco - 2](https://raw.githubusercontent.com/geaz/tableDisco/master/images/2.jpg)

![TableDisco - 3](https://raw.githubusercontent.com/geaz/tableDisco/master/images/3.jpg)

![TableDisco - 4](https://raw.githubusercontent.com/geaz/tableDisco/master/images/4.jpg)

![TableDisco - 5](https://raw.githubusercontent.com/geaz/tableDisco/master/images/5.jpg)

![TableDisco - 6](https://raw.githubusercontent.com/geaz/tableDisco/master/images/6.jpg)

![TableDisco - 7](https://raw.githubusercontent.com/geaz/tableDisco/master/images/7.jpg)

## OTA Update

WIP