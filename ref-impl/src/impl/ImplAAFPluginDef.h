//@doc
//@class    AAFPluginDescriptor | Implementation class for AAFPluginDescriptor
#ifndef __ImplAAFPluginDescriptor_h__
#define __ImplAAFPluginDescriptor_h__


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

class ImplAAFPluggableCode;

class ImplEnumAAFPluginLocators;



#ifndef __ImplAAFObject_h__
#include "ImplAAFObject.h"
#endif

#include "ImplAAFLocator.h"
#include "ImplAAFNetworkLocator.h"

class ImplAAFPluginDescriptor : public ImplAAFObject
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFPluginDescriptor ();

protected:
  virtual ~ImplAAFPluginDescriptor ();

public:
  // Initialize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Initialize
        // @parm [in] Pointer to an AUID reference
        (const aafUID_t & pAuid,
		 const aafCharacter * name,
		 const aafCharacter * description);


  //****************
  // GetAUID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAUID
        // @parm [retval,out] Pointer to an AUID reference
        (aafUID_t *  pAuid) const;


  //****************
  // SetAUID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetAUID
        // @parm [in] Pointer to an AUID reference
        (const aafUID_t & id);


  //****************
  // SetName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetName
        (const aafCharacter *  name);  //@parm [in, ref] Definition Name


  //****************
  // GetName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetName
        (// @parm [out, string, size_is(bufSize)] buffer into which Name is to be written
         aafCharacter *  pName,

         // @parm [in] size of *pName buffer in bytes
         aafUInt32  bufSize);


  //****************
  // GetNameBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetNameBufLen
        (aafUInt32 *  nameLen);  //@parm [in,out] Definition Name length


  //****************
  // SetDescription()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetDescription
        (const aafCharacter *  description);  //@parm [in, ref] Definition description


  //****************
  // GetDescription()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetDescription
        (aafCharacter *  description,  //@parm [in] Definition Description
		 aafUInt32 bufSize);	  //@parm [in] size of the buffer required to hold Definition Description + terminator


  //****************
  // GetDescriptionBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetDescriptionBufLen
        (aafUInt32 *  descriptionLen);  //@parm [in,out] Definition description length



  //****************
  // GetCategoryClass()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetCategoryClass
        // @parm [out] The CategoryClass
        (aafUID_t *  pCategoryClass);


  //****************
  // SetCategoryClass()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetCategoryClass
        // @parm [in] The Category Class
        (const aafUID_t & categoryClass);


  //****************
  // GetPluginVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginVersion
        // @parm [out] The Plugin Version
        (aafVersionType_t *  pVersion);


  //****************
  // SetPluginVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginVersion
        (aafVersionType_t *  pVersion);


  //****************
  // GetPluginVersionString()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginVersionString
        (// @parm [in,string] Plugin version string
         aafCharacter *  pVersionString,

         // @parm [in] length of the buffer to hold plugin version string
         aafUInt32  bufSize);


  //****************
  // GetProductVersionStringLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginVersionStringBufLen
        // @parm [out] Mob Name
        (aafUInt32 *  pLen);


  //****************
  // SetPluginVersionString()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginVersionString
        // @parm [in, string] Plugin version
        (const aafCharacter * pVersionString);


  //****************
  // GetPluginManufacturerName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginManufacturerName
        (// @parm [in,string] Plugin Manufacturer Name
         aafCharacter *  pManufacturerName,

         // @parm [in] length of the buffer to hold plugin Manufacturer Name
         aafUInt32  bufSize);


  //****************
  // GetPluginManufacturerNameBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginManufacturerNameBufLen
        // @parm [out] Manufacturer Name
        (aafUInt32 *  pLen);


  //****************
  // SetPluginManufacturerName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginManufacturerName
        // @parm [in, string] Plugin Manufacturer
        (const aafCharacter * pManufacturerName);


  //****************
  // GetManufacturerInfo()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetManufacturerInfo
        // @parm [out,retval] ManufacturerInfo property value
        (ImplAAFNetworkLocator ** ppResult);


  //****************
  // SetManufacturerInfo()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetManufacturerInfo
        // @parm [in] ManufacturerInfo property value
        (ImplAAFNetworkLocator * pManufacturerInfo);


  //****************
  // GetManufacturerID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetManufacturerID
        // @parm [out] The ManufacturerID
        (aafUID_t *  pManufacturerID);


  //****************
  // SetManufacturerID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetManufacturerID
        // @parm [in] The Category Class
        (const aafUID_t & manufacturerID);


  //****************
  // GetHardwarePlatform()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetHardwarePlatform
        // @parm [out] The HardwarePlatform
        (aafHardwarePlatform_t *  pHardwarePlatform);


  //****************
  // SetHardwarePlatform()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetHardwarePlatform
        // @parm [in] The Category Class
        (aafHardwarePlatform_constref  hardwarePlatform);


  //****************
  // GetPlatformVersionRange()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPlatformVersionRange
        (// @parm [out] The Minimum Platform Version
         aafVersionType_t *  pMinVersion,

         // @parm [out] The Maximum Platform Version
         aafVersionType_t *  pMaxVersion);


  //****************
  // SetPlatformMinimumVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPlatformMinimumVersion
        // @parm [in] The Minimum Platform Version
        (const aafVersionType_t & minVersion);


  //****************
  // SetPlatformMaximumVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPlatformMaximumVersion
        // @parm [in] The Maximum Platform Version
        (const aafVersionType_t & maxVersion);


  //****************
  // GetEngine()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetEngine
        // @parm [out] The software engine
        (aafEngine_t *  pEngine);


  //****************
  // SetEngine()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEngine
        // @parm [in] The software engine
        (aafEngine_constref engine);


  //****************
  // GetEngineVersionRange()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetEngineVersionRange
        (// @parm [out] The Minimum Engine Version
         aafVersionType_t *  pMinVersion,

         // @parm [out] The Maximum Engine Version
         aafVersionType_t *  pMaxVersion);


  //****************
  // SetEngineMinimumVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEngineMinimumVersion
        // @parm [in] The Minimum Engine Version
        (const aafVersionType_t & minVersion);


  //****************
  // SetEngineMaximumVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEngineMaximumVersion
        // @parm [in] The Minimum Engine Version
        (const aafVersionType_t & maxVersion);


  //****************
  // GetPluginAPI()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginAPI
        // @parm [out] The PluginAPI
        (aafPluginAPI_t *  pPluginAPI);


  //****************
  // SetPluginAPI()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginAPI
        // @parm [in] The Category Class
        (aafPluginAPI_constref  pluginAPI);


  //****************
  // GetPluginAPIVersionRange()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginAPIVersionRange
        (// @parm [out] The Minimum Plugin API Version
         aafVersionType_t *  pMinVersion,

         // @parm [out] The Maximum Plugin API Version
         aafVersionType_t *  pMaxVersion);


  //****************
  // SetPluginAPIMinimumVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginAPIMinimumVersion
        // @parm [out] The Minimum Plugin API Version
        (const aafVersionType_t & minVersion);


  //****************
  // SetPluginAPIMaximumVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginAPIMaximumVersion
        // @parm [in] The Maximum Plugin API Version
        (const aafVersionType_t & maxVersion);


  //****************
  // IsSoftwareOnly()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    IsSoftwareOnly
        // @parm [out] The IsSoftwareOnly
        (aafBool *  pIsSoftwareOnly);



  //****************
  // SetIsSoftwareOnly()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetIsSoftwareOnly
        // @parm [in] The isSoftwareOnly flag
        (aafBool  isSoftwareOnly);



  //****************
  // IsAccelerated()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    IsAccelerated
        // @parm [out] The IsAccelerated
        (aafBool *  pIsAccelerated);




  //****************
  // SetIsAccelerated()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetIsAccelerated
        // @parm [in] The isAccelerated flag
        (aafBool  isAccelerated);


  //****************
  // SupportsAuthentication()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SupportsAuthentication
        // @parm [out] The SupportsAuthentication
        (aafBool *  pSupportsAuthentication);


  //****************
  // SetSupportsAuthentication()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetSupportsAuthentication
        // @parm [in] The SupportsAuthentication flag
        (aafBool  SupportsAuthentication);


  //****************
  // GetPluggableCode()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluggableCode
        // @parm [out] An interface pointer to the pluggable code object
        (ImplAAFPluggableCode ** pCode);


  //****************
  // CountLocators()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    CountLocators
        // @parm [out] Returns the number of locators
        (aafUInt32 *  pCount);


  //****************
  // AppendLocator()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    AppendLocator
        // @parm [in] Locator to append
        (ImplAAFLocator * pLocator);


  //****************
  // PrependLocator()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    PrependLocator
        // @parm [in] Locator to append
        (ImplAAFLocator * pLocator);


  //****************
  // InsertLocatorAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    InsertLocatorAt
        // @parm [in] index to place new locator
        (aafUInt32 index,

        // @parm [in] Locator to insert
		ImplAAFLocator * pLocator);


  //****************
  // GetLocatorAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetLocatorAt
        // @parm [in] index to place new locator
        (aafUInt32 index,

        // @parm [out, retval] returned Locator
		ImplAAFLocator ** ppLocator);


  //****************
  // RemoveLocatorAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    RemoveLocatorAt
        // @parm [in] index of locator to remove
        (aafUInt32 index);


  //****************
  // IsPluginLocal()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    IsPluginLocal
        // @parm [out] Returns kAAFTrue if the plugin is local
        (aafBool *  pIsLocal);


  //****************
  // GetPluginDescriptorID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPluginDescriptorID
        // @parm [out] The unique plugin descriptor id
        (aafUID_t *  pDescriptorID);


  //****************
  // SetPluginDescriptorID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPluginDescriptorID
        // @parm [in] New Mob ID
        (aafUID_t  descriptorID);
  

  //****************
  // GetLocators()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetLocators
        // @parm [out, retval] Plugin Locator Enumeration
        (ImplEnumAAFPluginLocators ** ppEnum);


