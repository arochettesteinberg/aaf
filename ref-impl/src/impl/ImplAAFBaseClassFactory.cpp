#include <stdio.h>
#include <stdlib.h>


#include "ImplAAFBaseClassFactory.h"

#include "ImplAAFObject.h"
#include "OMFile.h"
#include "OMClassFactory.h"

#include "ImplAAFObjectCreation.h"


#include <assert.h>


//
// Initialize the AUID's.
#define INIT_AUID
#include "AAFStoredObjectIDs.h"
#undef INIT_AUID

//
// Declare the corresponding CLSID's external.
#define AAF_CLASS(name, dataid, parent)\
  extern "C" aafClassID_t CLSID_AAF##name;

// The AAF reference implementation is still not quite in sync with SMPTE
// so we have to alias some of the SMPTE names to their corresponding
// name in AAF.
//
#define CLSID_AAFClassDefinition CLSID_AAFClassDef
#define CLSID_AAFConstantValue CLSID_AAFConstValue
#define CLSID_AAFDataDefinition CLSID_AAFDataDef
#define CLSID_AAFDefinitionObject CLSID_AAFDefObject
#define CLSID_AAFEdgeCode CLSID_AAFEdgecode
#define CLSID_AAFEffectDefinition CLSID_AAFEffectDef
#define CLSID_AAFEssenceGroup CLSID_AAFMediaGroup
#define CLSID_AAFFilmDescriptor CLSID_AAFMediaFilmDescriptor
#define CLSID_AAFGroup CLSID_AAFGroup
#define CLSID_AAFInterchangeObject CLSID_AAFObject
#define CLSID_AAFJPEGImageData CLSID_AAFJPEGData
#define CLSID_AAFMIDIFileData CLSID_AAFMIDIData
#define CLSID_AAFParameterDefinition CLSID_AAFParameterDef
#define CLSID_AAFPropertyDefinition CLSID_AAFPropertyDef
#define CLSID_AAFTypeDefinition CLSID_AAFTypeDef
#define CLSID_AAFTypeDefinitionEnumeration CLSID_AAFTypeDefEnum
#define CLSID_AAFTypeDefinitionFixedArray CLSID_AAFTypeDefFixedArray
#define CLSID_AAFTypeDefinitionInteger CLSID_AAFTypeDefInt
#define CLSID_AAFTypeDefinitionRecord CLSID_AAFTypeDefRecord
#define CLSID_AAFTypeDefinitionRename CLSID_AAFTypeDefRename
#define CLSID_AAFTypeDefinitionSet CLSID_AAFTypeDefSet
#define CLSID_AAFTypeDefinitionStream CLSID_AAFTypeDefStream
#define CLSID_AAFTypeDefinitionString CLSID_AAFTypeDefString
#define CLSID_AAFTypeDefinitionStrongObjectReference CLSID_AAFTypeDefStrongObjRef
#define CLSID_AAFTypeDefinitionVariableArray CLSID_AAFTypeDefVariableArray
#define CLSID_AAFTypeDefinitionWeakObjectReference CLSID_AAFTypeDefWeakObjRef
#define CLSID_AAFUNIXLocator CLSID_AAFUnixLocator
#define CLSID_AAFCodecDefinition CLSID_AAFCodecDef
#define CLSID_AAFContainerDefinition CLSID_AAFContainerDef
#define CLSID_AAFPluggableDefinition CLSID_AAFPluggableDef

//
// Include the AAF macro invocations.
#include "AAFMetaDictionary.h"
// cleanup symbols.
#undef AAF_CLASS



//
// Initialize the AUID to CLSID class table.
typedef struct tagAAFObjectEntry_t
{
	const char * pClassName;
	const aafUID_t* pAUID;
	const aafClassID_t* pClassID;
} AAFObjectEntry_t;

