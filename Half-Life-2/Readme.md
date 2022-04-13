# Half-Life 2 Re-signer


### Usage (command line):
> hl2sign.exe [XboxHDKey] [file]


------

#### Gamesave locations:

NTSC-U / NTSC-J / PAL
> /UDATA/45410091/[SaveID]/`*.*`

> /TDATA/45410091/hl2/hl2x/cfg/`*.cfg`

> /TDATA/45410091/hl2/hl2x/SAVE/`*.*`

<details>
<summary>View 9 known file names</summary>

```
save*
save*.pic
continue.cfg
xboxuser.cfg
_transition
autosave
*.hl1
*.hl2
*.hl3
```

</details>

------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

**WARNING: XSavSig cannot support signing for this games save files**

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"

```
[HL2]
ID=45410091
Title=Half-Life 2
SigKey=CCB0F5720B1478A0B2C518AB429E7DEA
AuthKey=F6CC28337A69F83B5C8CDD994B043943
```