public:
	virtual AAFRESULT
		GetNthLocator (aafInt32 index, ImplAAFLocator **ppLocator);
  //	virtual AAFRESULT
  //		 GetNumLocators (aafInt32 *  pCount);
  virtual const OMUniqueObjectIdentification& identification(void) const;

private:
	OMWideStringProperty          _name;
	OMWideStringProperty          _description;
	OMFixedSizeProperty<aafUID_t> _identification;
	OMFixedSizeProperty<aafUID_t>					_categoryClass;
	OMFixedSizeProperty<aafVersionType_t>			_pluginVersion;
	OMWideStringProperty                            _pluginVersionString;
	OMWideStringProperty                            _pluginManufacturerName;
	OMStrongReferenceProperty<ImplAAFNetworkLocator> _manufacturerURL;
	OMFixedSizeProperty<aafUID_t>					_pluginManufacturerID;
	OMFixedSizeProperty<aafUID_t>					_platform;
	OMFixedSizeProperty<aafVersionType_t>			_minPlatformVersion;
	OMFixedSizeProperty<aafVersionType_t>			_maxPlatformVersion;
	OMFixedSizeProperty<aafUID_t>					_engine;
	OMFixedSizeProperty<aafVersionType_t>			_minEngineVersion;
	OMFixedSizeProperty<aafVersionType_t>			_maxEngineVersion;
	OMFixedSizeProperty<aafUID_t>					_pluginAPI;
	OMFixedSizeProperty<aafVersionType_t>			_minPluginAPIVersion;
	OMFixedSizeProperty<aafVersionType_t>			_maxPluginAPIVersion;
	OMFixedSizeProperty<aafBool>					_softwareOnly;
	OMFixedSizeProperty<aafBool>					_accelerator;
    OMStrongReferenceVectorProperty<ImplAAFLocator> _locators;
	OMFixedSizeProperty<aafBool>					_authentication;
};

#endif // ! __ImplAAFPluginDescriptor_h__


