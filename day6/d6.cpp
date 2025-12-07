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

std::vector<std::vector<uint64_t>> nums;
std::vector<char> ops;

uint64_t do_math()
{
	std::vector<uint64_t> tots{nums[0]};
	std::cout << "nums r:" << nums.size() << " c:" << nums[0].size() << " ops size:" << ops.size() << "\n";
	for (size_t r=1; r!=nums.size(); r++) {
		for (size_t c=0; c!=nums[0].size(); c++) {
			switch(ops[c]) {
				case '*': {
				tots[c] *= nums[r][c];
				} break;

				case '+': {
				tots[c] += nums[r][c];
				} break;

				default: {
				std::cout << "this is bad \n";
				} break;
			}
		}
	}
    	
	auto max_it = std::max_element(tots.begin(), tots.end());

    	int max_index = std::distance(tots.begin(), max_it);

    	int max_value = *max_it;

    	std::cout << "Max Value: " << max_value << std::endl;
    	std::cout << "Max Index: " << max_index << std::endl;
	std::cout << "tots: " << tots[0] << " " << tots[1] << "\n";
	
	uint64_t t_scalar = 0;
	for (auto n: tots) t_scalar += n;
	return t_scalar;
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
			auto trimmed_view = line | std::ranges::views::drop_while(static_cast<int(*)(int)>(std::isspace));
			std::string new_line(trimmed_view.begin(), trimmed_view.end());
			std::istringstream stream(new_line);
			
			if (std::isdigit(static_cast<unsigned char>(stream.peek()))) {
				std::vector<uint64_t> tmpv{std::istream_iterator<uint64_t>(stream), std::istream_iterator<uint64_t>()};
				nums.push_back(tmpv);
			} else {
				std::copy(
        				std::istream_iterator<char>(stream),
        				std::istream_iterator<char>(),
        				std::back_inserter(ops)
    				);
			}
		}
			
		std::cout << do_math() << " \n";
	} else {
		return 1;
	}
}
