#include "Data\Types.h"
#include "Data\Functions.h"
#include "Data\Hexadecimal.h"
#include "Data\FileIO.h"
#include "XCalcSigLib\XCalcSigLib.h"

/*
Game: Burnout 3: Takedown
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4541005B
Signature Key: 8F4BC9B5D6B01E7F4772C5ACE04BC922
*/

const byte TitleSignatureKey[XCALCSIG_KEY_SIZE] = { 0x8F, 0x4B, 0xC9, 0xB5, 0xD6, 0xB0, 0x1E, 0x7F, 0x47, 0x72, 0xC5, 0xAC, 0xE0, 0x4B, 0xC9, 0x22 };

#define INFO_GAME_NAME "Burnout 3: Takedown\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / PAL / NTSC-J\0"
#define INFO_TITLE_ID "4541005B\0"
#define INFO_USAGE "b3sign <XboxHDKey> <file>\0"
#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
bool CheckXboxHDKey(utf7* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);