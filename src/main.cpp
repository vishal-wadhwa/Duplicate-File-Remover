#include "../include/file_handler.h"

int main()
{
    dfr::file_handler ff("../");

    ff.add_extension("png");
    ff.add_extension("jpg");
    ff.add_extension("gif");
    ff.load_directory();

    ff.generate_list();
    // ff.remove_in_place();
    return 0;
}

//features to be added
//-set recursive depth
//-set exclude directory
//-set only some directory
//synchronization: two objects modifying same directory.
//interactive