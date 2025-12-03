#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>

int main( int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "no filename\n";
		return EXIT_FAILURE;
	}

	std::ifstream fname(argv[1], std::ios::binary | std::ios::in);
	std::string line;


	if (fname.is_open()) {
		int pos = 2050;
		int o_pos = pos;
		int z_ct = 0;
		int step = 1;
		while (std::getline(fname, line)) {
			if (line.size() <= 1) {
				continue;
			}
			std::string_view ln(line);
			int t = std::stoi(std::string(ln.substr(1)));
			pos += ln[0] == 'R' ? t : -t;
			int rots = std::abs((pos/100)-(o_pos/100));
			rots -= (o_pos%100 == 0) && (o_pos > pos) ? 1 : 0;
			rots += (pos%100 == 0) && (o_pos > pos) ? 1: 0;
			z_ct+= rots > 0 ? rots : 0;	
			std::cout << "s: " << step << " " << o_pos << " to " << pos << " r: " << rots << " t: " << z_ct << "\n";
			pos += (pos < 2000) ? 2000 : 0;
			o_pos = pos;
			step++;	
		}
		std::cout << z_ct << " 0s\n";
	} else {
		return 1;
	}
}
