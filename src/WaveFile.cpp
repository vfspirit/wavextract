#include "WaveFile.hpp"

WaveFile::WaveFile(FILE *file, long offset, unsigned long size)
{
	_file = file;
	_offset = offset;
	_size = size;
}

void WaveFile::save(const char *path)
{
	// prepare buffer, save current position
	FILE *output = fopen(path, "wb");
	if (!output) {
		throw std::runtime_error(std::string("can't write to \"") + path + "\"");
	}
	unsigned char *buffer = new unsigned char[_size];
	long original_pos = ftell(_file);

	// perform copy
	fseek(_file, _offset, SEEK_SET);
	if (fread(buffer, _size, 1, _file) != 1) {
		throw std::runtime_error(std::string("read error (") + path + ")");
	}
	if (fwrite(buffer, _size, 1, output) != 1) {
		throw std::runtime_error(std::string("write error (") + path + ")");
	}
	fflush(_file);

	// restore position, free buffer
	fseek(_file, original_pos, SEEK_SET);
	delete[] buffer;
	fclose(output);
}
