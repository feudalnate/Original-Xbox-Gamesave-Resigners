[Jump to Xbox 360](#retrieving-the-xboxhdkey-from-the-xbox-360)

## Retrieving the XboxHDKey from the `Xbox`

#### Requirements
- Option 1: Modded console (softmod or hardmod)
- Option 2: Access to dumped EEPROM data (typically a `EEPROM.bin` file)



### Option 1: Modded console (softmod or hardmod)
------

Using a modded console the XboxHDKey can be obtained through software alone. Various dashboards and tools such as UnleashX dashboard, EvolutionX dashboard, Xbox Media Center, ConfigMagic, and various other applications will make this information available at a glance

![Image](https://i.imgur.com/d9GiC03.png)

------

### Option 2: Access to dumped EEPROM data
------

Using a dump of the EEPROM data the XboxHDKey can be obtained by opening the dump in a tool such a `LiveInfo`

![Image](https://i.imgur.com/nvqIDZd.png)
------

## Retrieving the XboxHDKey from the `Xbox 360`

#### Requirements
- Option 1: Tools and ability to disassemble the console
- Option 2: Access to dumped and decrypted keyvault data (typically a `KV.bin` file)

***In both cases for the Xbox 360 the goal is to obtain the `console serial number` and the `motherboard serial number`***



### Option 1: Tools and ability to disassemble the console
------

The `console serial number` can be obtained from either the **rear of the console** or through the Xbox 360 dashboard, under **Console Settings > System Info**

![Image](https://i.imgur.com/DCKImZV.png)
![Image](https://i.imgur.com/dBZRYNa.png)

The `motherboard serial number` can be obtained from a **sticker on top of the Xbox 360 motherboard** and requires opening the console
> The `motherboard serial number` is a string of *hexadecimal* characters (0-9 A-F)

- [Xbox 360 disassembly](https://www.ifixit.com/Teardown/Xbox+360+Teardown/1203)
- [Xbox 360 S disassembly](https://www.ifixit.com/Teardown/Xbox+360+S+Teardown/107077)
- [Xbox 360 E disassembly](https://www.ifixit.com/Teardown/Xbox+360+E+Teardown/15062)

![Image](https://i.imgur.com/x2Vd5hi.jpg)

[Continue to: Combining console and motherboard serial numbers](#combining-console-and-motherboard-serial-numbers)

------

### Option 2: Access to dumped and decrypted keyvault data
------

Using a dump of the decrypted KV data both the console serial number and motherboard serial number can be obtained by opening the dump in a tool such a `360 Flash Dump Tool`

![Image](https://i.imgur.com/mAkf55o.png)

Once the console serial number and motherboard serial number have been retrieved you can continue to the following section to generate the XboxHDKey

------

### Combining console and motherboard serial numbers

After obtaining both the `console serial number` and the `motherboard serial number` you must generate the XboxHDKey based on those two serial numbers

The method for generating the XboxHDKey is to combine those two serial numbers as follows

```
null (4 bytes)

the motherboard serial (8 bytes) (convert hex->bytes)

the first 4 digits of the console serial (4 bytes) (convert utf8->bytes)

Z = null, M = mobo serial, C = console serial

ZZZZZZZZMMMMMMMMMMMMMMMMCCCCCCCC
```

You can also automate this process using the [`XboxHDKey for Xbox 360`](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/tree/master/XboxHDKey%20for%20Xbox%20360) tool which available in this repository

![Image](https://i.imgur.com/03TtEHd.png)

[Troubleshooting invalid motherboard serial number](https://www.reddit.com/r/originalxbox/comments/adwlwg/xbox_game_save_resigner_formula/edugoxb/?utm_medium=web2x&context=3) (scroll down to the bottom of the thread)
