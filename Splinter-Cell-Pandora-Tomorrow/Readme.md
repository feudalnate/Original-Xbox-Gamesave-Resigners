# Splinter Cell: Pandora Tomorrow Re-signer


### Usage (command line):
> scptsign.exe [file]

------

#### Gamesave location:
> /UDATA/55530019/[SaveID]/`*.*`

<details>
<summary>View 5 known file names</summary>

```
*.sg1
*.sg2
*.sg3
offline.prf
online.prf
```

</details>

------

#### XSavSig

> Add entries to "resign.ini"

```
[SCPT_SP]
ID=55530019
Title=Splinter Cell: Pandora Tomorrow
SigKey=0D5B5C7E20F73FF9C24EC23B9A66B341
AuthKey=E00141FE5F785D32ABED7AD43809EBFF
DataFile=*.*
DataLen=-20
SigOffset=-20

[SCPT_MP]
ID=55530019
Title=Splinter Cell: Pandora Tomorrow (online.prf)
SigKey=0D5B5C7E20F73FF9C24EC23B9A66B341
AuthKey=E00141FE5F785D32ABED7AD43809EBFF
DataFile=online.prf
DataOffset=20
DataLen=-20
SigOffset=0
```
