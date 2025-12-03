#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>


// save max value of len digits.
// start at most significant. go right.
// higher ? delete left
// go left, check again.
// equal / lower go right.
uint64_t max_jolt(std::string s, size_t len) 
{
	uint64_t max_sub = 0;
	std::string::size_type pos = 0;

	while (s.size() > len) {
		uint8_t last = s[pos++];
		if (pos >= s.size()) {
			break;
		}

		if (s[pos] > last) {	
			pos--;
			s.erase(pos, 1);
			pos = pos > 0 ? pos - 1 : pos;
		}
		
		uint64_t tmp = std::stoull(s.substr(0, len));
		max_sub = std::max(max_sub, tmp);
	}

	return max_sub;
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
			uint64_t jolt = max_jolt(line, 12);
			std::cout << jolt << " :: " << line << "\n";
			tot += jolt;
		}
		std::cout << tot << " \n";
	} else {
		return 1;
	}
}
