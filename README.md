# wavextract

**wavextract** is a simple tool to find and extract wav files from any kind of binary files, like data files of games.
Please note, that wavextract can only successfully find wav files that are included in a raw, unencrypted form.

	usage: wavextract [-v] [-h] [-s] [-o <path>] <file1> [file2 ...]
	-h        show this help message
	-o <path> save files to specified directory
	-s        don't save files, only search
	-v        verbose mode

## Build & Install

All you need for building wavextract is CMake and a C\++ compiler compatible with C\++11.

To build on Linux:

	mkdir build
	cd build
	cmake ..
	make

And to install:

	sudo make install
