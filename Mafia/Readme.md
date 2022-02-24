# Mafia Re-signer


### Usage (command line):
`Single file`
> mafiasign.exe [XboxHDKey] [file]

`Directory`
> mafiasign.exe [XboxHDKey] [folder]

Note: When bulk signing files in a directory, only **known file names** will be signed

------

#### Gamesave location:
> /UDATA/54540009/[SaveID]/`[known file name]`

<details>
<summary>View known file names</summary>

```
110 known files  

mafia.000, mafia.005, mafia.010, mafia.015, mafia.020, mafia.025, mafia.030, mafia.040, mafia.045, mafia.050
mafia.055, mafia.060, mafia.065, mafia.070, mafia.075, mafia.080, mafia.085, mafia.090, mafia.095, mafia.100
mafia.105, mafia.110, mafia.115, mafia.130, mafia.131, mafia.135, mafia.140, mafia.145, mafia.146, mafia.150
mafia.155, mafia.160, mafia.165, mafia.170, mafia.185, mafia.190, mafia.195, mafia.197, mafia.200, mafia.205
mafia.220, mafia.223, mafia.225, mafia.230, mafia.235, mafia.240, mafia.243, mafia.245, mafia.260, mafia.263
mafia.265, mafia.270, mafia.275, mafia.277, mafia.280, mafia.290, mafia.295, mafia.310, mafia.315, mafia.320
mafia.325, mafia.330, mafia.335, mafia.340, mafia.345, mafia.350, mafia.355, mafia.360, mafia.370, mafia.372
mafia.375, mafia.380, mafia.385, mafia.390, mafia.405, mafia.407, mafia.410, mafia.415, mafia.425, mafia.430
mafia.435, mafia.440, mafia.452, mafia.455, mafia.460, mafia.465, mafia.466, mafia.470, mafia.475, mafia.487
mafia.490, mafia.495, mafia.497, mafia.500, mafia.505, mafia.520, mafia.525, mafia.530, mafia.532, mafia.535
mafia.540, mafia.550, mafia.552, mafia.555, mafia.557, mafia.560, mafia.561, mafia.570, mafia.sav, mr.sav
```
</details>

------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"
```
[54540009]
ID=54540009
Title=Mafia
SigKey=7F2BFB0822D125B958DAA8E9C640B83D
AuthKey=0A3C62B3153DB2FC9B4C0A1DC72371B0
DataFile=*.*
DataLen=-20
SigType=NoRoam
SigOffset=-20
```
