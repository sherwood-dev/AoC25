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
	uint32_t pass = 0;

	uint64_t tot_old = 0;
	while (1) {
		
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
			if (tmp < 4) {
				std::cout<<"r: "<< r << " c: " << c << " pass:" << pass << "\n";
				grid[r][c]='.';
				tot++;
			}
		}
		c++;
		c %= grid[0].size();
		r += (c == 0) ? 1 : 0;

		if (r == grid.size()) {
			if (tot == tot_old)
				break;
			tot_old = tot;
			pass++;
		}

		r %= grid.size();
	}
	std::cout << "passes: " << pass << "\n";
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
