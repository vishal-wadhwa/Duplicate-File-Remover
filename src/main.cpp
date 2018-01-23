#include "../include/file_handler.h"

int main()
{
    file_handler ff("/home/vishal/Desktop/dupl/");

    ff.add_extension("png");
    ff.add_extension("jpg");
    ff.add_extension("gif");
    ff.load_directory();

    ff.generate_list();
    ff.remove_in_place();
    return 0;
}

//g++ test.cpp file_handler.cpp -o out -lcrypto -std=c++14 -lboost_system -lboost_filesystem -Wall -pedantic -Wextra