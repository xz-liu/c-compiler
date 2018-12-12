#pragma once
#include "../basic/basic.h"
#include "token.h"

struct regex_table {
	std::vector<std::pair<std::regex, token>>  table;
	regex_table();
};
struct token_name_type {
	std::map<token, std::string> _name;
	std::string const& operator[](token t) { return _name[t]; }
	std::string const& operator[](int t) { return _name[token(t)]; }
	token_name_type();
};

extern token_name_type token_name;
typedef std::pair<token, std::string> token_pair;
typedef std::pair<token, std::any> token_item;
typedef std::pair<type_token, size_t> token_P2;

//template< class T> assign_val(token_item const& it, T& val) {
//	try {
//		val = std::any_cast<float>(a);
//		switch (it.first) {
//		case token::char_literal:
//			val = std::any_cast<char>(it.second); break;
//		case token::string_literal:
//			val = std::any_cast<std::string>(it.second); break;
//		case token::double_literal:
//			val = std::any_cast<double>(it.second); break;
//		case token::int_literal:
//			val = std::any_cast<int64_t>(it.second); break;
//		case token::identifier:
//
//			val = std::any_cast<char>(it.second); break;
//		default:
//			break;
//		}
//	} catch (const std::bad_any_cast& e) {
//		std::cout << e.what() << '\n';
//	}
//}

void assign_item(token_item &it, std::string const& s);

std::vector<token_P2>
lex(std::string const& s,
	std::vector<std::string	>& vlit_str,
	std::vector<std::int64_t>& vlit_int,
	std::vector<double		>& vlit_dbl,
	std::vector<char		>& vlit_chr,
	std::vector<std::string	>& vlit_idt,
	std::vector<std::string	>& vlit_file,
	std::vector<int			>& word_pos,
	std::vector<int			> const & lines

);


struct lex_data {
	std::vector<std::string	> vlit_str;
	std::vector<std::int64_t> vlit_int;
	std::vector<double		> vlit_dbl;
	std::vector<char		> vlit_chr;
	std::vector<std::string	> vlit_idt;
	std::vector<std::string	> vlit_file;
	
	std::vector<token_P2> lex_result;
	std::vector<int> word_pos;
	std::vector<int> lines;
	lex_data(std::string const&s,std::vector<int> const&lines):lines(lines) {
		lex_result = lex(s, vlit_str, vlit_int, vlit_dbl, vlit_chr, vlit_idt, vlit_file ,word_pos, lines);
	}

	std::string in_line_and_chr(int now) {
		std::string report;
		auto line = std::lower_bound(lines.begin(), lines.end(), word_pos[now]);
		if (*line != word_pos[now] )line--;

		int chr = word_pos[now] - *line;
		report += std::string("In line ") + std::to_string(distance(lines.begin(), line))
			+ ", char " + std::to_string(chr) + ":";
		return report;
	}

	std::string const& get_id( int now) const{
		return vlit_idt[lex_result[now].second];
	}
	std::string const& get_str(int now) const {
		return vlit_str[lex_result[now].second];
	}

	int64_t get_int(int now) const {
		return vlit_int[lex_result[now].second];
	}

	double get_double(int now) const {
		return vlit_dbl[lex_result[now].second];
	}

	char get_char(int now) const {
		return vlit_chr[lex_result[now].second];
	}


	template <class T> void output_vector(std::vector <T> const& v) {
		for (auto &i : v) { std::cout << "{" << i << "} "; }
		std::cout << std::endl;
	}

	int find_first_pos(int now) {
		int now_it = lex_result[now].second;
		for (int i = 0; i < lex_result.size();i++) {
			if (lex_result[i].first==type_token::identifier&& lex_result[i].second == now_it)return i;
		}
		return now;
	}

	template<class T1, class T2>
	static bool same_token(T1 a, T2 b) {
		return (int)(a) == (int)(b);
	}
	bool cmp_token(size_t pos, token tok) const {
		if (pos >= lex_result.size()) return false;
		type_token t = lex_result[pos].first;
		switch (t) {
		case type_token::keyword:
		case type_token::cpp_keyword:
		case type_token::delimiter:
			return same_token(lex_result[pos].second, tok);
		case type_token::double_literal:
			return same_token(token::double_literal, tok);
		case type_token::int_literal:
			return same_token(token::int_literal, tok);
		case type_token::char_literal:
			return same_token(token::char_literal, tok);
		case type_token::string_literal:
			return same_token(token::string_literal, tok);
		case type_token::identifier:
			return same_token(token::identifier, tok);
		case type_token::dummy:
			return false;
			break;
		default:
			break;
		}
		return false;
	}
	std::string get_token_name ( size_t pos) const {
		return token_name[get_token(pos)];
	}
	type_token get_type_token(size_t pos) const{
		return lex_result[pos].first;
	}
	token get_token(size_t pos)const {
		if (pos >= lex_result.size()) return token::dummy;
		type_token t = lex_result[pos].first;
		switch (t) {
		case type_token::keyword:
		case type_token::cpp_keyword:
		case type_token::delimiter:
			return token(lex_result[pos].second);
		case type_token::double_literal:
			return (token::double_literal);
		case type_token::int_literal:
			return(token::int_literal);
		case type_token::char_literal:
			return (token::char_literal);
		case type_token::string_literal:
			return (token::string_literal);
		case type_token::identifier:
			return (token::identifier);
		case type_token::dummy:
			return token::dummy;
			break;
		default:
			break;
		}
		return token::dummy;
	}
	void debug() {
		std::cout << "STRING LIST:";
		output_vector(vlit_str);
		std::cout << "INT LIST:";
		output_vector(vlit_int);
		std::cout << "FLOAT LIST:";
		output_vector(vlit_dbl);
		std::cout << "CHAR LIST:";
		output_vector(vlit_chr);
		std::cout << "ID LIST:";
		output_vector(vlit_idt);
		output_vector(vlit_file);
		for (auto r : lex_result) {
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
	}
};
