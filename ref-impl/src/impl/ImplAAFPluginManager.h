//@doc
//@class    AAFPluginManager | Implementation class for AAFPluginManager
#ifndef __ImplAAFPluginManager_h__
#define __ImplAAFPluginManager_h__


/************************************************\
*												*
* Advanced Authoring Format						*
*												*
* Copyright (c) 1998-1999 Avid Technology, Inc. *
* Copyright (c) 1998-1999 Microsoft Corporation *
*												*
\************************************************/



class ImplEnumAAFLoadedPlugins;

#ifndef __ImplAAFRoot_h__
#include "ImplAAFRoot.h"
#endif

#include "AAFPlugin.h"
#include "aafTable.h"

class ImplAAFPluginManager : public ImplAAFRoot
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFPluginManager ();

protected:
  virtual ~ImplAAFPluginManager ();

public:


  //****************
  // EnumLoadedPlugins()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    EnumLoadedPlugins
        (// @parm [in] Which category ID do we want to enumerate
         aafUID_t  categoryID,

         // @parm [out,retval] Loaded Plugin Enumeration
         ImplEnumAAFLoadedPlugins ** ppEnum);



public:
  // Declare the module test method. The implementation of the will be be
  // in /test/ImplAAFPluginManagerTest.cpp.
  static AAFRESULT test();

public:
	//Toolkit internal only
static ImplAAFPluginManager *GetPluginManager(void);

AAFRESULT GetPluginInstance(
			aafUID_t		pluginID,
			IAAFPlugin		**result);

AAFRESULT MakeCodecFromEssenceDesc(
			aafUID_t		essenceDesc,	// Stored class ID
			IAAFEssenceCodec **codec);

AAFRESULT RegisterPlugin(
			CLSID		plugin);

AAFRESULT Init(void);

private:
	aafTable_t	*_plugins;
	aafTable_t	*_codecDesc;
};

#endif // ! __ImplAAFPluginManager_h__

//!!! Clean out below here
// The implementation of this class should contain a structure like:
//typedef struct
//{
//	aafPluginType_t			type;
//	AAFEssenceCodec			*dispatch;
//	aafCodecMetaInfo_t		metaInfo;
//} codecTableEntry_t;

#if FULL_TOOLKIT
			class AAFEssenceCodec	*pluginRoutine,
			aafPluginType_t			type);
#endif



#if FULL_TOOLKIT
AAFRESULT EnumCodecs(
			aafUID_t		dataDefinition,
			aafFileRev_t	rev);

AAFRESULT EnumCodecVarieties(
			aafUID_t		codecID,
			aafFileRev_t    setrev,
			aafUID_t		dataDefinition);
#endif
