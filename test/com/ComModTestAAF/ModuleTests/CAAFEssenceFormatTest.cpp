// @doc INTERNAL
// @com This file implements the module test for CAAFEssenceFormat
/***********************************************************************
 *
 *              Copyright (c) 1998-1999 Avid Technology, Inc.
 *
 * Permission to use, copy and modify this software and accompanying 
 * documentation, and to distribute and sublicense application software
 * incorporating this software for any purpose is hereby granted, 
 * provided that (i) the above copyright notice and this permission
 * notice appear in all copies of the software and related documentation,
 * and (ii) the name Avid Technology, Inc. may not be used in any
 * advertising or publicity relating to the software without the specific,
 * prior written permission of Avid Technology, Inc.
 *
 * THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL AVID TECHNOLOGY, INC. BE LIABLE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, PUNITIVE, INDIRECT, ECONOMIC, CONSEQUENTIAL OR
 * OTHER DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE AND
 * ACCOMPANYING DOCUMENTATION, INCLUDING, WITHOUT LIMITATION, DAMAGES
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, AND WHETHER OR NOT
 * ADVISED OF THE POSSIBILITY OF DAMAGE, REGARDLESS OF THE THEORY OF
 * LIABILITY.
 *
 ************************************************************************/

#include "AAF.h"

#include <iostream.h>
#include <stdio.h>

#include "AAFStoredObjectIDs.h"
#include "AAFResult.h"
#include "AAFDataDefs.h"
#include "AAFCodecDefs.h"
#include "AAFContainerDefs.h"
#include "AAFDefUIDs.h"
#include "AAFEssenceFormats.h"

#include "CAAFBuiltinDefs.h"

#define	MobName			L"MasterMOBTest"
//#define	NumMobSlots		3

//static aafWChar* Manufacturer = L"Sony";
//static aafWChar* Model = L"MyModel";
//static aafTapeCaseType_t FormFactor = kVHSVideoTape;
//static aafVideoSignalType_t VideoSignalType = kPALSignal;
//static aafTapeFormatType_t TapeFormat = kVHSFormat;
//static aafLength_t TapeLength = 3200 ;

static aafMobID_t		NewMobID;
//#define TAPE_MOB_OFFSET	10
//#define TAPE_MOB_LENGTH	60
//#define TAPE_MOB_NAME	L"A Tape Mob"

// Cross-platform utility to delete a file.
static void RemoveTestFile(const wchar_t* pFileName)
{
	const size_t kMaxFileName = 512;
	char cFileName[kMaxFileName];
	
	size_t status = wcstombs(cFileName, pFileName, kMaxFileName);
	if (status != (size_t)-1)
	{ // delete the file.
		remove(cFileName);
	}
}

// convenient error handlers.
inline void checkResult(HRESULT r)
{
	if (FAILED(r))
		throw r;
}
inline void checkExpression(bool expression, HRESULT r)
{
	if (!expression)
		throw r;
}

static HRESULT OpenAAFFile(aafWChar*			pFileName,
						   aafMediaOpenMode_t	mode,
						   IAAFFile**			ppFile,
						   IAAFHeader**			ppHeader)
{
	aafProductIdentification_t	ProductInfo;
	HRESULT						hr = AAFRESULT_SUCCESS;
	
	ProductInfo.companyName = L"AAF Developers Desk";
	ProductInfo.productName = L"AAFEssenceFormat Test";
	ProductInfo.productVersion.major = 1;
	ProductInfo.productVersion.minor = 0;
	ProductInfo.productVersion.tertiary = 0;
	ProductInfo.productVersion.patchLevel = 0;
	ProductInfo.productVersion.type = kVersionUnknown;
	ProductInfo.productVersionString = NULL;
	ProductInfo.productID = UnitTestProductID;
	ProductInfo.platform = NULL;
	
	*ppFile = NULL;
	
	switch (mode)
	{
	case kMediaOpenReadOnly:
		hr = AAFFileOpenExistingRead(pFileName, 0, ppFile);
		break;
		
	case kMediaOpenAppend:
		hr = AAFFileOpenNewModify(pFileName, 0, &ProductInfo, ppFile);
		break;
		
	default:
		hr = AAFRESULT_TEST_FAILED;
		break;
	}
	
	if (FAILED(hr))
	{
		if (*ppFile)
		{
			(*ppFile)->Release();
			*ppFile = NULL;
		}
		return hr;
	}
	
	hr = (*ppFile)->GetHeader(ppHeader);
	if (FAILED(hr))
	{
		(*ppFile)->Release();
		*ppFile = NULL;
		return hr;
	}
	
	return hr;
}

