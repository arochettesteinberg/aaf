//=---------------------------------------------------------------------=
//
// $Id$ $Name$
//
// The contents of this file are subject to the AAF SDK Public Source
// License Agreement Version 2.0 (the "License"); You may not use this
// file except in compliance with the License.  The License is available
// in AAFSDKPSL.TXT, or you may obtain a copy of the License from the
// Advanced Media Workflow Association, Inc., or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.  Refer to Section 3.3 of the License for proper use
// of this Exhibit.
//
// WARNING:  Please contact the Advanced Media Workflow Association,
// Inc., for more information about any additional licenses to
// intellectual property covering the AAF Standard that may be required
// to create and distribute AAF compliant products.
// (http://www.amwa.tv/policies).
//
// Copyright Notices:
// The Original Code of this file is Copyright 1998-2009, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
//=---------------------------------------------------------------------=

#ifndef __EPDerivatinTest_h__
#define __EPDerivatinTest_h__

//Test/Result files
#include <Test.h>

#include <AxTypes.h>

namespace aafanalyzer {

using namespace std;

class TestGraph;
class CompMobDependency;

class EPDerivationTest : public Test
{
 public:

  EPDerivationTest( wostream& log,
		    boost::shared_ptr<const TestGraph> spGraph,
		    boost::shared_ptr<CompMobDependency> spDepTest );
  virtual ~EPDerivationTest();

  virtual boost::shared_ptr<TestLevelTestResult> Execute();
  virtual AxString GetName() const;
  virtual AxString GetDescription() const;
  static const TestInfo GetTestInfo();

 private:

  // prohibited
  EPDerivationTest();
  EPDerivationTest( const EPDerivationTest& );
  EPDerivationTest& operator=( const EPDerivationTest& );

  boost::shared_ptr<CompMobDependency> _spDepTest;
};

} // end of namespace aafanalyzer

#endif
