# Far Cry Instincts: Evolution Re-Signer


### Usage (command line):
> fciesign.exe [file] [file2]

<br>

__NOTE:__ [file2] is expected to be a path to the corresponding `*.sig` file. ___[file2] is optional___ and will be created if not found in the same directory as the provided ___map file___. The `*.sig` file is used to store the signature for the corresponding ___map file___ found in the [MapID] folder.

------

#### Gamesave location:
> /UDATA/55530060/[SaveID]/`*.*`

> /TDATA/55530060/$K/FarCryEditor/SyslinkMaps/[MapID]/`*.*`

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
[FCIE]
ID=55530060
Title=Far Cry Instincts Evolution
SigKey=79A31342BE08D67E139F395DD4CDFAD6
AuthKey=51145D98282B7B70957089AE8DCA9CA2
DataFile=*.*
DataOffset=0
DataLen=-20
SigOffset=-20
```