static HRESULT CreateAAFFile(aafWChar * pFileName)
{
	IAAFFile*			pFile = NULL;
	bool				bFileOpen = false;
	IAAFHeader *        pHeader = NULL;
	IAAFDictionary*		pDictionary = NULL;
	IAAFMob*			pMob = NULL;
	IAAFMasterMob*		pMasterMob = NULL;
	IAAFEssenceAccess	*pAccess = NULL;
	IAAFEssenceFormat	*pFormat = NULL;
	HRESULT				hr = S_OK;
	aafRational_t		rate = { 44100, 1 };
	aafInt32			numSpec, writeValue, readValue, bytesRead;
	aafRational_t		writeRat, readRat;
	aafUID_t			readCode;

	try
	{
		// Remove the previous test file if any.
		RemoveTestFile(pFileName);
		
		
		// Create the AAF file
		checkResult(OpenAAFFile(pFileName, kMediaOpenAppend, /*&pSession,*/ &pFile, &pHeader));
		bFileOpen = true;
		
		// Get the AAF Dictionary so that we can create valid AAF objects.
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs (pDictionary);
				
		// Create a Master Mob
		checkResult(pDictionary->CreateInstance(defs.cdMasterMob(),
			IID_IAAFMob, 
			(IUnknown **)&pMob));
		
		// Set the IAAFMob properties
		checkResult(CoCreateGuid((GUID *)&NewMobID));
		aafMobID_t NewMobAUID;
		memcpy (&NewMobAUID, &NewMobID, sizeof (NewMobID));
		checkResult(pMob->SetMobID(NewMobAUID));
		checkResult(pMob->SetName(MobName));
		
		checkResult(pMob->QueryInterface(IID_IAAFMasterMob, (void **) &pMasterMob));
		// Add the master mob to the file BEFORE creating the essence
		checkResult(pHeader->AddMob(pMob));
		checkResult(pMasterMob->CreateEssence (1,
											   defs.ddSound(),
											   CodecWave,
											   rate,
											   rate,
											   kSDKCompressionDisable,
											   NULL,
											   ContainerAAF,
											   &pAccess));
		
		// Fianlly! Get an essence format to test
		checkResult(pAccess->GetEmptyFileFormat(&pFormat));
		checkResult(pFormat->NumFormatSpecifiers(&numSpec));
		checkExpression(0 == numSpec, AAFRESULT_TEST_FAILED);
		
		/***/
		writeValue = 16;
		checkResult(pFormat->AddFormatSpecifier(kAAFAudioSampleBits,
												sizeof(writeValue), (aafDataBuffer_t)&writeValue));
		writeValue = 1;
		checkResult(pFormat->AddFormatSpecifier(kAAFNumChannels,
												sizeof(writeValue), (aafDataBuffer_t)&writeValue));
		writeRat.numerator = 44100;
		writeRat.denominator = 1;
		checkResult(pFormat->AddFormatSpecifier(kAAFSampleRate,
												sizeof(writeRat), (aafDataBuffer_t)&writeRat));
		/***/
		checkResult(pFormat->NumFormatSpecifiers(&numSpec));
		checkExpression(3 == numSpec, AAFRESULT_TEST_FAILED);

		/***/
		checkResult(pFormat->GetFormatSpecifier (kAAFAudioSampleBits,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead));
		checkExpression(sizeof(readValue) == bytesRead, AAFRESULT_TEST_FAILED);
		checkExpression(16 == readValue, AAFRESULT_TEST_FAILED);
		/***/
		checkResult(pFormat->GetFormatSpecifier (kAAFNumChannels,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead));
		checkExpression(sizeof(readValue) == bytesRead, AAFRESULT_TEST_FAILED);
		checkExpression(1 == readValue, AAFRESULT_TEST_FAILED);
		/***/
		checkResult(pFormat->GetFormatSpecifier (kAAFSampleRate,
  												sizeof(readRat), (aafDataBuffer_t)&readRat,
												&bytesRead));
		checkExpression(sizeof(readRat) == bytesRead, AAFRESULT_TEST_FAILED);
		checkExpression(44100 == readRat.numerator, AAFRESULT_TEST_FAILED);
		checkExpression(1 == readRat.denominator, AAFRESULT_TEST_FAILED);
		/***/

		//******* Test indexed calls
		/***/
		checkResult(pFormat->GetIndexedFormatSpecifier (0, &readCode,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead));
		checkExpression(memcmp(&readCode,&kAAFAudioSampleBits, sizeof(readCode)) == 0, AAFRESULT_TEST_FAILED);
		checkExpression(sizeof(readValue) == bytesRead, AAFRESULT_TEST_FAILED);
		checkExpression(16 == readValue, AAFRESULT_TEST_FAILED);
		/***/
		checkResult(pFormat->GetIndexedFormatSpecifier (1, &readCode,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead));
		checkExpression(memcmp(&readCode,&kAAFNumChannels, sizeof(readCode)) == 0, AAFRESULT_TEST_FAILED);
		checkExpression(sizeof(readValue) == bytesRead, AAFRESULT_TEST_FAILED);
		checkExpression(1 == readValue, AAFRESULT_TEST_FAILED);
		/***/
		checkResult(pFormat->GetIndexedFormatSpecifier (2, &readCode,
  												sizeof(readRat), (aafDataBuffer_t)&readRat,
												&bytesRead));
		checkExpression(memcmp(&readCode,&kAAFSampleRate, sizeof(readCode)) == 0, AAFRESULT_TEST_FAILED);
		checkExpression(sizeof(readRat) == bytesRead, AAFRESULT_TEST_FAILED);
		checkExpression(44100 == readRat.numerator, AAFRESULT_TEST_FAILED);
		checkExpression(1 == readRat.denominator, AAFRESULT_TEST_FAILED);
		/***/
		//******* Test indexed calls out of range
		checkExpression(pFormat->GetIndexedFormatSpecifier (-1, &readCode,
  												sizeof(readRat), (aafDataBuffer_t)&readRat,
												&bytesRead) == AAFRESULT_FORMAT_BOUNDS, AAFRESULT_TEST_FAILED);
		checkExpression(pFormat->GetIndexedFormatSpecifier (3, &readCode,
  												sizeof(readRat), (aafDataBuffer_t)&readRat,
												&bytesRead) == AAFRESULT_FORMAT_BOUNDS, AAFRESULT_TEST_FAILED);
		//******* Test indexed calls small buffer size
		checkExpression(pFormat->GetIndexedFormatSpecifier (2, &readCode,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead) == AAFRESULT_SMALLBUF, AAFRESULT_TEST_FAILED);
		//******* Test ID calls small buffer size
		checkExpression(pFormat->GetFormatSpecifier (kAAFSampleRate,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead) == AAFRESULT_SMALLBUF, AAFRESULT_TEST_FAILED);
		//******* Test ID calls missing ID
		checkExpression(pFormat->GetFormatSpecifier (kAAFSampleFormat,
  												sizeof(readValue), (aafDataBuffer_t)&readValue,
												&bytesRead) == AAFRESULT_FORMAT_NOT_FOUND, AAFRESULT_TEST_FAILED);

		pAccess->CompleteWrite();
		pAccess->Release();
		pAccess = NULL;

	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	
	// Cleanup and return	
	if (pAccess)
		pAccess->Release();
	
	if (pMasterMob)
		pMasterMob->Release();
	
	if (pMob)
		pMob->Release();
	
	if (pDictionary)
		pDictionary->Release();
	
	if (pHeader)
		pHeader->Release();
	
	if (pFormat)
		pFormat->Release();
	
	if (pFile)
	{  // Close file
		if (bFileOpen)
		{
			pFile->Save();
			pFile->Close();
		}
		pFile->Release();
	}
	
	return hr;
}

static HRESULT ReadAAFFile(aafWChar* pFileName)
{
	IAAFFile*		pFile = NULL;
	bool bFileOpen = false;
	IAAFHeader*		pHeader = NULL;
	IAAFMob*		pMob = NULL;
	IAAFMasterMob*		pMasterMob = NULL;
	HRESULT			hr = S_OK;
	
	
	
	try
	{
		// Open the AAF file
		checkResult(OpenAAFFile(pFileName, kMediaOpenReadOnly, &pFile, &pHeader));
		bFileOpen = true;
		
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	// Cleanup and return
	if (pHeader)
		pHeader->Release();
	
	if (pFile)
	{  // Close file
		if (bFileOpen)
			pFile->Close();
		pFile->Release();
	}
	
	return hr;
}


extern "C" HRESULT CAAFEssenceFormat_test()
{
	HRESULT hr = AAFRESULT_NOT_IMPLEMENTED;
	aafWChar * pFileName = L"AAFEssenceFormatTest.aaf";
	
	try
	{
		hr = CreateAAFFile(pFileName);
		if (SUCCEEDED(hr))
			hr = ReadAAFFile(pFileName);
	}
	catch (...)
	{
		cerr << "CAAFEssenceFormat_test...Caught general C++ exception!" << endl; 
	}
	
	// When all of the functionality of this class is tested, we can return success.
	// When a method and its unit test have been implemented, remove it from the list.
//	if (SUCCEEDED(hr))
//	{
//		cout << "The following IAAFEssenceFormat tests have not been implemented:" << endl; 
//		cout << "     GetIndexedFormatSpecifier" << endl; 
//		hr = AAFRESULT_TEST_PARTIAL_SUCCESS;
//	}
	
	return hr;
}
























