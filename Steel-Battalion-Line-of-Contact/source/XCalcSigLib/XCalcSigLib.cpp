#include "XCalcSigLib.h"


/*

	NOTE: All these function signatures have been cleaned up for readability, may not be 1:1 with actual variable/reference types/names


	NOTE: Private functions

	//--------------------------------------------------------------------------------------------------------------------------------
	//Block-based HMAC-SHA-1
	//--------------------------------------------------------------------------------------------------------------------------------
	void XShaHmacInitialize(void* pbKey, unsigned int cbKey, PSHACTX pShaContext)
	void XShaHmacUpdate(PSHACTX pShaContext, void* pbData, unsigned int cbData)
	void XShaHmacComputeFinal(PSHACTX pShaContext, void *pbKey, unsigned int cbKey, void *pbHmac)

	//--------------------------------------------------------------------------------------------------------------------------------
	//Converts roamable signature type to non-roamable signature type
	//--------------------------------------------------------------------------------------------------------------------------------
	bool XapiConvertSignatureToNonRoamable(PXCALCSIG_CONTEXT pCalcSig, void* pSignatureRoamable, void* pSignatureNonRoamable)

	//--------------------------------------------------------------------------------------------------------------------------------
	//Gamesave hashing functions. Used with XCALCSIG_FLAG_SAVE_GAME and XCALCSIG_FLAG_NON_ROAMABLE flags
	//--------------------------------------------------------------------------------------------------------------------------------
	unsigned int XapipCalculateSaveGameSignatureBegin(unsigned int dwFlags, unsigned int dwAltTitleId)
	unsigned int XapipCalculateSaveGameSignatureUpdate(PXCALCSIG_CONTEXT pCalcSig, void* pbData, unsigned int cbData)
	unsigned int XapipCalculateSaveGameSignatureEnd(PXCALCSIG_CONTEXT pCalcSig, void* pbSignature)

	//--------------------------------------------------------------------------------------------------------------------------------
	//Content hashing functions. Used with XCALCSIG_FLAG_CONTENT and XCALCSIG_FLAG_DIGEST flags
	//--------------------------------------------------------------------------------------------------------------------------------
	unsigned int XapipCalculateContentSignatureBegin()
	unsigned int XapipCalculateContentSignatureUpdate(PXCALCSIG_CONTEXT pCalcSig, void* pbData, unsigned int cbData)
	unsigned int XapipCalculateContentSignatureEnd(PXCALCSIG_CONTEXT pCalcSig, void* pbSignature)



	NOTE: Public functions
	
	PXCALCSIG_CONTEXT XCalculateSignatureBegin(unsigned int dwFlags)
	PXCALCSIG_CONTEXT XCalculateSignatureBeginEx(unsigned int dwFlags, unsigned int dwAltTitleId)
	unsigned int XCalculateSignatureUpdate(PXCALCSIG_CONTEXT pCalcSig, void* pbData, unsigned int cbData)
	unsigned int XCalculateSignatureEnd(PXCALCSIG_CONTEXT pCalcSig, void* pbSignature)

*/

#pragma region "Private XAPI functions"

/*

	NOTE: These XAPI calls aren't really necessary outside the Xbox runtime (see xcalcsig_decomp.cpp). They are used to allocate/fetch/process data that we can simply provide or process upfront


u32 XapiConvertSignatureToNonRoamable(PXCALCSIG_CONTEXT pContext, byte* pbSignature) {

	if (pContext &&pContext->pShaContext && pContext->pXboxHDKey && pbSignature) {
		
		hmacsha1_init(pContext->pShaContext, pContext->pXboxHDKey, XCALCSIG_KEY_SIZE);
		hmacsha1_update(pContext->pShaContext, pbSignature, XCALCSIG_SIGNATURE_SIZE);
		hmacsha1_final(pContext->pShaContext, pContext->pXboxHDKey, XCALCSIG_KEY_SIZE, pbSignature);

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

u32 XapipCalculateSaveGameSignatureBegin(PXCALCSIG_CONTEXT pContext) {

	if (pContext && pContext->pShaContext && pContext->pSignatureKey) {

		hmacsha1_init(pContext->pShaContext, pContext->pSignatureKey, XCALCSIG_KEY_SIZE);

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

u32 XapipCalculateSaveGameSignatureUpdate(PXCALCSIG_CONTEXT pContext, byte* pbData, u32 cbData) {

	if (pContext && pContext->pShaContext && pbData && cbData > 0) {

		hmacsha1_update(pContext->pShaContext, pbData, cbData);

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

u32 XapipCalculateSaveGameSignatureEnd(PXCALCSIG_CONTEXT pContext, byte* pbSignature) {

	if (pContext && pContext->pShaContext && pbSignature) {

		hmacsha1_final(pContext->pShaContext, pContext->pSignatureKey, XCALCSIG_KEY_SIZE, pbSignature);

		if (pContext->dwFlags == XCALCSIG_FLAG_NON_ROAMABLE) {

			if (!XapiConvertSignatureToNonRoamable(pContext, pbSignature))
				return XCALCSIG_ERROR;
		}

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

u32 XapipCalculateContentSignatureBegin(PXCALCSIG_CONTEXT pContext) {

	if (pContext && pContext->pShaContext) {

		sha1_init(pContext->pShaContext);

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

u32 XapipCalculateContentSignatureUpdate(PXCALCSIG_CONTEXT pContext, byte* pbData, u32 cbData) {

	if (pContext && pContext->pShaContext && pbData && cbData > 0) {

		sha1_update(pContext->pShaContext, pbData, cbData);

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

u32 XapipCalculateContentSignatureEnd(PXCALCSIG_CONTEXT pContext, byte* pbSignature) {

	if (pContext && pContext->pShaContext && pbSignature) {

		sha1_final(pContext->pShaContext, pbSignature);

		return XCALCSIG_SUCCESS;
	}

	return XCALCSIG_ERROR;
}

*/

