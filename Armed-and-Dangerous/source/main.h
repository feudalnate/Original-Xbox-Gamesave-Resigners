#pragma once
#include <stdlib.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Armed & Dangerous
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4C41000D
Signature Key: 2B6E33422A6AEC5A41E4A77E6882201A
*/

/*
"options.opt" file format

-------------------------------------------------------------------------------------------------
| Offset  | Length | Data type | Description                                                    |
-------------------------------------------------------------------------------------------------
| 0x0     | 0x14   | byte      | Non-roamable signature (HMAC-SHA1) (covers 0x18-EOF)           |
| 0x14    | 0x4    | uint32    | Decompressed file size                                         |
| 0x18    | 0x2    | byte      | ZLIB magic/flag (0x78 0xDA) (BEST_COMPRESSION)                 |
| 0x1A    | ???    | byte      | Compressed data, end of compressed data marked with null byte  |
| EOF-0x4 | 0x4    | uint32    | Adler32 checksum of decompressed data                          |
-------------------------------------------------------------------------------------------------

Note: "Decompressed file size" isn't covered by the Non-roamable signature (for some reason)
*/

#define INFO_GAME_NAME "Armed & Dangerous\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "4C41000D\0"

#define INFO_USAGE "aadsign <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
