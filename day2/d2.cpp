#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>

bool check_dig (uint64_t dig) 
{
	uint64_t ret = 0;
	uint64_t mask = 10;
	if (dig < mask)
		return false;
	// check for repeating numbers
	while (mask < dig) {
		uint64_t rep = dig % mask;
		uint64_t tmp = dig / mask;
		while (tmp && (tmp % mask == rep) && ((rep*10) >=mask)) {
			tmp /= mask;
		}

	//	if (rep == tmp && ((rep*10) >= mask )) {
		if (!tmp) {
			std::cout << " chk: " << dig << " " << rep <<"==" << tmp << "\n";
			return true;
		}
		mask *=10;
	}
	return false;
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
		while (std::getline(fname, line,',')) {
			std::string::size_type n = line.find("-");
			if (line.size() <= 3 || std::string::npos == n) {
				continue;
			}
			
			uint64_t in = std::stoull(line.substr(0,n));
			uint64_t out = std::stoull(line.substr(n+1));
			
			if (in >= out)
				continue;

			uint64_t tst = in;

			std::cout << "check " << in << " to " << out << "\n";
			while (tst <= out) {
				tot += check_dig(tst) ? tst : 0;
				tst++;
			}
		}
		std::cout << tot << " \n";
	} else {
		return 1;
	}
}
