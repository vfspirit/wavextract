#ifndef WAVEXTRACT_WAVEFILE_HPP
#define WAVEXTRACT_WAVEFILE_HPP

#include <stdexcept>
#include <string>
#include <cstdio>

class WaveFile {
public:
	WaveFile(FILE *file, long offset, unsigned long size);
	void save(const char *path);
private:
	FILE *_file;
	long _offset;
	unsigned long _size;
};

#endif //WAVEXTRACT_WAVEFILE_HPP
