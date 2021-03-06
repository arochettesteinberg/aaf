###############################################################################
#
# $Id$ $Name$
#
# The contents of this file are subject to the AAF SDK Public Source
# License Agreement Version 2.0 (the "License"); You may not use this
# file except in compliance with the License.  The License is available
# in AAFSDKPSL.TXT, or you may obtain a copy of the License from the
# Advanced Media Workflow Association, Inc., or its successor.
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
# the License for the specific language governing rights and limitations
# under the License.  Refer to Section 3.3 of the License for proper use
# of this Exhibit.
#
# WARNING:  Please contact the Advanced Media Workflow Association,
# Inc., for more information about any additional licenses to
# intellectual property covering the AAF Standard that may be required
# to create and distribute AAF compliant products.
# (http://www.amwa.tv/policies).
#
# Copyright Notices:
# The Original Code of this file is Copyright 1998-2009, licensor of the
# Advanced Media Workflow Association.  All rights reserved.
#
# The Initial Developer of the Original Code of this file and the
# licensor of the Advanced Media Workflow Association is
# Avid Technology.
# All rights reserved.
#
###############################################################################

ALL = AnalyzerBase \
      AAFAnalyzerBase \
      EPAnalyzerBase \
      RequirementLib \
      TestPhaseLib \
      BaseTestImpl \
      EditProtocolTestImpl \
      AAFAnalyzer 

# Temporarily disable regression tests until they can be brough in
# sync with recent changes.
#      RegressionTestStructure
#      RegressionTestFiles

GCOV =

all: $(ALL)

.PHONY: gcov
gcov: GCOV = gcov
gcov: $(ALL)

#.PHONY: RegressionTest
#RegressionTest: RegressionTestStructure RegressionTestFiles

.PHONY: AnalyzerBase
AnalyzerBase:
	cd AnalyzerBase && $(MAKE) $(GCOV)

.PHONY: AAFAnalyzerBase
AAFAnalyzerBase: AnalyzerBase
	cd AAFAnalyzerBase && $(MAKE) $(GCOV)

.PHONY: EPAnalyzerBase
EPAnalyzerBase: AnalyzerBase AAFAnalyzerBase
	cd EPAnalyzerBase && $(MAKE) $(GCOV)

.PHONY: RequirementLib
RequirementLib: AnalyzerBase
	cd RequirementLib && $(MAKE) $(GCOV)	

.PHONY: TestPhaseLib
TestPhaseLib: AnalyzerBase RequirementLib
	cd TestPhaseLib && $(MAKE) $(GCOV)

.PHONY: BaseTestImpl
BaseTestImpl: AnalyzerBase AAFAnalyzerBase RequirementLib TestPhaseLib
	cd BaseTestImpl && $(MAKE) $(GCOV)

.PHONY: EditProtocolTestImpl
EditProtocolTestImpl: AnalyzerBase AAFAnalyzerBase EPAnalyzerBase RequirementLib TestPhaseLib
	cd EditProtocolTestImpl && $(MAKE) $(GCOV)

.PHONY: AAFAnalyzer
AAFAnalyzer: AAFAnalyzerBase RequirementLib TestPhaseLib BaseTestImpl EditProtocolTestImpl
	cd AAFAnalyzer && $(MAKE) $(GCOV)

.PHONY: RegressionTestStructure
RegressionTestStructure: AnalyzerBase AAFAnalyzerBase RequirementLib TestPhaseLib BaseTestImpl
	cd RegressionTest && $(MAKE) $(GCOV) $@

.PHONY: RegressionTestFiles
RegressionTestFiles: AAFAnalyzerBase RequirementLib TestPhaseLib BaseTestImpl EditProtocolTestImpl AAFAnalyzer
	cd RegressionTest && $(MAKE) $(GCOV) $@

.PHONY : check
check : RegressionTestStructure RegressionTestFiles AAFAnalyzer
	cd RegressionTest && $(MAKE) $(GCOV) $@

.PHONY: clean
clean:
	cd RequirementLib && $(MAKE) GENDEPS=0 $@
	cd AnalyzerBase && $(MAKE) GENDEPS=0 $@
	cd AAFAnalyzerBase && $(MAKE) GENDEPS=0 $@
	cd EPAnalyzerBase && $(MAKE) GENDEPS=0 $@
	cd TestPhaseLib && $(MAKE) GENDEPS=0 $@
	cd RegressionTest && $(MAKE) GENDEPS=0 $@
	cd BaseTestImpl && $(MAKE) GENDEPS=0 $@
	cd EditProtocolTestImpl && $(MAKE) GENDEPS=0 $@
	cd AAFAnalyzer && $(MAKE) GENDEPS=0 $@

.PHONY: realclean
realclean: clean
