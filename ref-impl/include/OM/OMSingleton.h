//=---------------------------------------------------------------------=
//
// $Id$ $Name$
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
// The Original Code of this file is Copyright 1998-2004, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

// @doc OMEXTERNAL
#ifndef OMSINGLETON_H
#define OMSINGLETON_H

  // @class Singleton objects.
  //
  // References ...
  //
  // [1] "Design Patterns: Elements of Reusable Object-Oriented Software",
  // Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides,
  // 1994 Addison-Wesley, ISBN 0-201-63361-2, Singleton(127)
  //
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
template <typename Type>
class OMSingleton{
public:

  static Type* instance(void);
  static void destroy(void);

protected:
  OMSingleton(void);
  virtual ~OMSingleton(void);

private:
  static Type* _onlyInstance;
};

#include "OMSingletonT.h"

#endif
