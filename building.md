# BrailleSPK building manual

## Solder elements on PCB

### XIAO ESP32-C3 Welding

<img src="./pictures/20260829_100808.jpg" alt="The ESP32C3 in place" width="25%" />

 - Take care of the USB connector orientation to place the MCU on board

### Audio Amp Welding


<img src="./pictures/20260829_101201.jpg" alt="The audio amp in place" width="25%" />

 - We use header pin to solder the audio output on the PCB. On audio amp the output connector use 3mm space. I've used 2 isolated pins cut from a standard 2.54 header.

### Soldering the speaker and glue it on PCB

<img src="./pictures/20260827_082309.jpg" alt="The audio speaker in place" width="25%" />

- Solder the speaker wire on the BrailleSPK PCB. Respect the +/- polarity of the speaker.
- Glue the speaker on the PCB. Most 1510 speaker are equipped with adhesive tape.

### Upload the firmware

 - Open the firmware in 'firmware' directory with Arduino IDE version 2.3.x or later
 - Install ESP32 compiler if needed ([detail instructions available here](https://wiki.seeedstudio.com/Getting_Started_with_Arduino/))
 - Select **XIAO ESP32-C3** in menu **Tools/Board**.

 <img src="./pictures/arduino_xia_select.png" alt="Select XIAO" width="25%" />
 
 - Select "Huge partition scheme" in menu **Tools/Partition Scheme**.

 <img src="./pictures/partition_xiao.png" alt="Huge partition scheme" width="25%" />

 - Compile and upload the firmware

### Install Braille dots on BrailleSPK PCB

 - Gently insert 6 dots.stl on each keyboard switch of the BrailleSPK PCB.

### Install the action button

  - Insert the **bouton.stl** part in the hole on the top of the part **capot.stl**.

   <img src="./pictures/20260829_101028.jpg" alt="Huge partition scheme" width="25%" />

### Install the PCB

 - Gently put the PCB in place in **capot.stl** part, take care the action bouton stay in place.

 <img src="./pictures/20260829_101047.jpg" alt="Place the PCB" width="25%" />

 - Check that the action button is aligned with the PCB switch.

 <img src="./pictures/20260829_101142.jpg" alt="Huge partition scheme" width="25%" />

### Close the box

 - Put in place the part **fond.stl**. Use 3 M3-12 hex screw to secure the assembly.

## Enjoy !




 
