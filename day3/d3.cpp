#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>

uint64_t max_jolt(std::string s) 
{
	uint64_t last = 0;
	uint64_t spec = 0;
	for (auto c: s) {
		uint32_t tmp = c-'0';
		last = (spec > last) ? spec + tmp : ((tmp > (last % 10)) ? (last - (last % 10) + tmp) : last);
		spec = ((tmp * 10) > spec) ? tmp * 10 : spec;
	}

	return last;
}

int main( int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "no filename\n";
		return EXIT_FAILURE;
	}

	std::ifstream fname(argv[1], std::ios::binary | std::ios::in);
	std::string line;


	if (fname.is_open()) {
		uint64_t tot = 0;
		while (std::getline(fname, line)) {
			uint32_t jolt = max_jolt(line);
			std::cout << jolt << " :: " << line << "\n";
			tot += jolt;
		}
		std::cout << tot << " \n";
	} else {
		return 1;
	}
}
