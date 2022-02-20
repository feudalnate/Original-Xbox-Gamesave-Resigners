# Armed and Dangerous Re-signer


### Usage (command line):
> aadsign.exe [XboxHDKey] [file]

------

#### Gamesave location:
> /UDATA/4C41000D/[SaveID]/`options.opt`

------

#### XboxHDKey (per-console key)

* [Retrieve the XboxHDKey from a **Xbox** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox)
* [Retrieve the XboxHDKey from a **Xbox 360** ](https://github.com/feudalnate/Original-Xbox-Gamesave-Resigners/blob/master/XboxHDKey.md#retrieving-the-xboxhdkey-from-the-xbox-360)

------

#### File format (`options.opt`)


| Offset  | Length | Data type | Description                                                    |
|---------|--------|-----------|----------------------------------------------------------------|
| 0x0     | 0x14   | byte      | Non-roamable signature (HMAC-SHA1) (covers 0x18-EOF)           |
| 0x14    | 0x4    | uint32    | Decompressed file size                                         |
| 0x18    | 0x2    | byte      | ZLIB magic/flag (0x78 0xDA) (BEST_COMPRESSION)                 |
| 0x1A    | ???    | byte      | Compressed data, end of compressed data marked with null byte  |
| EOF-0x4 | 0x4    | uint32    | Adler32 checksum of decompressed data                          |

------

#### XSavSig

> Add your XboxHDKey to "xbhddkey.ini"

> Add entry to "resign.ini"
```
[4C41000D]
Title=Armed & Dangerous
SigKey=2B6E33422A6AEC5A41E4A77E6882201A
AuthKey=EB8174CA524C095806C7CADCEC3B8A5B
DataFile=options.opt
SigOffset=0
SigType=NoRoam
DataOffset=24
```
