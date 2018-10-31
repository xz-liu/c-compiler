
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include "lex\lex.h"
#include "error\error.h"

template <class T> void output_vector(std::vector <T> const& v) {
	for (auto &i : v) { std::cout << "{" << i << "} "; }
	std::cout << std::endl;
}

int main() {
	freopen("D:\\lextest.c", "r", stdin);
	try {
		char c; std::string s;
		while ((c = getchar()) != EOF) {
			s.push_back(c);
		}
		std::vector<std::string	> vlit_str;
		std::vector<std::int64_t> vlit_int;
		std::vector<double		> vlit_dbl;
		std::vector<char		> vlit_chr;
		std::vector<std::string	> vlit_idt;
		std::vector<std::string	> vlit_file;
		auto res = lex(s, vlit_str, vlit_int, vlit_dbl, vlit_chr, vlit_idt, vlit_file);
		output_vector(vlit_str);
		output_vector(vlit_int);
		output_vector(vlit_dbl);
		output_vector(vlit_chr);
		output_vector(vlit_idt);
		output_vector(vlit_file);
		for (auto r : res) {
			std::cout << nameof(r.first) << "\t: " << r.second << " { ";
			switch (r.first) {
			case type_token::keyword:
			case type_token::cpp_keyword:
			case type_token::delimiter:
				std::cout << token_name[r.second];
				break;
			case type_token::double_literal:
				std::cout << vlit_dbl[r.second];
				break;
			case type_token::int_literal:
				std::cout << vlit_int[r.second];
				break;
			case type_token::char_literal:
				std::cout << vlit_chr[r.second];
				break;
			case type_token::string_literal:
				std::cout << vlit_str[r.second];
				break;
			case type_token::include_file:
				std::cout << vlit_file[r.second];
				break;
			case type_token::identifier:

				std::cout << vlit_idt[r.second];
				break;
			default:
				break;
			}
			std::cout << " }" << std::endl;
		}
	} catch (std::regex_error e) {
		std::cout << e.what() << "\n"
			<< e.code() << std::endl;
	} catch (lex_error e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "UNKNOWN ERROR!" << std::endl;
	}
	while (1);
	return 0;
}