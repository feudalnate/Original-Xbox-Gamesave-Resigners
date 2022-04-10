# Ninja Gaiden Black Re-signer


### Usage (command line):
> ngbsign.exe [XboxHDKey] [file]


------

#### Gamesave locations:

NTSC-U / NTSC-J / PAL
> /UDATA/5443000D/[SaveID]/`save###.dat`

> /TDATA/5443000D/`system.dat`


------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"

```
[NGB]
ID=5443000D
Title=Ninja Gaiden Black
SigKey=FC3376488B3E5F00F65A6BDA9209CFE8
AuthKey=BE4FA303FD1EE6B9E276E04A6648289C
DataFile=*.*
DataOffset=20
SigOffset=0
SigType=NoRoam
```
