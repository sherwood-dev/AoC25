#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>
#include <vector>
#include <queue>
#include <cctype>
#include <numeric>
#include <sstream>
#include <iterator>
#include <ranges>
#include <iostream>

std::vector<std::vector<char>> raw;

uint64_t make_num(size_t col, uint64_t st)
{
	if (col >= raw[0].size())
		return st;

	uint64_t num = 0;
	for (size_t r=0; r!= raw.size()-1; r++) {
		if (!std::isspace(static_cast<unsigned char>(raw[r][col]))) {
			num*=10;
			num+= (raw[r][col]-'0');
		}
	}
	std::cout << "c=" << col << " num=" << num << "\n";
	return std::max(num, st);
}

size_t find_next_op(size_t r, size_t sc)
{
	for (size_t c = sc; c < raw[0].size(); c++) {
		if (!std::isspace(static_cast<unsigned char>(raw[r][c])))
			return c;
	}
	return raw[0].size();
}

uint64_t do_math()
{
	size_t c = 0;
	auto nc = find_next_op(raw.size()-1, c+1);
	uint64_t tot = 0;
	
	while (c < raw[0].size()) {
		char op = raw[raw.size()-1][c];
		uint64_t loc_tot = (op=='+') ? 0 :1;
		for (size_t sc=c; sc!=nc; sc++)
			loc_tot = (op == '+') ? loc_tot + make_num(sc,0): loc_tot*make_num(sc,1);
		std::cout << "c= " << c << " subtotal =" << loc_tot << "\n"; 
		tot += loc_tot;
		c = nc;
		nc = find_next_op(raw.size()-1, c+1);
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

	if (fname.is_open()) {
		std::string line;
		while (std::getline(fname, line)) {
			if (line.empty()) continue;
			std::istringstream stream(line);
			
			std::vector<char> tmpv{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
			raw.push_back(tmpv);
		}
		std::cout << "raw size :" << raw.size() << "x" << raw[0].size() << "\n";		
		std::cout << "also " << raw[raw.size()-1].size() << "\n";
		for (auto c: raw[raw.size()-1])
			std::cout << c;
		std::cout << "\n";
		std::cout << do_math() << " \n";
	} else {
		return 1;
	}
}
