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
#include <map>

struct pt {
	int64_t x,y,z;
	bool out;

	pt(const std::vector<uint64_t>& vec) {
            x = vec[0];
            y = vec[1];
            z = vec[2];
        }
	
	pt() : x(0), y(0), z(0) {}
};

std::vector<std::vector<size_t>> c_s;
std::vector<pt> box;
std::map<uint64_t, std::pair<size_t, size_t>> d_map;


uint64_t calc_dist( size_t p1, size_t p2 )
{
	uint64_t d1 = std::llabs(box[p1].x - box[p2].x);
	uint64_t d2 = std::llabs(box[p1].y - box[p2].y);
	uint64_t d3 = std::llabs(box[p1].z - box[p2].z);
	d1 *= d1;
	d2 *= d2;
	d3 *= d3;
	return (d1+d2+d3);
}

void build_map ()
{
	size_t b1=0;
	while (b1 < box.size()) {
		size_t b2=b1;
		while(++b2 < box.size()) {
			uint64_t d = calc_dist(b1,b2);
			d_map[d] = std::make_pair(b1,b2);
		}
		b1++;
	}
}

// top_x > 0
void make_1()
{
	size_t out = box.size();
	for (const auto& [d, p] : d_map) {
		size_t b1 = p.first;
		size_t b2 = p.second;
		auto it1 = c_s.end();
		auto it2 = c_s.end();
		for(auto vit = c_s.begin(); vit!=c_s.end(); vit++) {
			auto t1 = std::find(vit->begin(),vit->end(),b1);
			auto t2 = std::find(vit->begin(),vit->end(),b2);
			it1 = (t1 !=vit->end()) ? vit : it1;
			it2 = (t2 !=vit->end()) ? vit : it2;
			if (it1!=c_s.end() && it2!=c_s.end())
				break;
		}
		
		std::vector<size_t> tmp {b1, b2};
		if (it1 == c_s.end() && it2 == c_s.end()) {
			c_s.push_back(tmp);
		} else if (it1 == c_s.end() && it2 != c_s.end()) {
			it2->push_back(b1);
		} else if (it1 != c_s.end() && it2 == c_s.end()) {
			it1->push_back(b2);
		} else if (it2 != it1) {
			std::ranges::move(*it2, std::back_inserter(*it1));
			c_s.erase(it2);
		}
		
		if (box[b1].out) {
			out--;
			box[b1].out = false;
		}
		
		if (box[b2].out) {
			out--;
			box[b2].out = false;
		}
		
		if (c_s.size() == 1 && out == 0) {
			std::cout << "last prod: " << (box[b1].x * box[b2].x) << "\n";
			break;
		}
	}
	
	std::sort(c_s.begin(), c_s.end(), [](const std::vector<size_t>& a, const std::vector<size_t>& b) {
        	return a.size() > b.size(); 
    	});

	uint64_t tot = 1;
	int ct = 3;
	for (auto v: c_s) {
		std::cout << v.size() << " ";
		tot *= v.size();
		if (--ct == 0) break;
	}

	std::cout << tot << " product \n";
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
		int ct = 0;
		while (std::getline(fname, line)) {
			if (line.empty()) continue;
			std::istringstream line_stream(line);
        		std::string coord;
        		std::vector<uint64_t> tmp;

        		while (std::getline(line_stream, coord, ',')) {
				tmp.push_back(std::stod(coord));
			}
			pt t = tmp;
			t.out = true;
			box.push_back(t);
		}
		build_map();
		make_1();
	} else {
		return 1;
	}
}
