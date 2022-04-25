### XSavSig Gamesave Signing Profiles

A collection of `resign.ini` sections to add signing support of various gamesaves and game related data to XSavSig

---

#### How to use:
1) Copy the INI section(s) for whichever game(s) you want XSavSig to support
2) Open the `resign.ini` file stored in the XSavSig program directory with a text editing program
3) Paste the copied section(s) into the `resign.ini` and save the file
4) Run XSavSig, select the game you want to sign for, open the corresponding save file for the selected game, and click `Apply`

> Some gamesaves are signed as `non-roamable` and require the unique per-console `XboxHDKey` to be stored in the `xboxhddkey.ini` file. If the `XboxHDKey` is required then the key must be from the console you intend to copy the gamesave to or the save will display as "corrupt".

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

---

#### Roamable vs. Non-Roamable

A majority (not all) of gamesaves are "signed" using the built-in Xbox API provided hashing functions. The 2 most widely used signing methods are `roamable` and `non-roamable` signatures:

<br>

__Roamable:__ Save data signed with a _roamable_ signature can be copied freely between any console via a memory card or other means and will still be considered valid save data.

<br>

__Non-Roamable:__ Save data signed with a _non-roamable_ signature cannot be copied between consoles and is "locked" to the console it was initially created on. Copying a _non-roamble_ save to another console without signing it to the target consoles unique `XboxHDKey` beforehand will generally result in the game displaying a "corrupted" message on-screen.


---

Configurations
------


__Armed & Dangerous__

`XboxHDKey required`

```
[AAD]
ID=4C41000D
Title=Armed & Dangerous
SigKey=2B6E33422A6AEC5A41E4A77E6882201A
AuthKey=EB8174CA524C095806C7CADCEC3B8A5B
DataFile=options.opt
DataOffset=24
SigOffset=0
SigType=NoRoam
```

------

__Call of Duty: Finest Hour__

```
[CODFH]
ID=4156002A
Title=Call of Duty: Finest Hour
SigKey=50AFC9B126306875A53A9C4DB8E25A21
AuthKey=A5C7A0CC9922A1845AA2653D205C568B
DataFile=*.dat
DataOffset=24
DataLen=212
SigOffset=4
```

------

__Dead or Alive Ultimate__

`XboxHDKey required`

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

------

__Grabbed by the Ghoulies__

```
[GBTG]
ID=4D530053
Title=Grabbed by the Ghoulies
SigKey=4426DB89185652A1945C8820DC5A0A43
AuthKey=2618c508888e75b9363e23da8fe02d37
DataFile=progress.xsv
DataLen=1004
SigOffset=1004
```

------

__Hitman: Contracts__

```
[HC]
ID=45530012
Title=Hitman: Contracts
SigKey=2AE2713DD4A34AE3F20C29CD851DD327
AuthKey=8272AAD74300C29BD4B90768F2313BFE
DataFile=*.xsv
DataLen=-24
SigOffset=-24
```

------

__Jet Set Radio Future__

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

------

__Mafia__

`XboxHDKey required`

```
[Mafia]
ID=54540009
Title=Mafia
SigKey=7F2BFB0822D125B958DAA8E9C640B83D
AuthKey=0A3C62B3153DB2FC9B4C0A1DC72371B0
DataFile=*.*
DataLen=-20
SigOffset=-20
SigType=NoRoam
```

------

__Metal Gear Solid 2: Substance__

```
[MGS2]
ID=4B4E0007
Title=Metal Gear Solid 2: Substance
SigKey=EF10BE0E45D1F420604450136C358A14
AuthKey=A1543DE6F21C1700C1A9C39D9D8DE429
DataFile=*.d
DataOffset=24
DataLen=-24
SigOffset=4
```

------

__Ninja Gaiden__

`XboxHDKey required`

```
[NG_SAVE]
ID=54430003
Title=Ninja Gaiden - Save File
SigKey=A50114CA2B7C8198E829E7C937D6FC40
AuthKey=B32B2E0A471CDE09C8E2F925E87C9CA768964B34
DataFile=*.dat
DataOffset=20
SigOffset=0
SigType=NoRoam

[NG_SYSTEM]
ID=54430003
Title=Ninja Gaiden - System File
SigKey=A50114CA2B7C8198E829E7C937D6FC40
AuthKey=B32B2E0A471CDE09C8E2F925E87C9CA768964B34
DataFile=system.dat
DataOffset=20
SigOffset=0
SigType=NoRoam
```

