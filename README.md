# DUPLICATE FILE REMOVER

[GitHub](https://github.com/vishal-wadhwa/Duplicate-File-Remover)

A command line utility that __recursively__ scans the set directory to find exact duplicate files inside all the sub-directories. 
The files so found can be listed in an output file. If required the duplicates can also be removed, thereby preserving a single unique file.

<a href="https://asciinema.org/a/CgLfUrJvV3If2ifGZNhdDC8iu?autoplay=1&preload=1"><img src="https://asciinema.org/a/CgLfUrJvV3If2ifGZNhdDC8iu.png" width="640"/></a>

__Features:__
1. Recursive scan of the set directory.
2. Generate list of duplicate files.
3. Scan all files or filter based on file extension.

__Future Plans:__
1. Set a recursive scan depth for the set directory.
2. A way to exclude certain directories.
3. A way to include only some directories.
4. Robust error handling for synchronization issues.
5. Make the program interactive.

> Caution: As of now, there is no way to select which of the duplicate files will be preserved. The selection happens on the order in which they are loaded into `std::map`. The first file is the one which is preserved.

## <a name="dep">Dependencies</a>:
1. For main program:

    `sudo apt-get install libssl-dev libboost-filesystem-dev libboost-system-dev`

2. For tests, apart from the dependencies for main program:

    `sudo apt-get install libcppunit-dev`

## Downloading and Building
1. Clone the project:

    `git clone https://github.com/vishal-wadhwa/Duplicate-File-Remover.git`

2. Change directory to src:

    `cd Duplicate-File-Remover/src`

3. Build project using Make utility (assuming you've downloaded the [dependencies](#dep)):

    `make main`

4. Run it (See [Usage](#use)):

    `./main ...`

## Testing
1. From the root directory of the project go to tests directory:

    `cd Duplicate-File-Remover/tests`

2. Build tests using Make utility (assuming you've downloaded the [dependencies](#dep)):

    `make test`

3. Run them tests, bruh:

    `./test`

You should see _OK_ if all the tests pass and then you can go on to using the program. ;)


## <a name="use">Usage</a>
1. Use `-d` switch to set the directory to be scanned.
2. Use `-e` switch to provide a list of extensions to filter the files scanned.
3. Use `-l` switch to generate an output(log) file. If this switch is not followed by a name/path, then a default file _dupl_file.txt_ is generated in the current directory.
4. Use `-r` switch to remove the duplicates and keep only one copy.
5. Use `-h` switch to display this help:
    
```
Usage: ./main -d [DIRECTORY]
or: ./main -d [DIRECTORY] -e [EXTENSIONS]...
or: ./main -d [DIRECTORY] -l [OUTFILE]

Scan the provided directory and its sub-directories recursively and find duplicates.

Not using either of -l or -r switch is pointless as no action is performed.

-d switch is necessary to set the search directory.

Other switches:
    -d		provided argument is the directory to be scanned.
    -e		following arguments treated as extensions.
    -l		generate file list (default file: "dupl_file.txt").
    -h		prints this help.
    -r		remove the duplicates so found.
```
> Note: Use `sudo` if required.

## Examples
1. `./main -d ./ -l -r`
2. `./main -e png jpg jpeg -d ./../ -l log.out`
3. `./main -d ./ -r`
