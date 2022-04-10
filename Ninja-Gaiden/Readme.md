# Ninja Gaiden Re-signer


### Usage (command line):
> ngsign.exe [XboxHDKey] [file]


------

#### Gamesave locations:

NTSC-U / NTSC-J / PAL
> /UDATA/54430003/[SaveID]/`save###.dat`

> /TDATA/54430003/`system.dat`


------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"

```
[NG]
ID=54430003
Title=Ninja Gaiden
SigKey=A50114CA2B7C8198E829E7C937D6FC40
AuthKey=B32B2E0A471CDE09C8E2F925E87C9CA768964B34
DataFile=*.*
DataOffset=20
SigOffset=0
SigType=NoRoam
```
