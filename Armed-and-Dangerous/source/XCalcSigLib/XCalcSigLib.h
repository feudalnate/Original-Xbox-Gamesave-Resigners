#pragma once
#ifndef XCALCSIG
#define XCALCSIG

#include "Data\Types.h"
#ifndef _STRING_H_
//#include "Data\Functions.h"
#endif
#include "SHA1\SHA1.h"
#include "HMAC\HMACSHA1.h"

//flag values (not really used as flags from what I've seen, more so enum values)
#define XCALCSIG_FLAG_SAVE_GAME		0x00000000 //hmac-sha1 roamable - TitleSignatureKey signed content
#define XCALCSIG_FLAG_NON_ROAMABLE	0x00000001 //hmac-sha1 non-roamable - TitleSignatureKey & XboxHDKey signed content
#define XCALCSIG_FLAG_CONTENT		0x00000002 //basic sha1
#define XCALCSIG_FLAG_DIGEST		0x00000004 //basic sha1
#define XCALCSIG_FLAG_ONLINE		0x00000008 //unsupported (for now)

//return values (not present in the official XCalcSig class)
#define XCALCSIG_ERROR				0x00000000 //error result
#define XCALCSIG_SUCCESS			0x00000001 //success result

//data blob sizes
#define XCALCSIG_KEY_SIZE			0x00000010
#define XCALCSIG_SIGNATURE_SIZE		0x00000014
#define XCALCSIG_HASH_SIZE			0x00000014
#define XONLINE_SIGNATURE_SIZE		0x00000064

/*

	NOTE: Original structure of the XCALCSIG_CONTEXT

	124 bytes (0x7C) is allocated for this structure
	
typedef struct {
	//input flags passed to XCalculateSignatureBegin(DWORD dwFlags)
	DWORD dwFlags;

	//pointer to XboxSignatureKey or AlternateSignatureKey grabbed from the certificate of the executable (XBE) currently running in memory
	//by default XboxSignatureKey is used when XCalculateSignatureBegin(DWORD dwFlags) is called
	//if XCalculateSignatureBeginEx(DWORD dwFlags, DWORD dwAltTitleId) is used, an AlternatedSignatureKey is selected based on the TitleId specified
	//(ex: if TitleId[2] then use AlternateSignatureKey[2])
	DWORD pSignatureKey;

	//block of memory used to hold SHA1 state 
	SHA1CTX SHA1CONTEXT;
} XCALCSIG_CONTEXT, *PXCALCSIG_CONTEXT;
*/

/// <summary>
/// Improvised XCALCSIG_CONTEXT structure more suitable for use outside the Xbox runtime.
/// 
/// Initialization and destruction of this context is handled by XCalculateSignatureBegin() and XCalculateSignatureEnd() respectively
/// </summary>
typedef struct {
	u32 dwFlags;
	byte* pSignatureKey;
	byte* pXboxHDKey;
	sha1_context* pShaContext;
} XCALCSIG_CONTEXT, *PXCALCSIG_CONTEXT;


/*

	NOTE: Original function signatures (roughly)

	Can't really use these in their original form
	XboxHDKey and TitleSignatureKey(s) are in memory ready for use by the running title

	We need to pass these keys explicitly to the functions instead

PXCALCSIG_CONTEXT XCalculateSignatureBegin(unsigned int dwFlags);
PXCALCSIG_CONTEXT XCalculateSignatureBeginEx(unsigned int dwFlags, unsigned int dwAltTitleId);

unsigned int XCalculateSignatureUpdate(PXCALCSIG_CONTEXT pCalcSig, void* pbData, unsigned int cbData);

//pbSignature _might_ be another structure (references to XCALCSIG_SIGNATURE, don't know if it's anything more than a struct holding a pointer to block of memory)
unsigned int XCalculateSignatureEnd(PXCALCSIG_CONTEXT pCalcSig, void* pbSignature); 
*/


/// <summary>
/// Returns size (in bytes) of a signature the given flag will produce
/// </summary>
/// <param name="dwFlags">Flag to specific the signature type to generate</param>
/// <returns>Size of signature (in bytes)</returns>
u32 XCalculateSignatureGetSize(u32 dwFlags);

/// <summary>
/// Creates and returns context based on the given flag
/// </summary>
/// <param name="dwFlags">Flag to specific the signature type to generate</param>
/// <returns>On success, returns pointer to an initialized context. On error, returns NULL</returns>
PXCALCSIG_CONTEXT XCalculateSignatureBegin(u32 dwFlags);

/// <summary>
/// Creates and returns context based on the given flag and key
/// </summary>
/// <param name="dwFlags">Flag to specific the signature type to generate</param>
/// <param name="pbTitleSignatureKey">Unique per-title key (0x10 bytes). TitleSignatureKey/AlternateTitleKey is stored in the XBE certificate of a given titl</param>
/// <returns>On success, returns pointer to an initialized context. On error, returns NULL</returns>
PXCALCSIG_CONTEXT XCalculateSignatureBegin(u32 dwFlags, byte* pbTitleSignatureKey);

/// <summary>
/// Creates and returns context based on the given flag and keys
/// </summary>
/// <param name="dwFlags">Flag to specific the signature type to generate</param>
/// <param name="pbTitleSignatureKey">Unique per-title key (0x10 bytes). TitleSignatureKey/AlternateTitleKey is stored in the XBE certificate of a given title</param>
/// <param name="pbXboxHDKey">Unique per-console key (0x10 bytes). XboxHDKey is stored in the EEPROM data</param>
/// <returns>On success, returns pointer to an initialized XCALCSIG_CONTEXT. On error, returns NULL</returns>
PXCALCSIG_CONTEXT XCalculateSignatureBegin(u32 dwFlags, byte* pbTitleSignatureKey, byte* pbXboxHDKey);

/// <summary>
/// Update signature generation with specified input data
/// </summary>
/// <param name="pContext">Pointer to an initialized XCALCSIG_CONTEXT</param>
/// <param name="pbData">Pointer to data block to include in signature generation</param>
/// <param name="cbData">Number of bytes in pbData to include in signature generation</param>
/// <returns>On success, returns XCALCSIG_SUCCESS. On error, returns XCALCSIG_ERROR</returns>
u32 XCalculateSignatureUpdate(PXCALCSIG_CONTEXT pContext, byte* pbData, u32 cbData);

/// <summary>
/// Finalizes signature generation and destroys context
/// </summary>
/// <param name="pContext">Pointer to an initialized XCALCSIG_CONTEXT</param>
/// <param name="pbSignature">Pointer to buffer to store resulting signature</param>
/// <returns>On success, returns XCALCSIG_SUCCESS. On error, returns XCALCSIG_ERROR. Destroys context regardless of result</returns>
u32 XCalculateSignatureEnd(PXCALCSIG_CONTEXT &pContext, byte* pbSignature);

#endif