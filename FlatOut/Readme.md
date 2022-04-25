# FlatOut Re-signer


### Usage (command line):
> fosign.exe [XboxHDKey] [file]


------

#### Gamesave locations:

NTSC-U / NTSC-J / PAL
> /UDATA/454D0009/[SaveID]/`*.sav`


------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"

```
[FO]
ID=454D0009
Title=FlatOut
SigKey=C8D3C3573CFAD039B9DBB54D742ED579
AuthKey=586D8E52CAC2F01568E46C5975E79852
DataFile=*.sav
DataOffset=0
DataLen=-20
SigOffset=-20
SigType=NoRoam
```
