#include "unit_tests.h"
#include "../include/file_handler.h"
#include "../include/file_hash.h"
#include <boost/filesystem/exception.hpp>
#include <unordered_map>
#include <string>
#include <fstream>

dfr::file_handler_test::file_handler_test() {}
void dfr::file_handler_test::setUp()
{
    //setup for remove_in_place_test
    std::ofstream of("./props/a.txt");
    CPPUNIT_ASSERT_EQUAL(true, of.is_open());
    of << "hllo";
    of.close();

    of.open("./props/b.txt");
    CPPUNIT_ASSERT_EQUAL(true, of.is_open());
    of << "hllo";
    of.close();

    of.open("./props/c.txt");
    CPPUNIT_ASSERT_EQUAL(true, of.is_open());
    of << "hllo";
    of.close();
}

void dfr::file_handler_test::tearDown() {}

void dfr::file_handler_test::invalid_dir_test()
{
    std::unordered_map<std::string, bool> test_dir = {
        {"", false},
        {"_._-.", false},
        {"props/inaccessible", true},
        {".", true},
        {"../", true},
        {"..", true},
        {"/home/vishal/Desktop/dupl/tests/", true}};

    for (auto &p : test_dir)
    {
        file_handler fho;
        fho.set_directory(p.first);
        CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE(
            std::string("Failed at ") + p.first,
            CPPUNIT_ASSERT_EQUAL(p.second, fho.load_directory()));
    }
}

void dfr::file_handler_test::list_generate_test()
{
    file_handler fho(".");
    fho.load_directory();
    CPPUNIT_ASSERT_EQUAL(false, fho.generate_list("."));
    CPPUNIT_ASSERT_EQUAL(true, fho.generate_list("./props/lst.txt"));
    std::ifstream fi("./props/lst.txt");
    CPPUNIT_ASSERT_EQUAL(true, fi.is_open());
    fi.close();
    CPPUNIT_ASSERT_EQUAL(false, fho.generate_list("./props/inaccessible/lst.txt"));
}

void dfr::file_handler_test::init_val_test()
{
    file_handler fho(".");
    CPPUNIT_ASSERT_EQUAL((size_t)0, fho.distinct_file_count());
    CPPUNIT_ASSERT_EQUAL((size_t)0, fho.total_hashed_file_count());
}

void dfr::file_handler_test::remove_in_place_test()
{
    file_handler fho(".");
    fho.load_directory();
    CPPUNIT_ASSERT_EQUAL(true, fho.remove_in_place());
    setUp();
    remove("./props/a.txt");
    CPPUNIT_ASSERT_EQUAL(true, fho.remove_in_place());
    //no errors because this was the first file, so it wasn't going to be deleted anyway

    setUp();
    remove("./props/c.txt");
    CPPUNIT_ASSERT_EQUAL(false, fho.remove_in_place());
}

void dfr::file_handler_test::filter_test() {
    file_handler fho;
    fho.set_directory(".");
    fho.add_extension("cpp");
    fho.load_directory();
    CPPUNIT_ASSERT_EQUAL((size_t)2, fho.total_hashed_file_count());
    
    file_handler fho1;
    fho1.set_directory(".");
    fho1.add_extension(".cpp");
    fho1.load_directory();
    CPPUNIT_ASSERT_EQUAL((size_t)0, fho1.total_hashed_file_count());    
}

void dfr::file_handler_test::clean_test() {
    file_handler fho(".");
    fho.load_directory();
    size_t c1 = fho.total_hashed_file_count();

    fho.set_directory("./props/");
    fho.load_directory();
    size_t c2 = fho.total_hashed_file_count();
    CPPUNIT_ASSERT(c1 != c2);
}

dfr::file_hash_test::file_hash_test() {}
void dfr::file_hash_test::setUp() {
    std::ofstream of("props/blah.blah");
    of << "random.text";
    of << 12;
    of << '\r';
    of << '\t';
    of << '\n';
    of << -1e12;
    of << "endddd";

    of.close();

    of.open("props/blank.file");
    of.close();
}
void dfr::file_hash_test::tearDown() {}

void dfr::file_hash_test::md5_hash_test() {
    CPPUNIT_ASSERT_EQUAL(std::string("d41d8cd98f00b204e9800998ecf8427e"), dfr::hash::MD5("props/blank.file"));
    CPPUNIT_ASSERT_EQUAL(std::string("53d9f7fdbde588c8e887d37001ed95c5"), dfr::hash::MD5("props/blah.blah"));
    CPPUNIT_ASSERT_EQUAL(std::string(""), dfr::hash::MD5("non_existent_dir"));
}