// cleanup symbols.
#undef AAF_TABLE_BEGIN
#undef AAF_CLASS
#undef AAF_CLASS_SEPARATOR
#undef AAF_TABLE_END
#define AAF_TABLE_BEGIN() static AAFObjectEntry_t gAAFObjectTable[] = {

#define AAF_CLASS(name, id, parent)\
{ #name, &AUID_AAF##name, &CLSID_AAF##name }

#define AAF_CLASS_SEPARATOR() ,

#define AAF_TABLE_END() };
//
// Include the AAF macro invocations.
// This will define all of the entries in the gAAFObjectTable.
#include "AAFMetaDictionary.h"
// cleanup symbols.
#undef AAF_TABLE_BEGIN
#undef AAF_CLASS
#undef AAF_CLASS_SEPARATOR
#undef AAF_TABLE_END

// Define a table of pointers to entries on the gAAFObjectTable. We use 
// this table to sort and search for AUID's in the gAAFObjectTable.
const size_t kTotalAUIDCount = sizeof(gAAFObjectTable)/sizeof(AAFObjectEntry_t);
static AAFObjectEntry_t * g_AUIDTable[kTotalAUIDCount] = {0};


// Declare a global instance of the factory so that the initialization
// code will only be called once.
static ImplAAFBaseClassFactory s_AAFBaseClassFactory;


// Compare proc for sort and search.
static int CompareTableEntries(const AAFObjectEntry_t **elem1,
                               const AAFObjectEntry_t **elem2)
{
  const aafUID_t &auid1 = *((**elem1).pAUID);
  const aafUID_t &auid2 = *((**elem2).pAUID);

  // Compare the unsigned long member
  if (auid1.Data1 < auid2.Data1)
    return -1;
  else if (auid1.Data1 > auid2.Data1)
    return 1;
  // Compare the first unsigned short member
  else if (auid1.Data2 < auid2.Data2)
    return -1;
  else if (auid1.Data2 > auid2.Data2)
    return 1;
  // Compare the second unsigned short member
  else if (auid1.Data3 < auid2.Data3)
    return -1;
  else if (auid1.Data3 > auid2.Data3)
    return 1;
  else
  // Compare the last 8 bytes.
    return memcmp(auid1.Data4, auid2.Data4, 8);
}

static void InitializeAUIDTable(void)
{
  for (size_t i = 0; kTotalAUIDCount > i; ++i)
  {
    g_AUIDTable[i] = &gAAFObjectTable[i];
  }

  // Now sort the table.
  qsort(g_AUIDTable, kTotalAUIDCount, sizeof(AAFObjectEntry_t *),
        (int (*)(const void*, const void*))CompareTableEntries); 
}


ImplAAFBaseClassFactory::ImplAAFBaseClassFactory(void)
{
  // Initialize our lookup table for the built-in base class auids.
  if (0 == g_AUIDTable[0])
    InitializeAUIDTable();
}

ImplAAFBaseClassFactory::~ImplAAFBaseClassFactory(void)
{
}



// Global function that looksup the built-in code class id for the corresponding
// auid.
const aafClassID_t* ImplAAFBaseClassFactory::LookupClassID(const aafUID_t* pAUID)
{
  // Return NULL if the given AUID cannot be found.
  const aafClassID_t *pClassID = NULL;

  // Lookup the class id in the predefined "base class" table.
  AAFObjectEntry_t **ppResult = NULL;
  AAFObjectEntry_t key = {"KEY", pAUID, NULL};
  AAFObjectEntry_t *pKey = &key;
  
  // Use standard library's binary search routine.
  ppResult = (AAFObjectEntry_t **)bsearch(&pKey, g_AUIDTable, kTotalAUIDCount,
               sizeof(AAFObjectEntry_t *),
               (int (*)(const void*, const void*))CompareTableEntries);

  // Return the corresponding class id.
  if (NULL != ppResult)
    pClassID = (**ppResult).pClassID;

  return (pClassID);
}

