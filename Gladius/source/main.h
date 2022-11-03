#include "Data\Types.h"
#include "Data\Functions.h"
#include "Data\Hexadecimal.h"
#include "Data\FileIO.h"
#include "XCalcSigLib\XCalcSigLib.h"

/*
Game: Gladius
Region: NTSC-U / PAL
TitleID: 0x4C410008
Signature Key: 48A73E2F85CF76F105EE68AC96231B2B
*/

const byte TitleSignatureKey[XCALCSIG_KEY_SIZE] = { 0x48, 0xA7, 0x3E, 0x2F, 0x85, 0xCF, 0x76, 0xF1, 0x05, 0xEE, 0x68, 0xAC, 0x96, 0x23, 0x1B, 0x2B };

#define INFO_GAME_NAME "Gladius\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / PAL\0"
#define INFO_TITLE_ID "4C410008\0"
#define INFO_USAGE "gladsign <file>\0"
#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);