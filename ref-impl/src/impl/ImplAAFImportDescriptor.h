//@doc
//@class    ImplAAFImportDescriptor | Implementation class for IAAFImportDescriptor
#ifndef __ImplAAFImportDescriptor_h__
#define __ImplAAFImportDescriptor_h__

//=---------------------------------------------------------------------=
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
// 
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
// 
// The Original Code of this file is Copyright 1998-2001, Licensor of the
// AAF Association.
// 
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=


#ifndef __AAFTypes_h__
#include "AAFTypes.h"
#endif

#ifndef __ImplAAFPhysicalDescriptor_h__
#include "ImplAAFPhysicalDescriptor.h"
#endif

#include "OMWideStringProperty.h"



class ImplAAFImportDescriptor : public ImplAAFPhysicalDescriptor
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFImportDescriptor ();
  virtual ~ImplAAFImportDescriptor ();


  virtual AAFRESULT STDMETHODCALLTYPE
	Initialize ();




public:

//  virtual AAFRESULT	STDMETHODCALLTYPE
//		GetOwningMobKind (aafMobKind_t *pMobKind);

	// Persistent properties
private:
};

#endif // ! __ImplAAFImportDescriptor_h__

