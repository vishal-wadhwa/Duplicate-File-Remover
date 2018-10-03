#include <cppunit/CompilerOutputter.h>
// #include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "unit_tests.h"
#include <string>



// CPPUNIT_TEST_SUITE_REGISTRATION(dfr::file_handler_test);
// CPPUNIT_TEST_SUITE_REGISTRATION(dfr::file_hash_test);

int main()
{

	// CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
	CppUnit::TextUi::TestRunner runner;

	runner.addTest(dfr::file_handler_test::suite());
	runner.addTest(dfr::file_hash_test::suite());
	CppUnit::CompilerOutputter *cot = new CppUnit::CompilerOutputter(&runner.result(), std::cerr);
	runner.setOutputter(cot);
	return runner.run();
}
