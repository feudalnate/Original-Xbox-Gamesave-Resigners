#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Richard Burns Rally
Region: PAL
TitleID: 0x53430005
Signature Key: BFD9EF83979291CEE2FBB44E03EAD982
*/

#define INFO_GAME_NAME "Richard Burns Rally\0"
#define INFO_SUPPORTED_REGIONS "PAL\0"
#define INFO_TITLE_ID "53430005\0"

#define INFO_USAGE "rbrsign <XboxHDKey> <file> [file2]\n\nNOTE: [file2] is expected to be the \"signa.tur\" file. [file2] is optional and will be created/overwritten automatically if not specified.\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
bool32 GetContainingDirectory(utf8* in_file_path, utf8* out_directory_path, u32& out_directory_path_length, bool32 trim_trailing_seperator);