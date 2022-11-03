# Gladius Re-signer


### Usage (command line):
> gladsign.exe [file]

------

#### Gamesave location:

> /UDATA/4C410008/[SaveID]/`SaveGame.xsv`

------

#### Internal Data Block Format (`SaveGame.xsv`)

> Saves contain one or more data blocks aligned one after the other until EOF


| Offset | Length | Data Type | Description                                         |
|--------|--------|-----------|-----------------------------------------------------|
| 0x0    | 0x4    | int32     | Size of entire block (including size and hash)      |
| 0x4    | 0x14   | byte      | Block data hash (XAPI roamable signature)           |
| 0x18   | ???    | byte      | Block data start. Length = (block size - 0x18)      |


------

#### XSavSig

**WARNING: XSavSig cannot support signing for this games save files**

> Add entry to "resign.ini"

```
[Gladius]
ID=4C410008
Title=Gladius
SigKey=48A73E2F85CF76F105EE68AC96231B2B
AuthKey=6C5734C7303C5EEB98E677A27B0E89D7
```
