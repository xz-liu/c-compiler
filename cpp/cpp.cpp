#include "cpp.h"

void discard_comments(std::istream& item, std::string& out) {
	std::istreambuf_iterator<char> first(item), last;
	std::string whole(first, last);
	std::regex discard(R"**(/\*.*\*/|//(^[\n\r])*[\n\r]|\\[\t\s]*[\n\r])**");
	std::regex_replace(out, whole.begin(), whole.end(), discard, "");
}



cpp::cpp() {}

std::vector<token_pair> cpp::operator()
(std::string const& dir, std::istream &in, std::ostream &out) {
	std::string whole;
	discard_comments(in, whole);
	auto items = lex(whole);
	auto equals = [&](int rk,token tk)->bool {
		if (rk<0 || rk>items.size())return false;
		return items[rk].first == tk;
	};
#	define lasteq(k,tk) if(equals(i-k,tk))
	for (int i = 0; i < items.size(); i++) {
		token_pair& now = items[i];
		lasteq(0,token::identifier) {
			auto it = mdefines.find(now.second);
			if (it != mdefines.end())now.second = it->second;
		}
		lasteq(2,token::hash){
			lasteq(1, token::tokinclude) {
				lasteq(0, token::include_file) {

				}
			}
		}
	}
}
