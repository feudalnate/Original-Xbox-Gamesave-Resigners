# FlatOut 2 Re-signer


### Usage (command line):
> fo2sign.exe [XboxHDKey] [file]


------

#### Gamesave locations:

NTSC-U / NTSC-J / PAL
> /UDATA/454D0020/[SaveID]/`*.sav`


------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"

```
[FO2]
ID=454D0020
Title=FlatOut 2
SigKey=EC1981167F15ACB9FEAD8AB67A02C1A5
AuthKey=9E20635C39F13E314A9D297154F354FD
DataFile=*.sav
DataOffset=0
DataLen=-20
SigOffset=-20
SigType=NoRoam
```
