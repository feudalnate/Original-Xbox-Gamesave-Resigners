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

__Index__

- [Armed & Dangerous](#armed--dangerous)
- [Breakdown](#breakdown)
- [Burnout 3: Takedown](#burnout-3-takedown)
- [Call of Duty: Finest Hour](#call-of-duty-finest-hour)
- [Darkwatch](#darkwatch)
- [Dead or Alive Ultimate](#dead-or-alive-ultimate)
- [Far Cry Instincts](#far-cry-instincts)
- [Far Cry Instincts: Evolution](#far-cry-instincts-evolution)
- [FlatOut](#flatout)
- [FlatOut 2](#flatout-2)
- [Forza Motorsport](#forza-motorsport)
- [Grabbed by the Ghoulies](#grabbed-by-the-ghoulies)
- [Halo: Combat Evolved](#halo-combat-evolved)
- [Halo 2](#halo-2)
- [Hitman: Contracts](#hitman-contracts)
- [Jet Set Radio Future](#jet-set-radio-future)
- [Mafia](#mafia)
- [Metal Gear Solid 2: Substance](#metal-gear-solid-2-substance)
- [MotoGP](#motogp)
- [MotoGP 2](#motogp-2)
- [Ninja Gaiden](#ninja-gaiden)
- [Ninja Gaiden Black](#ninja-gaiden-black)
- [Otogi: Myth of Demons](#otogi-myth-of-demons)
- [Otogi 2: Immortal Warriors](#otogi-2-immortal-warriors)
- [Project Gotham Racing 2](#project-gotham-racing-2)
- [Silent Hill 4: The Room](#silent-hill-4-the-room)
- [Splinter Cell: Chaos Theory](#splinter-cell-chaos-theory)
- [Splinter Cell: Double Agent](#splinter-cell-double-agent)
- [Splinter Cell: Pandora Tomorrow](#splinter-cell-pandora-tomorrow)
- [Star Wars: Republic Commando](#star-wars-republic-commando)
- [Steel Battalion: Line of Contact](#steel-battalion-line-of-contact)
- [The Thing](#the-thing)
- [TimeSplitters 2](#timesplitters-2)
- [TRON 2.0: Killer App](#tron-20-killer-app)

------

#### Armed & Dangerous

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

#### Breakdown

```
[BD]
ID=4E4D0009
Title=Breakdown (data.sav)
SigKey=73006AC72D8070BF9E200D9A7E2042F4
AuthKey=4B15F0F2FD0EC19C8104A789602C922E
DataFile=data.sav
DataOffset=0
DataLen=0x1FC30
SigOffset=0x1FC30

[BD_SYS]
ID=4E4D0009
Title=Breakdown (system.sav)
SigKey=73006AC72D8070BF9E200D9A7E2042F4
AuthKey=4B15F0F2FD0EC19C8104A789602C922E
DataFile=system.sav
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### Burnout 3: Takedown

`XboxHDKey required`

```
[B3]
ID=4541005B
Title=Burnout 3: Takedown
SigKey=8F4BC9B5D6B01E7F4772C5ACE04BC922
AuthKey=B22A08CC431324366E65ADF1427845DC
DataFile=*.*
DataOffset=0
DataLen=-20
SigOffset=-20
SigType=NoRoam
```

------

#### Call of Duty: Finest Hour

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

#### Darkwatch

```
[DW_NTSCU]
ID=43430016
Title=Darkwatch (NTSC-U)
SigKey=42AB477C2A5D3F4842256474E14DE672
AuthKey=96E3FD75D5929064C61D7CD2EE223AC0
DataFile=*.*
DataOffset=0
DataLen=-20
SigOffset=-20

[DW_PAL]
ID=5553005C
Title=Darkwatch (PAL)
SigKey=9CE2958FBA2E2649E58CDB79F5595A86
AuthKey=A0098831DCF721B2F25B681D13E4FF97
DataFile=*.*
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### Dead or Alive Ultimate

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

#### Far Cry Instincts

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

------

#### Far Cry Instincts: Evolution

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

------

#### FlatOut

`XboxHDKey required`

```
[FO]
ID=454D0009
Title=FlatOut
SigKey=C8D3C3573CFAD039B9DBB54D742ED579
AuthKey=586D8E52CAC2F01568E46C5975E79852
DataFile=*.sav
DataOffset=0
DataLen=-20
SigOffset=-20
SigType=NoRoam
```

------

#### FlatOut 2

`XboxHDKey required`

```
[FO2]
ID=454D0020
Title=FlatOut 2
SigKey=EC1981167F15ACB9FEAD8AB67A02C1A5
AuthKey=9E20635C39F13E314A9D297154F354FD
DataFile=*.sav
DataOffset=0
DataLen=-20
SigOffset=-20
SigType=NoRoam
```

------

#### Forza Motorsport

`XboxHDKey required`

```
[FM_NR]
ID=4D53006E
Title=Forza Motorsport (non-roamable)
SigKey=9B62FF6FF98DD4F002A1BD2B72608EFC
AuthKey=909260B0E496746D5A1DC067A694F830
;-----
;SUPPORTED FILES: "UserProfile.xml", "Garage.bin", "Garage.dat", "*.crt", "Leaderboard*"
;-----
DataFile=*.* 
DataOffset=0
DataLen=-20
SigOffset=-20
SigType=NoRoam

[FM_R]
ID=4D53006E
Title=Forza Motorsport (roamable)
SigKey=9B62FF6FF98DD4F002A1BD2B72608EFC
AuthKey=909260B0E496746D5A1DC067A694F830
;-----
;SUPPORTED FILES: "*.FGF", "*.frp"
;-----
DataFile=*.* 
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### Grabbed by the Ghoulies

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

#### Halo: Combat Evolved

```
[H1_G]
ID=4D530004
Title=Halo: Combat Evolved (Gametype)
SigKey=1F71DE93D52AADB19446D7494F731158
AuthKey=5770E155A1C75FA9830B141896544428
DataFile=blam.lst
DataOffset=0
DataLen=104
SigOffset=104

[H1_P]
ID=4D530004
Title=Halo: Combat Evolved (Profile)
SigKey=1F71DE93D52AADB19446D7494F731158
AuthKey=5770E155A1C75FA9830B141896544428
DataFile=blam.sav
DataOffset=0
DataLen=48
SigOffset=48

[H1_G_TW]
ID=4D530057
Title=Halo: Combat Evolved (Taiwan) (Gametype)
SigKey=FEFE53BC72E2E07444D1D318ACE06DAC
AuthKey=087F980482788FE539573697D7387BC2
DataFile=blam.lst
DataOffset=0
DataLen=104
SigOffset=104

[H1_P_TW]
ID=4D530057
Title=Halo: Combat Evolved (Taiwan) (Profile)
SigKey=FEFE53BC72E2E07444D1D318ACE06DAC
AuthKey=087F980482788FE539573697D7387BC2
DataFile=blam.sav
DataOffset=0
DataLen=48
SigOffset=48
```

------

#### Halo 2

```
[H2]
ID=4D530064
Title=Halo 2
SigKey=2116D927510F01D19B7EC75CAFE669AC
AuthKey=29328FAC19662CD21C92C49936D4A58D
DataFile=*.*
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### Hitman: Contracts

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

#### Jet Set Radio Future

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

#### Mafia

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

#### Metal Gear Solid 2: Substance

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

#### MotoGP

```
[MGP]
ID=54510008
Title=MotoGP (NTSC-U)
SigKey=E32C0DCDF1200A729F54E81B5DEC06BA
AuthKey=5DDB49EB053FD0B4ADEAFB4F23D8008A
DataFile=gamedata
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### MotoGP 2

```
[MGP2]
ID=54510016
Title=MotoGP 2 (NTSC-U)
SigKey=1A6AAB369117FBEDFC2CBCE8395E8973
AuthKey=CD6D6EB71089E557483E66BC51F55CC4
DataFile=profile
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### Ninja Gaiden

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

#### Ninja Gaiden Black

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

#### Otogi: Myth of Demons

```
[O1MoD]
ID=46530002
Title=Otogi: Myth of Demons
SigKey=BC8C7B2D9CDFCE88DB435445EAD78DAD
AuthKey=15BCC6854D8122990D0C964894C813BD
DataFile=*.xsv
DataOffset=24
DataLen=-24
SigOffset=4
```

------

#### Otogi 2: Immortal Warriors

```
[O2IM]
ID=46530004
Title=Otogi 2: Immortal Warriors
SigKey=456DFE66A20E0A976AED8F85FC978B39
AuthKey=6F2502B88D553CE3AF4242FB203B6AE0
DataFile=*.xsv
DataOffset=24
DataLen=-24
SigOffset=4
```

------

#### Project Gotham Racing 2

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

#### Silent Hill 4: The Room

```
[SH4]
ID=4B4E001F
Title=Silent Hill 4: The Room
SigKey=F51CE54B75A442BE31C167AA96999672
AuthKey=2DC1FD8C6F2EE0524A766D37E586B742
DataFile=*.dat
DataOffset=0
DataLen=-20
SigOffset=-20
```

------

#### Splinter Cell: Chaos Theory

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

#### Splinter Cell: Double Agent

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

#### Splinter Cell: Pandora Tomorrow

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

#### Star Wars: Republic Commando

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

#### Steel Battalion: Line of Contact

```
[SBLoC]
ID=43430009
Title=Steel Battalion: Line of Contact
SigKey=B91003CEC57E68A99AA961D10DC34C98
AuthKey=7281FDBCCDC944DE71C341B4730A2D77
DataFile=*.*
DataOffset=24
DataLen=-24
SigOffset=4
```

------

#### The Thing

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

#### TimeSplitters 2

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

------

#### TRON 2.0: Killer App

```
[TRON]
ID=42560001
Title=TRON 2.0 Killer App
SigKey=8DF7A69459390F9BFA41012D82445519
AuthKey=7408C4B5755BA389CF0BF0BCB1153A50
DataFile=*.sav
DataOffset=20
DataLen=-20
SigOffset=0
```