------

__Ninja Gaiden Black__

`XboxHDKey required`

```
[NGB_SAVE]
ID=5443000D
Title=Ninja Gaiden Black - Save File
SigKey=FC3376488B3E5F00F65A6BDA9209CFE8
AuthKey=BE4FA303FD1EE6B9E276E04A6648289C
DataFile=*.dat
DataOffset=20
SigOffset=0
SigType=NoRoam

[NGB_SYSTEM]
ID=5443000D
Title=Ninja Gaiden Black - System File
SigKey=FC3376488B3E5F00F65A6BDA9209CFE8
AuthKey=BE4FA303FD1EE6B9E276E04A6648289C
DataFile=system.dat
DataOffset=20
SigOffset=0
SigType=NoRoam
```

------

__Project Gotham Racing 2__

```
[PGR2]
ID=4D53004B
Title=Project Gotham Racing 2
SigKey=E24F381F76FA6084DD4E25607184EF81
AuthKey=DAF08DBEFECFFA314876F9837FCC2090
DataFile=Profile.sav
DataOffset=20
DataLen=-20
SigOffset=0
```

------

__Splinter Cell: Chaos Theory__

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

------

__Splinter Cell: Double Agent__

`XboxHDKey required`

```
[SCDA]
ID=5553005E
Title=Splinter Cell: Double Agent
SigKey=61676F08B31D71DCF8E02903CB5164BB
AuthKey=0E07D758C668860E11BD19181569B838
DataFile=*.sav
DataLen=-20
SigOffset=-20
SigType=NoRoam
```

------

__Splinter Cell: Pandora Tomorrow__

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

------

__Star Wars: Republic Commando__

`XboxHDKey required`

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

------

__The Thing__

`XboxHDKey required`

```
[TT_NTSC]
ID=5655000D
Title=The Thing - Save File (NTSC)
SigKey=43CB904A552EAC237D62D9D2EC2E7D9C
AuthKey=9EC891A685B9E6F74727F7F2513F5D88
DataFile=*.sav
DataOffset=20
DataLen=-20
SigOffset=0

[TT_NTSC_OPT]
ID=5655000D
Title=The Thing - Options File (NTSC)
SigKey=43CB904A552EAC237D62D9D2EC2E7D9C
AuthKey=9EC891A685B9E6F74727F7F2513F5D88
DataFile=Options.dat
DataOffset=20
DataLen=-20
SigOffset=0
SigType=NoRoam

[TT_PAL]
ID=56560003
Title=The Thing - Save File (PAL)
SigKey=1CE3975F1B2486B4264ADC9D1D844D17
AuthKey=CFAC2B7197509F5FBA3E8B48887DA60B
DataFile=*.sav
DataOffset=20
DataLen=-20
SigOffset=0

[TT_PAL_OPT]
ID=56560003
Title=The Thing - Options File (PAL)
SigKey=1CE3975F1B2486B4264ADC9D1D844D17
AuthKey=CFAC2B7197509F5FBA3E8B48887DA60B
DataFile=Options.dat
DataOffset=20
DataLen=-20
SigOffset=0
SigType=NoRoam
```

------

__TimeSplitters 2__

```
[TS2_SAVE]
ID=4553000A
Title=TimeSplitters 2 - Save File
SigKey=D8A7948C1A665B9E11E090CC55D3CEC2
AuthKey=ABE92BE49BBEF5C6C6C232CC79688CBC
DataFile=*.ts2
DataOffset=20
SigOffset=0

[TS2_MAP]
ID=4553000A
Title=TimeSplitters 2 - Map File
SigKey=D8A7948C1A665B9E11E090CC55D3CEC2
AuthKey=ABE92BE49BBEF5C6C6C232CC79688CBC
DataFile=*.mkr
DataOffset=0
DataLen=-20
SigOffset=-20
```

