#pragma once

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Far Cry Instincts
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530008
Signature Key: 2FF20BB65D72ED5D46A2A2D625E1A625
*/

#define INFO_GAME_NAME "Far Cry Instincts\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "55530008\0"

#define INFO_USAGE "fcisign <file> [file2]\n\nNOTE: [file2] is expected to be a \"*.sig\" file. [file2] is optional when signing a map file and will be created/overwritten automatically if not specified.\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
bool GenerateRoamableSignature(byte* buffer, u32 length, byte* TitleSignatureKey, byte* signature);
bool GenerateMapSignature(byte* map_data, u32 map_data_len, byte* TitleSignatureKey, byte* signature);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
bool SplitFilePath(utf8* in_file_path, utf8* out_file_name, u32& out_file_name_length, utf8* out_directory_path, u32& out_directory_path_length, bool trim_trailing_seperator);
bool CombineFilePath(utf8* in_directory_path, utf8* in_file_name, utf8* out_file_path, u32& out_file_path_length);