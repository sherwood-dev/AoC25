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

// strings would make more sense, but p2 is probs going to be buck.
std::vector<std::vector<char>> raw;

uint64_t split_beams()
{
	uint64_t tot_splits = 0;
	std::vector<uint64_t> t_in (raw[0].size(), 0);
	std::vector<uint64_t> t_out (raw[0].size(), 0);
	size_t r_in = 0;
	size_t r_out= 1;
	uint64_t t_l = 0;
	
	
	while (r_out < raw.size()) {
		
		uint32_t b_in_ct = std::count(raw[r_in].begin(),raw[r_in].end(),'S');
		auto b_it = std::find(raw[r_in].begin(),raw[r_in].end(), 'S');
		while (b_it!=raw[r_in].end()) {
			
			ptrdiff_t b_idx = std::distance(raw[r_in].begin(), b_it);
			switch(raw[r_out][b_idx]) {
				case '.':
				case 'S':
					raw[r_out][b_idx] = 'S';
					t_out[b_idx] += (t_in[b_idx] ==0) ? 1 : t_in[b_idx];
					break;
				
				case '^':
					tot_splits++;
					if (b_idx > 0 && b_idx < raw[r_out].size()-1) 
					if (b_idx > 0) {
						raw[r_out][b_idx-1] = 'S';
						t_out[b_idx-1] += t_in[b_idx];
					}
					if (b_idx < raw[r_out].size()-1) {
						raw[r_out][b_idx+1] = 'S';
						t_out[b_idx+1] += t_in[b_idx];
					}
					break;

				default:
					break;
			}
			std::advance(b_it,1);
			b_it = std::find(b_it,raw[r_in].end(), 'S'); 
		}
		
		t_l = 0;
		for (auto t: t_out) {
			t_l += t;
			// std::cout << t << " ";
		}
		uint32_t b_out_ct = std::count(raw[r_out].begin(),raw[r_out].end(),'S');
		// std::cout << "line:" << r_out << " in: " << b_in_ct << " out:" << b_out_ct << " tls: " << t_l << "\n";
		r_in++;
		r_out++;
		std::swap(t_in, t_out);
		std::fill(t_out.begin(), t_out.end(), 0);

	}
	std::cout << "ways: " << t_l << "\n";
	return tot_splits;
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
		std::cout << "raw size (rxc) :" << raw.size() << "x" << raw[0].size() << "\n";		
		std::cout << split_beams() << " \n";
	} else {
		return 1;
	}
}
