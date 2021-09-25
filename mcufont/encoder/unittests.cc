/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_RLEFontEncodeTests_init = false;
#include "encode_rlefont.hh"

static RLEFontEncodeTests suite_RLEFontEncodeTests;

static CxxTest::List Tests_RLEFontEncodeTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RLEFontEncodeTests( "encode_rlefont.hh", 63, "RLEFontEncodeTests", suite_RLEFontEncodeTests, Tests_RLEFontEncodeTests );

static class TestDescription_suite_RLEFontEncodeTests_testEncode : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RLEFontEncodeTests_testEncode() : CxxTest::RealTestDescription( Tests_RLEFontEncodeTests, suiteDescription_RLEFontEncodeTests, 66, "testEncode" ) {}
 void runTest() { suite_RLEFontEncodeTests.testEncode(); }
} testDescription_suite_RLEFontEncodeTests_testEncode;

static class TestDescription_suite_RLEFontEncodeTests_testDecode : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RLEFontEncodeTests_testDecode() : CxxTest::RealTestDescription( Tests_RLEFontEncodeTests, suiteDescription_RLEFontEncodeTests, 95, "testDecode" ) {}
 void runTest() { suite_RLEFontEncodeTests.testDecode(); }
} testDescription_suite_RLEFontEncodeTests_testDecode;

#include "bdf_import.hh"

static BDFTests suite_BDFTests;

static CxxTest::List Tests_BDFTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BDFTests( "bdf_import.hh", 18, "BDFTests", suite_BDFTests, Tests_BDFTests );

static class TestDescription_suite_BDFTests_testLoadBDF : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BDFTests_testLoadBDF() : CxxTest::RealTestDescription( Tests_BDFTests, suiteDescription_BDFTests, 21, "testLoadBDF" ) {}
 void runTest() { suite_BDFTests.testLoadBDF(); }
} testDescription_suite_BDFTests_testLoadBDF;

#include "datafile.hh"

static DataFileTests suite_DataFileTests;

static CxxTest::List Tests_DataFileTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DataFileTests( "datafile.hh", 120, "DataFileTests", suite_DataFileTests, Tests_DataFileTests );

static class TestDescription_suite_DataFileTests_testFileLoad : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DataFileTests_testFileLoad() : CxxTest::RealTestDescription( Tests_DataFileTests, suiteDescription_DataFileTests, 123, "testFileLoad" ) {}
 void runTest() { suite_DataFileTests.testFileLoad(); }
} testDescription_suite_DataFileTests_testFileLoad;

static class TestDescription_suite_DataFileTests_testFileSave : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DataFileTests_testFileSave() : CxxTest::RealTestDescription( Tests_DataFileTests, suiteDescription_DataFileTests, 142, "testFileSave" ) {}
 void runTest() { suite_DataFileTests.testFileSave(); }
} testDescription_suite_DataFileTests_testFileSave;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
