//@doc
//@class    AAFFile | Implementation class for AAFFile
#ifndef __ImplAAFFile_h__
#define __ImplAAFFile_h__

/******************************************\
*                                          *
* Advanced Authoring Format                *
*                                          *
* Copyright (c) 1998 Avid Technology, Inc. *
* Copyright (c) 1998 Microsoft Corporation *
*                                          *
\******************************************/

#ifndef __AAFTypes_h__
#include "AAFTypes.h"
#endif

#include "Stubs.h"

typedef enum
{
	kOmCreate, kOmModify, kOmOpenRead
}				openType_t;

//
// Forward declaration
//
struct IAAFFile;
class AAFFile;
struct IAAFMedia;
class AAFMedia;
struct IAAFHeader;
class AAFHeader;
struct IAAFSession;
class ImplAAFSession;
class ImplAAFDataDefinition;

class ImplAAFFile
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFFile ();
  virtual ~ImplAAFFile ();

  //***********************************************************
  // METHOD NAME: Close()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFFile | Close |
  // Closes an AAF file, saving the result.
  // @end
  virtual AAFRESULT STDMETHODCALLTYPE
    Close ();

  //***********************************************************
  // METHOD NAME: GetRevision()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFFile | GetRevision |
  // Get the revision of the ciurrent AAF file.
  // @end
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
  GetRevision (
    // @parm aafFileRev_t * | rev | [out] Revision of the current file
    aafFileRev_t *  rev
  );

public:
  // Declare the module test method. The implementation of the will be be
  // in /test/ImplAAFFileTest.cpp.
  static AAFRESULT test();

  void InitContainer (void * pContainer);

  void * GetContainer ();

AAFRESULT Create(
			aafDataBuffer_t		stream, 
			ImplAAFSession *	session, 
			aafFileRev_t		rev);
AAFRESULT OpenRead(
			aafDataBuffer_t		stream, 
			ImplAAFSession *	session);
AAFRESULT OpenModify(
			aafDataBuffer_t		stream, 
			ImplAAFSession *	session);
private:

AAFRESULT InternOpenFile(aafDataBuffer_t stream, 
								   ImplAAFSession * session,
								   OMLContainerUseMode useMode, 
								   openType_t type);
  void * _pContainer;

		aafInt32       	_cookie;
		aafFileFormat_t _fmt;
		OMContainer     *_container;
		aafInt16           _byteOrder;
		openType_t		_openType;
		ImplAAFFile			*_prevFile;
#if FULL_TOOLKIT
		AAFHeader *     _head;		// Needed by Head object
		aafCloseMediaPtr _closeMediaProc;
		aafBool			_customStreamFuncsExist;	//!!!	
		struct aafCodecStreamFuncs _streamFuncs;	//!!!	
		aafRawStream_t	*_rawFile;	//!!!	
		aafLocatorFailureCB _locatorFailureCallback;	//!!!	
		aafCodecID_t	_rawCodecID;	//!!!	
		void           	*_rawFileDesc;		//!!!/* If non-omfi file */
		AAFMedia *   _topMedia;	//!!!
#endif
		aafBool         _semanticCheckEnable;	//!!!  /* Used to stop recursion in checks */
		ImplAAFSession		 *_session;		//!!!  used by file checker
		ImplAAFDataDefinition *	_nilKind;// !!!
		ImplAAFDataDefinition *	_pictureKind;// !!!
		ImplAAFDataDefinition *	_soundKind;// !!!
#ifdef AAF_ERROR_TRACE
		char			*_stackTrace;	//!!!	
		aafInt32		_stackTraceSize;	//!!!	
#endif
		aafFileRev_t     _setrev;
};

#endif // ! __ImplAAFFile_h__

