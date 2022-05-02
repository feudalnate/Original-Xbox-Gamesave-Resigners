# Far Cry Instincts Re-Signer


### Usage (command line):
> fcisign.exe [file] [file2]

<br>

__NOTE:__ [file2] is expected to be a path to the corresponding `*.sig` file. ___[file2] is optional___ and will be created if not found in the same directory as the provided ___map file___. The `*.sig` file is used to store the signature for the corresponding ___map file___ found in the [MapID] folder.

------

#### Gamesave location:
> /UDATA/55530008/[SaveID]/`*.*`

> /TDATA/55530008/$K/FarCryEditor/SyslinkMaps/[MapID]/`*.*`

__NOTE:__ Maps stored in the "LiveMaps" folder have not been tested. Only maps stored in the "SyslinkMaps" folder are known to be signable.

<details>
<summary>View 8 known file names</summary>

```
*.fcs
*.mt
*.dat
*.fat
*.dat.sig
*.fat.sig
profile.sav
renamer.ren
```

</details>

------

#### XSavSig

__WARNING: XSavSig cannot support signing for map files because the map file signature is stored in a seperate file. XSavSig does not support accessing multiple files at once.__ (gamesaves are okay)

<br>

> Add entry to "resign.ini"
```
[FCI]
ID=55530008
Title=Far Cry Instincts
SigKey=2FF20BB65D72ED5D46A2A2D625E1A625
AuthKey=FEE516F601C6432342E0753A090A02B5
DataFile=*.*
DataOffset=0
DataLen=-20
SigOffset=-20
```