#pragma endregion

u32 XCalculateSignatureGetSize(u32 dwFlags) {

	if (dwFlags <= XCALCSIG_FLAG_CONTENT || dwFlags == XCALCSIG_FLAG_DIGEST)
		return XCALCSIG_SIGNATURE_SIZE;

	if (dwFlags == XCALCSIG_FLAG_ONLINE)
		return XONLINE_SIGNATURE_SIZE;

	return 0;
}

PXCALCSIG_CONTEXT XCalculateSignatureBegin(u32 dwFlags) {

	if (dwFlags == XCALCSIG_FLAG_CONTENT || dwFlags == XCALCSIG_FLAG_DIGEST || dwFlags == XCALCSIG_FLAG_ONLINE)
		return XCalculateSignatureBegin(dwFlags, 0, 0);

	return 0;
}

PXCALCSIG_CONTEXT XCalculateSignatureBegin(u32 dwFlags, byte* pbTitleSignatureKey) {

	if (dwFlags == XCALCSIG_FLAG_SAVE_GAME || dwFlags == XCALCSIG_FLAG_CONTENT || dwFlags == XCALCSIG_FLAG_DIGEST || dwFlags == XCALCSIG_FLAG_ONLINE)
		return XCalculateSignatureBegin(dwFlags, pbTitleSignatureKey, 0);

	return 0;
}

PXCALCSIG_CONTEXT XCalculateSignatureBegin(u32 dwFlags, byte* pbTitleSignatureKey, byte* pbXboxHDKey) {

	/*
		SELF-NOTE(feudalnate): Should key length(s) be required here?

		Also, the context initialization could be simplified but favoring sanity checks for now
	*/

	PXCALCSIG_CONTEXT pContext = 0;

	if (dwFlags == XCALCSIG_FLAG_SAVE_GAME || dwFlags == XCALCSIG_FLAG_NON_ROAMABLE) {

		static byte XboxCERTKey[XCALCSIG_KEY_SIZE] = { 0x5C, 0x07, 0x33, 0xAE, 0x04, 0x01, 0xF7, 0xE8, 0xBA, 0x79, 0x93, 0xFD, 0xCD, 0x2F, 0x1F, 0xE0 };

		//temp buffer to store hash of TitleSignatureKey (aka "authkey"), the _real_ signing key
		byte* pTempHash = new byte[XCALCSIG_HASH_SIZE];

		if (dwFlags == XCALCSIG_FLAG_SAVE_GAME && pbTitleSignatureKey) {
			pContext = new XCALCSIG_CONTEXT;
			pContext->dwFlags = dwFlags;
			pContext->pShaContext = new sha1_context;
			pContext->pSignatureKey = new byte[XCALCSIG_KEY_SIZE];
			pContext->pXboxHDKey = 0;

			hmacsha1_init(pContext->pShaContext, XboxCERTKey, XCALCSIG_KEY_SIZE);
			hmacsha1_update(pContext->pShaContext, pbTitleSignatureKey, XCALCSIG_KEY_SIZE);
			hmacsha1_final(pContext->pShaContext, XboxCERTKey, XCALCSIG_KEY_SIZE, pTempHash);
			copy(pContext->pSignatureKey, pTempHash, XCALCSIG_KEY_SIZE);

			hmacsha1_init(pContext->pShaContext, pContext->pSignatureKey, XCALCSIG_KEY_SIZE);
		}

		if (dwFlags == XCALCSIG_FLAG_NON_ROAMABLE && pbTitleSignatureKey && pbXboxHDKey) {
			pContext = new XCALCSIG_CONTEXT;
			pContext->dwFlags = dwFlags;
			pContext->pShaContext = new sha1_context;
			pContext->pSignatureKey = new byte[XCALCSIG_KEY_SIZE];
			pContext->pXboxHDKey = pbXboxHDKey;

			hmacsha1_init(pContext->pShaContext, XboxCERTKey, XCALCSIG_KEY_SIZE);
			hmacsha1_update(pContext->pShaContext, pbTitleSignatureKey, XCALCSIG_KEY_SIZE);
			hmacsha1_final(pContext->pShaContext, XboxCERTKey, XCALCSIG_KEY_SIZE, pTempHash);
			copy(pContext->pSignatureKey, pTempHash, XCALCSIG_KEY_SIZE);

			hmacsha1_init(pContext->pShaContext, pContext->pSignatureKey, XCALCSIG_KEY_SIZE);
		}

		delete[] pTempHash;

	}
	else if (dwFlags == XCALCSIG_FLAG_CONTENT || dwFlags == XCALCSIG_FLAG_DIGEST) {
		pContext = new XCALCSIG_CONTEXT;
		pContext->dwFlags = dwFlags;
		pContext->pShaContext = new sha1_context;
		pContext->pSignatureKey = 0;
		pContext->pXboxHDKey = 0;

		sha1_init(pContext->pShaContext);
	}
	else if (dwFlags == XCALCSIG_FLAG_ONLINE) {

		/*
			NOTE: Unsupported (for now)
		*/

		//pContext = g_pfnxcsbOnline(XCALCSIG_FLAG_ONLINE); //where is this?
	}

	return pContext;
}

