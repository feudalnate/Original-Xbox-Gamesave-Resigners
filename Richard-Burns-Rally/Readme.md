# Richard Burns Rally Re-signer


### Usage (command line):
> rbrsign.exe [XboxHDKey] [file] [file2]

<br>

__NOTE:__ [file2] is expected to be a path to the corresponding `signa.tur` file. ___[file2] is optional___ and will be created if not found in the same directory as the provided gamesave file. The `signa.tur` file is used to store the signature for the corresponding gamesave found in the [SaveID] folder.

------

#### Gamesave location:
> /UDATA/53430005/[SaveID]/`*.*`

<details>
<summary>View 4 known file names</summary>

```
*.rbr
*.rst
*.rpl
signa.tur
```

</details>

------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### XSavSig

__WARNING: XSavSig cannot support signing for this game because the gamesave signature is stored in a seperate file. XSavSig does not support accessing multiple files at once.__

<br>

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"
```
[53430005]
Title=Richard Burns Rally
SigKey=BFD9EF83979291CEE2FBB44E03EAD982
AuthKey=62FB7AB9D9A469B9A6165CCB58E57BEF
```
