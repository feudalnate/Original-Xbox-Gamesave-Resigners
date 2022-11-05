# Jet Set Radio Future Re-signer


### Usage (command line):

__NTSC-U / NTSC-J__
> jsrfsign.exe ntsc [file]


__PAL__
> jsrfsign.exe pal [file]

<br>

> __NOTE:__ To convert a NTSC save to a PAL save or vice-versa, sign to the desired region

------

#### Gamesave locations:

__NTSC-U / NTSC-J__
> /UDATA/5345000A/[SaveID]/`JSRFDATA.SAV`


__PAL__
> /UDATA/49470018/[SaveID]/`JSRFDATA.SAV`

------

#### XSavSig

> Add entry to "resign.ini"

```
[JSRF_NTSC]
ID=5345000A
Title=Jet Set Radio Future (NTSC)
SigKey=E1D4118A91D20D24C0E3BBB16232964D 
AuthKey=B93F95768BB7A5CA0DE856FE4E94C299 
DataFile=JSRFDATA.SAV
DataOffset=20 
DataLen=-20
SigOffset=0

[JSRF_PAL]
ID=49470018
Title=Jet Set Radio Future (PAL)
SigKey=074BD1972F7BE074539F82143A722E4F 
AuthKey=27F169A87D6753B9A71CFFC205033C2A 
DataFile=JSRFDATA.SAV 
DataOffset=20 
DataLen=-20
SigOffset=0
```
