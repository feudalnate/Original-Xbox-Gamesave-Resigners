# Fatal Frame / Project ZERO Re-signer


### Usage (command line):
> ffsign.exe [na|pal] [XboxHDKey] [file]
<br>

> NOTE: Specify "na" to sign for Fatal Frame (NTSC-U) or "pal" for Project ZERO (PAL)

**NTSC-J is not supported**

------

#### Gamesave locations:

Fatal Frame (NTSC-U)
> /UDATA/54430004/[SaveID]/`G`

Project ZERO (PAL)
> /UDATA/4D530059/[SaveID]/`N`

------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

**WARNING: XSavSig cannot support signing for this games save files**

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"

```
[FF]
ID=54430004
Title=Fatal Frame
SigKey=BD1E1C7B4DB4BA8D49E37EA24F80F14E
AuthKey=2E10F04B6560C35A03A12A33C6AF7FE6

[PZ]
ID=4D530059
Title=Project ZERO
SigKey=0D07E43488A315BF1BDC3B47E0B46B24
AuthKey=9BD8C3DF2EE5BC9E48B00165D244E6A3
```