u32 XCalculateSignatureUpdate(PXCALCSIG_CONTEXT pContext, byte* pbData, u32 cbData) {

	if (pContext && pContext->pShaContext && pbData && cbData > 0) {

		if (pContext->dwFlags == XCALCSIG_FLAG_SAVE_GAME || pContext->dwFlags == XCALCSIG_FLAG_NON_ROAMABLE) {
			
			//return XapipCalculateSaveGameSignatureUpdate(pContext, pbData, cbData);

			hmacsha1_update(pContext->pShaContext, pbData, cbData);
			return XCALCSIG_SUCCESS;
		}
		else if (pContext->dwFlags == XCALCSIG_FLAG_CONTENT || pContext->dwFlags == XCALCSIG_FLAG_DIGEST) {

			//return XapipCalculateContentSignatureUpdate(pContext, pbData, cbData);

			sha1_update(pContext->pShaContext, pbData, cbData);
			return XCALCSIG_SUCCESS;
		}
		else if (pContext->dwFlags == XCALCSIG_FLAG_ONLINE) {

			/*
				NOTE: Unsupported (for now)
			*/

			//g_pfnxcsuOnline(pContext, pbData, cbData); //where is this?
			//return XCALCSIG_SUCCESS;
		}

	}

	return XCALCSIG_ERROR;
}

u32 XCalculateSignatureEnd(PXCALCSIG_CONTEXT& pContext, byte* pbSignature) {

	u32 result = XCALCSIG_ERROR;

	if (pContext && pContext->pShaContext && pbSignature) {

		if (pContext->dwFlags == XCALCSIG_FLAG_SAVE_GAME && pContext->pSignatureKey) {

			hmacsha1_final(pContext->pShaContext, pContext->pSignatureKey, XCALCSIG_KEY_SIZE, pbSignature);
			result = XCALCSIG_SUCCESS;
		}
		else if (pContext->dwFlags == XCALCSIG_FLAG_NON_ROAMABLE && pContext->pSignatureKey && pContext->pXboxHDKey) {

			hmacsha1_final(pContext->pShaContext, pContext->pSignatureKey, XCALCSIG_KEY_SIZE, pbSignature); //roamable result

			hmacsha1_init(pContext->pShaContext, pContext->pXboxHDKey, XCALCSIG_KEY_SIZE);
			hmacsha1_update(pContext->pShaContext, pbSignature, XCALCSIG_SIGNATURE_SIZE);
			hmacsha1_final(pContext->pShaContext, pContext->pXboxHDKey, XCALCSIG_KEY_SIZE, pbSignature);

			//result = XapiConvertSignatureToNonRoamable(pContext, pbSignature);
			result = XCALCSIG_SUCCESS;
		}
		else if (pContext->dwFlags == XCALCSIG_FLAG_CONTENT || pContext->dwFlags == XCALCSIG_FLAG_DIGEST) {

			sha1_final(pContext->pShaContext, pbSignature);
			result = XCALCSIG_SUCCESS;

		}
		else if (pContext->dwFlags == XCALCSIG_FLAG_ONLINE) {

			/*
				NOTE: Unsupported (for now)
			*/

			//g_pfnxcseOnline(hCalcSig, pbSignature); //where is this?
			//result = XCALCSIG_SUCCESS;

			//delete pContext->pShaContext;
			//delete pContext;

		}

	}

	//clean up context no matter the result
	if (pContext) {

		if (pContext->pShaContext)
			delete pContext->pShaContext;

		if (pContext->pSignatureKey)
			delete[] pContext->pSignatureKey;

		delete pContext;
		pContext = 0; //no double deletes please
	}

	return result;
}