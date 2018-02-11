#ifndef DFR_TEST_H_
#define DFR_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace dfr
{
class file_handler_test : public CppUnit::TestFixture
{ 
    CPPUNIT_TEST_SUITE(file_handler_test);
    CPPUNIT_TEST(invalid_dir_test);
    CPPUNIT_TEST(list_generate_test);
    CPPUNIT_TEST(init_val_test);
    CPPUNIT_TEST(remove_in_place_test);
    CPPUNIT_TEST(filter_test);
    CPPUNIT_TEST(clean_test);
    CPPUNIT_TEST_SUITE_END();

  public:
    file_handler_test();
    void setUp();
    void tearDown();

    void invalid_dir_test();
    void list_generate_test();
    void init_val_test();
    void remove_in_place_test();
    void filter_test();
    void clean_test();
};

class file_hash_test : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(file_hash_test);
  CPPUNIT_TEST(md5_hash_test);
  CPPUNIT_TEST_SUITE_END();
public:
  file_hash_test();
  void setUp();
  void tearDown();

  void md5_hash_test();
};
}
#endif

// class unit_tests
// {
//   public:
// 	//test md5 somehow
// };