#include "../include/file_handler.h"
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <regex>

/*

DFA STRUCTURE TO PROCESS COMMAND LINE ARGUMENTS.

Input alphabets:

0 - -d
1 - -e
2 - -h
3 - -o
4 - -r
5 - word

States:

0 start (S) - final
1 dth (D) - non-final
2 lth (L) - final
3 rth (R) - final
4 eth (E) - non-final
5 eth_aux - final
6 hth/trap (T/H) ->trap state - non-final
*/

int dfa[7][6];
std::unordered_map<char, int> inp_map = {{'d', 0},
                                         {'e', 1},
                                         {'h', 2},
                                         {'l', 3},
                                         {'r', 4}};

void init_dfa()
{
    std::fill(&dfa[0][0], &dfa[0][0] + 7 * 6, 6);

    //S
    dfa[0][0] = 1;
    dfa[0][1] = 4;
    dfa[0][3] = 2;
    dfa[0][4] = 3;
    //D
    dfa[1][5] = 0;
    //L
    dfa[2][0] = 1;
    dfa[2][1] = 4;
    dfa[2][3] = 2;
    dfa[2][4] = 3;
    dfa[2][5] = 0;
    //R
    dfa[3][0] = 1;
    dfa[3][1] = 4;
    dfa[3][3] = 2;
    dfa[3][4] = 3;
    //E
    dfa[4][5] = 5;
    //Eth_aux
    dfa[5][0] = 1;
    dfa[5][1] = 4;
    dfa[5][3] = 2;
    dfa[5][4] = 3;
    dfa[5][5] = 5;
    //T/H
}

void usage_msg(char *filename)
{
    std::cout << "\nUsage: " << filename << " -d [DIRECTORY]\n";
    std::cout << "  or: " << filename << " -d [DIRECTORY] -e [EXTENSIONS]...\n";
    std::cout << "  or: " << filename << " -d [DIRECTORY] -o [OUTFILE]\n\n";
    std::cout << "Scan the provided directory and its sub-directories recursively and find duplicates.\n\n";

    std::cout << "Not using either of -o or -r switch is pointless as no action is performed.\n\n";
    std::cout << "-d switch is necessary to set the search directory.\n\n";

    std::cout << "Other switches:\n";
    std::cout << "    -d\t\t"
              << "provided argument is the directory to be scanned.\n";
    std::cout << "    -e\t\t"
              << "following arguments treated as extensions.\n";
    std::cout << "    -o\t\t"
              << "generate file list (default file: \"dupl_file.txt\").\n";
    std::cout << "    -h\t\t"
              << "prints this help.\n";
    std::cout << "    -r\t\t"
              << "remove the duplicates so found.\n";
}

int main(int argc, char *argv[])
{
    init_dfa();
    int q = 0, pq = 0, i;
    bool gen_list = false, remov = false, dir_set = false;
    std::string outfile = "";
    dfr::file_handler fh;
    for (i = 1; i < argc; ++i)
    {
        if (std::regex_match(argv[i], std::regex("-[dhrle]")))
            q = dfa[q][inp_map[argv[i][1]]];
        else
        {
            ///Inpput alphabet is a word.
            switch (q)
            {
            case 1:
                fh.set_directory(argv[i]);
                break;
            case 2:
                outfile = argv[i];
                break;
            case 4:
            case 5:
                fh.add_extension(argv[i]);
            }
            q = dfa[q][5];
        }
        if (pq == 1 && q == 0)
            dir_set = true;
        if (q == 2)
            gen_list = true;
        if (q == 3)
            remov = true;

        pq = q;
    }
    //this check, if 'D' has been visited, can be accomodated in dfa
    //but it would make the dfa more complex(more states) :(
    if (!dir_set)
        q = 6;

    //final states
    if (q == 0 || q == 2 || q == 3 || q == 5)
    {
        fh.load_directory();
        if (gen_list)
        {
            if (outfile.empty())
                fh.generate_list();
            else
                fh.generate_list(outfile);
        }
        if (remov)
            fh.remove_in_place();
    }
    else
        usage_msg(argv[0]);

    return 0;
}

//features to be added
//-set recursive depth
//-set exclude directory
//-set only some directory
//synchronization: two objects modifying same directory.
//interactive