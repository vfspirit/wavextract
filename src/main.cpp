#include "main.hpp"

int main(int argc, char *argv[])
{
	conf_t config {false, false, ""};

	if (!process_args(argc, argv, config)) {
		print_help();
		return 0;
	}

	Extractor extractors[config.files.size()];
	unsigned long found;

	try {
		for (int i = 0; i < config.files.size(); ++i) {
			extractors[i].setFile(config.files[i]);
			if (config.verbose) {
				std::cout << config.files[i] << ": ";
				std::cout.flush();
			}

			found = extractors[i].search();

			if (config.verbose) {
				std::cout << found << " wavs found" << std::endl;
			}

			// save files
			if (!config.simulate) {
				if (config.output_path != "" && config.output_path[config.output_path.size() - 1] != '/') {
					config.output_path += '/';
				}
				for (int ii = 0; ii < extractors[i].size(); ++ii) {
					std::string file_name = config.output_path + extractors[i].getFileName() + "_" + std::to_string(ii) + ".wav";
					extractors[i][ii]->save(file_name.c_str());
				}
			}
		}
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}

void print_help()
{
	std::cout << "wavextract -- search wav files inside any binary files\n"
		<< "usage: wavextract [-v] [-h] [-s] [-o <path>] <file1> [file2 ...]\n"
		<< "\t-h        show this help message\n"
		<< "\t-o <path> save files to specified directory\n"
		<< "\t-s        don't save files, only search\n"
		<< "\t-v        verbose mode\n";
}

bool process_args(int argc, char **argv, conf_t &config)
{
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-h")) {
			return false;
		} else if (!strcmp(argv[i], "-v")) {
			config.verbose = true;
		} else if (!strcmp(argv[i], "-s")) {
			config.simulate = true;
		} else if (!strcmp(argv[i], "-o")) {
			if (i < argc - 1) {
				config.output_path = argv[++i];
			} else {
				return false;
			}
		} else {
			config.files.push_back(argv[i]);
		}
	}

	if (config.files.size() > 0) {
		return true;
	} else {
		return false;
	}
}
