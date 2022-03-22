# Star Wars: Republic Commando Re-signer


### Usage (command line):
> swrpsign.exe [jp] [XboxHDKey] [file]

__NOTE: Only specify "jp" if signing NTSC-J gamesaves__

------

#### Gamesave location:

NTSC-U / PAL
> /UDATA/4C410013/[SaveID]/`*.*`

NTSC-J
> /UDATA/4C410019/[SaveID]/`*.*`

<details>
<summary>View 3 known file names</summary>

```
*.cts
System.ini
User.ini
```

</details>

------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entries to "resign.ini"

```
[SWRP]
ID=4C410013
Title=Star Wars: Republic Commando
SigKey=88C3BC25F5BB1DE11F1F6FCE21BF7F74
AuthKey=3A01DDD2D364F75800D556EB2E0CF9BD
DataFile=*.*
DataLen=-24
SigOffset=-20
SigType=NoRoam

[SWRP_JP]
ID=4C410019
Title=Star Wars: Republic Commando (Japan)
SigKey=54731ABF22F0EA8687AAA6478F4BAAEA
AuthKey=E050E8136F70B9E4A10A7B415226A098
DataFile=*.*
DataLen=-24
SigOffset=-20
SigType=NoRoam
```
