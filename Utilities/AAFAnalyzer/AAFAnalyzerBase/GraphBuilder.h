//=---------------------------------------------------------------------=
//
// $Id$
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
//=---------------------------------------------------------------------=

#ifndef __GRAPHBUILDER_h__
#define __GRAPHBUILDER_h__

//project files
#include "TestGraph.h"

//stl files
#include <string>
#include <map>

//boost files
#include <boost/shared_ptr.hpp>

namespace aafanalyzer {

class NodeFactory;

class GraphBuilder
{

 public:
  GraphBuilder();
  ~GraphBuilder();

  TestGraph CreateGraph(const std::basic_string<wchar_t>& fileName, boost::shared_ptr<NodeFactory> spFactory );

 private:  

  // prohibited
  GraphBuilder( const GraphBuilder& );
  GraphBuilder& operator=( const GraphBuilder& );
};

} // end of namespace diskstream

#endif