#include "Extractor.hpp"

Extractor::Extractor(const char *file_name)
{
	setFile(file_name);
}

Extractor::~Extractor()
{
	_free();
}

void Extractor::setFile(const char *file_name)
{
	if (_file) {
		_free();
	}
	_file_name = file_name;
	_file = fopen(file_name, "rb");
	if (!_file) {
		throw std::runtime_error(std::string("unable to open file (") + file_name + ")");
	}
}

unsigned long Extractor::search()
{
	fseek(_file, 0, SEEK_SET);
	unsigned char buffer[5] {0};
	unsigned long size;

	do {
		// look for "RIFF"
		fread(buffer, 1, 1, _file);
		if (buffer[0] != 'R') {
			continue;
		}
		fread(buffer + 1, 1, 3, _file);
		if (strcmp((char *)buffer, "RIFF")) {
			fseek(_file, -3, SEEK_CUR);
			continue;
		}
		// read size
		fread(buffer, 1, 4, _file);
		size = 0UL + buffer[0] + buffer[1] * 256 + buffer[2] * (256 << 8) + buffer[3] * (256 << 16) + 8;

		// verify
		fread(buffer, 1, 4, _file);
		if (strcmp((char *)buffer, "WAVE")) {
			fseek(_file, -8, SEEK_CUR);
			continue;
		} else {
			push_back(new WaveFile(_file, ftell(_file) - 12, size));
		}

	} while (!feof(_file));

	return this->size();
}

std::string& Extractor::getFileName()
{
	return _file_name;
}

void Extractor::_free() {
	for (WaveFile *waveFile : *this) {
		delete waveFile;
	}
	fclose(_file);
}
