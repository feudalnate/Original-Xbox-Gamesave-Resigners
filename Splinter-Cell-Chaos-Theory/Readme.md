# Splinter Cell: Chaos Theory Re-signer


### Usage (command line):
> scctsign.exe [file]

------

#### Gamesave location:

Single Player / CO-OP
> /UDATA/55530038/[SaveID]/`*.sav`

Multiplayer
> /UDATA/55530041/[SaveID]/`Online.prf`

<details>
<summary>View 26 known file names</summary>

```
single0.sav
single1.sav
single2.sav
single3.sav
single4.sav
single5.sav
multi0.sav
multi1.sav
multi2.sav
multi3.sav
multi4.sav
multi5.sav
single0image.sav
single1image.sav
single2image.sav
single3image.sav
single4image.sav
single5image.sav
multi0image.sav
multi1image.sav
multi2image.sav
multi3image.sav
multi4image.sav
multi5image.sav
profile.sav
Online.prf
```

</details>

> NOTE: Single Player / CO-OP files are pre-allocated whether used or not. Unused files may contain uninitialized junk data.

------

#### XSavSig

> Add entries to "resign.ini"

```
[SCCT_SP]
ID=55530038
Title=Splinter Cell: Chaos Theory
SigKey=EC3283DB375155B3929ED6F1E1C9546F
AuthKey=80B01C733549071203F4208F5A00B3E7
DataFile=*.sav
DataLen=-20
SigOffset=-20

[SCCT_MP]
ID=55530041
Title=Splinter Cell: Chaos Theory (Online.prf)
SigKey=6342DD40F83B4728EA822BFD8CB13AC4
AuthKey=6250A824A0FD5C108FE705EB13E7FCEE
DataFile=Online.prf
DataOffset=20
DataLen=-20
SigOffset=0
```
