# DUPLICATE FILE REMOVER

A command line utility that **recursively** scans the set directory to find exact duplicate files inside all the sub-directories. 
The files so found can be listed in an output file. If required the duplicates can also be removed, thereby preserving a single unique file.

**Features:**
1. Recursive scan of the set directory.
2. Generate list of duplicate files.
3. Scan all files or filter based on file extension.

**Future Plans:**
1. Set a recursive scan depth for the set directory.
2. A way to exclude certain directories.
3. A way to include only some directories.
4. Robust error handling for synchronization issues.
5. Make the program interactive.

> Caution: As of now, there is no way to select which of the duplicate files will be preserved. The selection happens on the order in which they are loaded into `std::map`. The first file is the one which is preserved.

## Downloading and Building
1. Clone the project:

    `git clone https://github.com/vishal-wadhwa/Duplicate-File-Remover.git`

2. Change directory to src:

    `cd src`

3. Build project using Make utility:

    `make main`

4. Run it (See [Usage](#use)):

    `./main ...`

## Testing
1. From the root directory of the project go to test directory:

    `cd test`

2. Build tests using Make utility.

    `make test`

3. Run them tests, bruh:

    `./test`

You should see _OK_ if all the tests pass and then you can go on to using the program. ;)


## <a name="use">Usage</a>

### Other command line params
