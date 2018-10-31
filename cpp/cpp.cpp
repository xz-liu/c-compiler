#define _CRT_SECURE_NO_WARNINGS
#include "cpp.h"
#include "../error/error.h"
//void discard_comments(std::istream& item, std::string& out) {
//	std::istreambuf_iterator<char> first(item), last;
//	std::string whole(first, last);
//	std::regex discard(R"**(/\*.*\*/|//(^[\n\r])*[\n\r]|\\[\t\s]*[\n\r])**");
//	std::regex_replace(out, whole.begin(), whole.end(), discard, "");
//}

enum class action{
	defid,
	deffunc,
	undef,
	acif,
	acignore
};

cpp::cpp() {}

//std::vector<token_pair> cpp::operator()
//(std::string const& dir, std::istream &in, std::ostream &out) {
//	std::string whole;
//	discard_comments(in, whole);
//	auto items = lex(whole);
//	auto equals = [&](int rk,token tk)->bool {
//		if (rk<0 || rk>items.size())return false;
//		return items[rk].first == tk;
//	};
//#	define lasteq(k,tk) if(equals(i-k,tk))
//	for (int i = 0; i < items.size(); i++) {
//		token_pair& now = items[i];
//		lasteq(0,token::identifier) {
//			auto it = mdefines.find(now.second);
//			if (it != mdefines.end())now.second = it->second;
//		}
//		lasteq(2,token::hash){
//			lasteq(1, token::tokinclude) {
//				lasteq(0, token::include_file) {
//					std::ifstream ifs(now.second);
//					auto ins = (*this)(dir, ifs, out);
//					ifs.close();
//					items.insert(items.begin() + i, ins.begin(), ins.end());
//				} else lasteq(0, token::string_literal) {
//					std::ifstream ifs(dir+now.second);
//					auto ins = (*this)(dir, ifs, out);
//					ifs.close();
//					items.insert(items.begin() + i, ins.begin(), ins.end());
//				}
//				else {
//					throw(cpp_error("Include file expected"));
//				}
//			} else lasteq(1, token::tokif) {
//
//			} else lasteq(1, token::tokelif) {
//
//			} else lasteq(1, token::tokelse) {
//
//			} else lasteq(1, token::tokif) {
//
//			} else lasteq(1, token::tokendif) {
//
//			} else lasteq(1,token::tokdefine) {
//				lasteq(0, token::identifier) {
//					lasteq(-1, token::identifier) {//define alias
//						auto defined = mdefines.find(now.second);
//						
//					} else lasteq(-1, token::lparenthesis) {//define macro function
//
//					}
//					else throw(cpp_error("Identifier expected, got '", now.second, "' of type '", token_name[now.first], "' ."));
//				} else throw(cpp_error("Identifier expected, got '", now.second, "' of type '", token_name[now.first], "' ."));
//			} else lasteq(1, token::tokundef) {
//
//			} else lasteq(1, token::tokifdef) {
//
//			} else {
//
//			}
//		}
//	}
//	
//}