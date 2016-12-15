#ifndef WAVEXTRACT_EXTRACTOR_HPP
#define WAVEXTRACT_EXTRACTOR_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include "WaveFile.hpp"

class Extractor : public std::vector<WaveFile *> {
public:
	Extractor() = default;
	Extractor(const char *file_name);
	~Extractor();
	void setFile(const char *file_name);
	unsigned long search();
	std::string& getFileName();
private:
	void _free();

	std::string _file_name;
	FILE *_file = nullptr;
};

#endif //WAVEXTRACT_EXTRACTOR_HPP
