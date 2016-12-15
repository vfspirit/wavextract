#ifndef WAVEXTRACT_MAIN_HPP
#define WAVEXTRACT_MAIN_HPP

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include "Extractor.hpp"
#include "WaveFile.hpp"

struct conf_t {
	bool verbose;
	bool simulate;
	std::string output_path;
	std::vector<char *> files;
};

int main(int argc, char *argv[]);
void print_help();

/**
 * process_args - Process the command line arguments
 * @return true if program can continue, false if help is needed
 */
bool process_args(int argc, char **argv, conf_t &config);

#endif //WAVEXTRACT_MAIN_HPP
