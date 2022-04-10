# Dead or Alive 1/2 Ultimate Re-signer


### Usage (command line):
> doausign.exe [XboxHDKey] [file]


------

#### Gamesave locations:

NTSC-U / NTSC-J / PAL
> /UDATA/54430006/[SaveID]/`*.*`

<details>
<summary>View 3 known file names</summary>

```
doasave.sav
br.dat
ups.dat
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
[DOAU]
ID=54430006
Title=Dead or Alive Ultimate
SigKey=42CBF532BF1FD14739D0F7F66DF8B7B1
AuthKey=113CBBA711C45DC03E68CA131E4376EF
DataFile=*.*
DataOffset=20
SigOffset=0

[DOAU_NR]
ID=54430006
Title=Dead or Alive Ultimate (ups.dat)
SigKey=42CBF532BF1FD14739D0F7F66DF8B7B1
AuthKey=113CBBA711C45DC03E68CA131E4376EF
DataFile=ups.dat
DataOffset=20
SigOffset=0
SigType=NoRoam
```
