#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>
#include <vector>

std::vector<std::vector<char>> grid;

uint64_t process_grid () 
{
	uint64_t tot = 0;
	ssize_t r = 0;
	ssize_t c = 0;
	
	while (r < grid.size()) {

		if (grid[r][c]=='@') {
			uint32_t tmp = 0;
			for(ssize_t i= 0; i!=9; i++) {
				ssize_t nr = r - 1 + (i/3);
				ssize_t nc = c - 1 + (i%3);
				if ((nc == c && nr == r) || nc < 0 || nc >= grid[0].size() || nr < 0 || nr >= grid.size())
					continue;

				if (grid[nr][nc]=='@') {
					tmp++;
				}
			}
			std::cout << " r: " << r << " c: " << c << " tot:" << tmp << "\n";
			if (tmp < 4) {
				tot++;
			}
		}
		c++;
		c %= grid[0].size();
		r += (c == 0) ? 1 : 0;
	}
	return tot;
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
		size_t len = 0;
		while (std::getline(fname, line)) {
			std::vector<char> tmp (line.begin(), line.end());
			grid.push_back(tmp);
		}
		
		tot = process_grid();

		std::cout << tot << " \n";
	} else {
		return 1;
	}
}
