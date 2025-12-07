#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>
#include <vector>
#include <queue>

struct gaps {
	uint64_t in{};
	uint64_t out{};
	uint64_t sz{};

	friend bool operator<(gaps const& left, gaps const& right) 
	{ 
		return left.in > right.in; 
	}
};

std::priority_queue<gaps> gq;
std::vector<gaps> gps;

void add_range ( gaps gp )
{
	gps.push_back(gp);
}

void merge_range( gaps gp ) 
{
	std::vector<gaps> gv;
	std::cout << "merge " << gp.in << "-" << gp.out << " queue size:" << gq.size() << "\n"; 
	for(; !gq.empty(); gq.pop()) {
		bool m_in = (gq.top().in >= (gp.in-1)) && (gq.top().in <= (gp.out+1));
		bool m_out = (gq.top().out >= (gp.in-1)) && (gq.top().out <= (gp.out+1));
		bool inside = (gp.in >= gq.top().in) && (gp.out<=gq.top().out);
		bool before = gq.top().out < (gp.in-1);
		std::cout << gq.top().in << "-" << gq.top().out << (m_in ? " in " : "") << (m_out ? " out " : "") << (inside ? " inside " : "") << "\n"; 
		if (m_in || m_out || inside) {
			// merge
			std::cout << "merge " << gq.top().in << "-" << gq.top().out << " and " << gp.in << "-" << gp.out;
			gp.in = std::min(gp.in, gq.top().in);
			gp.out = std::max(gp.out, gq.top().out);
			gp.sz = (gp.out - gp.in) + 1;
			std::cout << " gets " << gp.in << "-" << gp.out << ": " << gp.sz << "\n";
		} else if (before) {
			gv.push_back (gq.top());
		} else {
			break;
		}
	}

	gv.push_back(gp);
	gq.push_range(gv);
}

uint64_t tot_fresh()
{
	uint64_t t = 0;
	for(; !gq.empty(); gq.pop()) {
		t += gq.top().sz;
	}
	return t;
}

bool check_fresh (uint64_t chk)
{
	for (auto g: gps) {
		if (chk >= g.in && chk <= g.out) {
			return true;
		}
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
		size_t lines = 0;
		while (std::getline(fname, line)) {
			std::string::size_type p = line.find('-');
			if(p != std::string::npos) {
				lines++;
				gaps gp;
				gp.in = std::stoull(line.substr(0, p));
				gp.out = std::stoull(line.substr(p+1));
				
				if (gp.out < gp.in)
					continue;

				gp.sz = (gp.out - gp.in) + 1;
				merge_range( gp );
				continue;
			}
		}

		std::cout << "lines: " << lines << "\n";
		std::cout << tot_fresh() << "\n";
	} else {
		return 1;
	}
}
