#include "token.h"
#include "lex.h"
#include "../error/error.h"

regex_table::regex_table() :table{
	make_pair(std::regex(R"QWERTY(typedef)QWERTY"),token::toktypedef),
	make_pair(std::regex(R"QWERTY(void)QWERTY"),token::tokvoid),
	make_pair(std::regex(R"QWERTY(const)QWERTY"),token::tokconst),
	make_pair(std::regex(R"QWERTY(volatile)QWERTY"),token::tokvolatile),
	make_pair(std::regex(R"QWERTY(register)QWERTY"),token::tokregister),
	make_pair(std::regex(R"QWERTY(char)QWERTY"),token::tokchar),
	make_pair(std::regex(R"QWERTY(int)QWERTY"),token::tokint),
	make_pair(std::regex(R"QWERTY(unsigned)QWERTY"),token::tokunsigned),
	make_pair(std::regex(R"QWERTY(short)QWERTY"),token::tokshort),
	make_pair(std::regex(R"QWERTY(long)QWERTY"),token::toklong),
	make_pair(std::regex(R"QWERTY(float)QWERTY"),token::tokfloat),
	make_pair(std::regex(R"QWERTY(double)QWERTY"),token::tokdouble),
	make_pair(std::regex(R"QWERTY(sizeof)QWERTY"),token::toksizeof),
	make_pair(std::regex(R"QWERTY(struct)QWERTY"),token::tokstruct),
	make_pair(std::regex(R"QWERTY(enum)QWERTY"),token::tokenum),
	make_pair(std::regex(R"QWERTY(union)QWERTY"),token::tokunion),
	make_pair(std::regex(R"QWERTY(if)QWERTY"),token::tokif),
	make_pair(std::regex(R"QWERTY(else)QWERTY"),token::tokelse),
	make_pair(std::regex(R"QWERTY(do)QWERTY"),token::tokdo),
	make_pair(std::regex(R"QWERTY(for)QWERTY"),token::tokfor),
	make_pair(std::regex(R"QWERTY(while)QWERTY"),token::tokwhile),
	make_pair(std::regex(R"QWERTY(return)QWERTY"),token::tokreturn),
	make_pair(std::regex(R"QWERTY(goto)QWERTY"),token::tokgoto),
	make_pair(std::regex(R"QWERTY(switch)QWERTY"),token::tokswitch),
	make_pair(std::regex(R"QWERTY(case)QWERTY"),token::tokcase),
	make_pair(std::regex(R"QWERTY(default)QWERTY"),token::tokdefault),
	make_pair(std::regex(R"QWERTY(break)QWERTY"),token::tokbreak),
	make_pair(std::regex(R"QWERTY(continue)QWERTY"),token::tokcontinue),
	make_pair(std::regex(R"QWERTY(auto)QWERTY"),token::tokauto),
	make_pair(std::regex(R"QWERTY(extern)QWERTY"),token::tokextern),
	make_pair(std::regex(R"QWERTY(static)QWERTY"),token::tokstatic),
	make_pair(std::regex(R"QWERTY(pragma)QWERTY"),token::tokpragma),
	make_pair(std::regex(R"QWERTY(include)QWERTY"),token::tokinclude),
	make_pair(std::regex(R"QWERTY(define)QWERTY"),token::tokdefine),
	make_pair(std::regex(R"QWERTY(undef)QWERTY"),token::tokundef),
	make_pair(std::regex(R"QWERTY(ifdef)QWERTY"),token::tokifdef),
	make_pair(std::regex(R"QWERTY(elif)QWERTY"),token::tokelif),
	make_pair(std::regex(R"QWERTY(endif)QWERTY"),token::tokendif),
	make_pair(std::regex(R"QWERTY([0-9]+((((\.[0-9]+)([eE]-?[0-9]+)|(\.[0-9]+)|([eE]-?[0-9]+))[fF]?)|[fF]))QWERTY"),token::double_literal),
	make_pair(std::regex(R"QWERTY((0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+)[uU]?[lL]{0,2})QWERTY"),token::int_literal),
	make_pair(std::regex(R"QWERTY('.')QWERTY"),token::char_literal),
	make_pair(std::regex(R"QWERTY(".*?[^\\]")QWERTY"),token::string_literal),
	make_pair(std::regex(R"QWERTY(<[a-zA-Z_\\/]+(\.[a-zA-Z_\\/]+)?>)QWERTY"),token::include_file),
	make_pair(std::regex(R"QWERTY([a-zA-Z_][0-9a-zA-Z_]*)QWERTY"),token::identifier),
	make_pair(std::regex(R"QWERTY(\+\+)QWERTY"),token::inc),
	make_pair(std::regex(R"QWERTY(--)QWERTY"),token::dec),
	make_pair(std::regex(R"QWERTY(\+=)QWERTY"),token::addass),
	make_pair(std::regex(R"QWERTY(-=)QWERTY"),token::subass),
	make_pair(std::regex(R"QWERTY(\*=)QWERTY"),token::mulass),
	make_pair(std::regex(R"QWERTY(/=)QWERTY"),token::divass),
	make_pair(std::regex(R"QWERTY(%=)QWERTY"),token::modass),
	make_pair(std::regex(R"QWERTY(<<=)QWERTY"),token::shlass),
	make_pair(std::regex(R"QWERTY(>>=)QWERTY"),token::shrass),
	make_pair(std::regex(R"QWERTY(\|=)QWERTY"),token::orass),
	make_pair(std::regex(R"QWERTY(&=)QWERTY"),token::andass),
	make_pair(std::regex(R"QWERTY(\^=)QWERTY"),token::xorass),
	make_pair(std::regex(R"QWERTY(==)QWERTY"),token::equal),
	make_pair(std::regex(R"QWERTY(\|\|)QWERTY"),token::lor),
	make_pair(std::regex(R"QWERTY(&&)QWERTY"),token::land),
	make_pair(std::regex(R"QWERTY(!=)QWERTY"),token::nequal),
	make_pair(std::regex(R"QWERTY(<=)QWERTY"),token::lequal),
	make_pair(std::regex(R"QWERTY(>=)QWERTY"),token::gequal),
	make_pair(std::regex(R"QWERTY(<<)QWERTY"),token::shl),
	make_pair(std::regex(R"QWERTY(>>)QWERTY"),token::shr),
	make_pair(std::regex(R"QWERTY(\.)QWERTY"),token::point),
	make_pair(std::regex(R"QWERTY(->)QWERTY"),token::arrow),
	make_pair(std::regex(R"QWERTY(\.{3})QWERTY"),token::tokellipsis),
	make_pair(std::regex(R"QWERTY(##)QWERTY"),token::hashhash),
	make_pair(std::regex(R"QWERTY(#)QWERTY"),token::hash),
	make_pair(std::regex(R"QWERTY(;)QWERTY"),token::semicolon),
	make_pair(std::regex(R"QWERTY(:)QWERTY"),token::colon),
	make_pair(std::regex(R"QWERTY(\?)QWERTY"),token::question),
	make_pair(std::regex(R"QWERTY(\{)QWERTY"),token::lbrace),
	make_pair(std::regex(R"QWERTY(\})QWERTY"),token::rbrace),
	make_pair(std::regex(R"QWERTY(\[)QWERTY"),token::lbracket),
	make_pair(std::regex(R"QWERTY(\])QWERTY"),token::rbracket),
	make_pair(std::regex(R"QWERTY(\()QWERTY"),token::lparenthesis),
	make_pair(std::regex(R"QWERTY(\))QWERTY"),token::rparenthesis),
	make_pair(std::regex(R"QWERTY(\+)QWERTY"),token::add),
	make_pair(std::regex(R"QWERTY(-)QWERTY"),token::sub),
	make_pair(std::regex(R"QWERTY(\*)QWERTY"),token::mul),
	make_pair(std::regex(R"QWERTY(/)QWERTY"),token::div),
	make_pair(std::regex(R"QWERTY(%)QWERTY"),token::mod),
	make_pair(std::regex(R"QWERTY(!)QWERTY"),token::not),
	make_pair(std::regex(R"QWERTY(~)QWERTY"),token::bnot),
	make_pair(std::regex(R"QWERTY(&)QWERTY"),token::band),
	make_pair(std::regex(R"QWERTY(\|)QWERTY"),token::bor),
	make_pair(std::regex(R"QWERTY(\^)QWERTY"),token::bxor),
	make_pair(std::regex(R"QWERTY(>)QWERTY"),token::greater),
	make_pair(std::regex(R"QWERTY(<)QWERTY"),token::less),
	make_pair(std::regex(R"QWERTY(=)QWERTY"),token::assign),
	make_pair(std::regex(R"QWERTY(,)QWERTY"),token::comma),
	make_pair(std::regex(R"QWERTY([\r\n\t\s]+)QWERTY"),token::whitespace)


} {}
token_name_type::token_name_type() {
	_name.emplace(token::toktypedef, "toktypedef");
	_name.emplace(token::tokvoid, "tokvoid");
	_name.emplace(token::tokconst, "tokconst");
	_name.emplace(token::tokvolatile, "tokvolatile");
	_name.emplace(token::tokregister, "tokregister");
	_name.emplace(token::tokchar, "tokchar");
	_name.emplace(token::tokint, "tokint");
	_name.emplace(token::tokunsigned, "tokunsigned");
	_name.emplace(token::tokshort, "tokshort");
	_name.emplace(token::toklong, "toklong");
	_name.emplace(token::tokfloat, "tokfloat");
	_name.emplace(token::tokdouble, "tokdouble");
	_name.emplace(token::toksizeof, "toksizeof");
	_name.emplace(token::tokstruct, "tokstruct");
	_name.emplace(token::tokenum, "tokenum");
	_name.emplace(token::tokunion, "tokunion");
	_name.emplace(token::tokif, "tokif");
	_name.emplace(token::tokelse, "tokelse");
	_name.emplace(token::tokdo, "tokdo");
	_name.emplace(token::tokfor, "tokfor");
	_name.emplace(token::tokwhile, "tokwhile");
	_name.emplace(token::tokreturn, "tokreturn");
	_name.emplace(token::tokgoto, "tokgoto");
	_name.emplace(token::tokswitch, "tokswitch");
	_name.emplace(token::tokcase, "tokcase");
	_name.emplace(token::tokdefault, "tokdefault");
	_name.emplace(token::tokbreak, "tokbreak");
	_name.emplace(token::tokcontinue, "tokcontinue");
	_name.emplace(token::tokauto, "tokauto");
	_name.emplace(token::tokextern, "tokextern");
	_name.emplace(token::tokstatic, "tokstatic");
	_name.emplace(token::tokpragma, "tokpragma");
	_name.emplace(token::tokinclude, "tokinclude");
	_name.emplace(token::tokdefine, "tokdefine");
	_name.emplace(token::tokundef, "tokundef");
	_name.emplace(token::tokifdef, "tokifdef");
	_name.emplace(token::tokelif, "tokelif");
	_name.emplace(token::tokendif, "tokendif");
	_name.emplace(token::double_literal, "double_literal");
	_name.emplace(token::int_literal, "int_literal");
	_name.emplace(token::char_literal, "char_literal");
	_name.emplace(token::string_literal, "string_literal");
	_name.emplace(token::include_file, "include_file");
	_name.emplace(token::identifier, "identifier");
	_name.emplace(token::inc, "inc");
	_name.emplace(token::dec, "dec");
	_name.emplace(token::addass, "addass");
	_name.emplace(token::subass, "subass");
	_name.emplace(token::mulass, "mulass");
	_name.emplace(token::divass, "divass");
	_name.emplace(token::modass, "modass");
	_name.emplace(token::shlass, "shlass");
	_name.emplace(token::shrass, "shrass");
	_name.emplace(token::orass, "orass");
	_name.emplace(token::andass, "andass");
	_name.emplace(token::xorass, "xorass");
	_name.emplace(token::equal, "equal");
	_name.emplace(token::lor, "lor");
	_name.emplace(token::land, "land");
	_name.emplace(token::nequal, "nequal");
	_name.emplace(token::lequal, "lequal");
	_name.emplace(token::gequal, "gequal");
	_name.emplace(token::shl, "shl");
	_name.emplace(token::shr, "shr");
	_name.emplace(token::point, "point");
	_name.emplace(token::arrow, "arrow");
	_name.emplace(token::tokellipsis, "tokellipsis");
	_name.emplace(token::hashhash, "hashhash");
	_name.emplace(token::hash, "hash");
	_name.emplace(token::semicolon, "semicolon");
	_name.emplace(token::colon, "colon");
	_name.emplace(token::question, "question");
	_name.emplace(token::lbrace, "lbrace");
	_name.emplace(token::rbrace, "rbrace");
	_name.emplace(token::lbracket, "lbracket");
	_name.emplace(token::rbracket, "rbracket");
	_name.emplace(token::lparenthesis, "lparenthesis");
	_name.emplace(token::rparenthesis, "rparenthesis");
	_name.emplace(token::add, "add");
	_name.emplace(token::sub, "sub");
	_name.emplace(token::mul, "mul");
	_name.emplace(token::div, "div");
	_name.emplace(token::mod, "mod");
	_name.emplace(token::not, "not");
	_name.emplace(token::bnot, "bnot");
	_name.emplace(token::band, "band");
	_name.emplace(token::bor, "bor");
	_name.emplace(token::bxor, "bxor");
	_name.emplace(token::greater, "greater");
	_name.emplace(token::less, "less");
	_name.emplace(token::assign, "assign");
	_name.emplace(token::comma, "comma");
	_name.emplace(token::whitespace, "whitespace");
	_name.emplace(token::dummy, "#");
}

token_name_type token_name;
void lex_next_word(std::string const& s, int &position, std::vector<token_pair> &table) {
	static const regex_table reg;
	if (position <= 0)return;
	if (position >= s.size())return;
	auto it = s.begin() + position;
	bool unsucc = true;
	for (auto &e : reg.table) {
		std::smatch m;
		if (std::regex_search(it, s.end(), m, e.first,
			std::regex_constants::match_continuous)) {
			std::string str = m[0].str();
			if (e.second != token::whitespace)
				table.emplace_back(e.second, str);
			//std::cerr << token_name[e.second] << " \"" << str <<"\""<< std::endl;
			position += str.size();
			unsucc = false; break;
		}
	}

}
#define _CASE_X_VEC(_STDF,_VLIT)\
{\
	auto v = _STDF ;\
	auto f = find(_VLIT.begin(), _VLIT.end(), v);\
	if (f == _VLIT.end())_VLIT.push_back(v);\
	now_num = _VLIT.size() - 1;\
}\


std::vector<token_P2>
lex(std::string const& s,
	std::vector<std::string	>& vlit_str,
	std::vector<std::int64_t>& vlit_int,
	std::vector<double		>& vlit_dbl,
	std::vector<char		>& vlit_chr,
	std::vector<std::string	>& vlit_idt,
	std::vector<std::string	>& vlit_file

) {
	static regex_table reg;
	std::vector<token_P2 > res;
	auto it = s.begin();
	while (it != s.end()) {
		bool unsucc = true;
		for (auto& e : reg.table) {
			std::smatch m;
			//std::cerr<<"\tTest " << token_name[e.second]<<std:: endl;
			if (std::regex_search(it, s.end(), m, e.first,
				std::regex_constants::match_continuous)) {
				std::string str = m[0].str();

				if (e.second != token::whitespace) {
					type_token tt = to_type_token(e.second);
					size_t now_num;
					switch (tt) {
					case type_token::keyword:
					case type_token::cpp_keyword:
					case type_token::delimiter:
						now_num = token_to_number(e.second);
						break;
					case type_token::double_literal:
						_CASE_X_VEC(std::stod(str), vlit_dbl);
						break;
					case type_token::int_literal:
						_CASE_X_VEC(std::stoll(str), vlit_int);
						break;
					case type_token::char_literal:
						_CASE_X_VEC(str[1], vlit_chr);
						break;
					case type_token::string_literal:
						_CASE_X_VEC(str.substr(1, str.size() - 2), vlit_str);
						break;
					case type_token::include_file:
						_CASE_X_VEC(str.substr(1, str.size() - 2), vlit_file);
						break;
					case type_token::identifier:
						_CASE_X_VEC(str, vlit_idt);
						break;
					default:
						break;
					}
					res.emplace_back(tt, now_num);
				}//std::cerr << token_name[e.second] << " \"" << str <<"\""<< std::endl;

				it += str.size();
				unsucc = false; break;
			}
		}
		if (unsucc) {
			int cnt = 0;
			std::string report = "Unexpected character :";
			while (cnt < 20 && it != s.end())report.push_back(*it++);
			throw (lex_error(report));
		}
	}
	/*
	for (auto m : res) {
		std::cerr << "{" << token_name[m.first] << " ,\"" << m.second << "\"},";
	}
	*/
	return res;
}
int token_to_number(token t) {
	return (int)t;
}
type_token to_type_token(token t) {
	if (token_to_number(t) >= 200) return type_token::delimiter;
	else if (token_to_number(t) < 100)return type_token::keyword;
	else if (token_to_number(t) < 150)return type_token::cpp_keyword;
	else switch (t) {
	case token::double_literal:
		return type_token::double_literal;
	case token::int_literal:
		return type_token::int_literal;
	case token::char_literal:
		return type_token::char_literal;
	case token::string_literal:
		return type_token::string_literal;
	case token::include_file:
		return type_token::include_file;
	case token::identifier:
		return type_token::identifier;
	default:
		return type_token::identifier;
	}
}

void assign_item(token_item &it, std::string const& s) {
	switch (it.first) {
	case token::char_literal:
		it.second = s[1];
		break;
	case token::string_literal:
		it.second = s.substr(1, s.size() - 2);
		break;
	case token::double_literal:
		it.second = std::stod(s);
		break;
	case token::int_literal:
		it.second = std::stoll(s);
		break;
	case token::identifier:
		it.second = static_cast<std::string>(s);
		break;
	default:
		it.second = nullptr;
		break;
	}
}

std::string nameof(type_token t) {
	switch (t) {
	case type_token::keyword:
		return "keyword";
	case type_token::cpp_keyword:
		return "cpp_keyword";
	case type_token::double_literal:
		return "double_literal";
	case type_token::int_literal:
		return "int_literal";
	case type_token::char_literal:
		return "char_literal";
	case type_token::string_literal:
		return "string_literal";
	case type_token::include_file:
		return "include_file";
	case type_token::identifier:
		return "identifier";
	case type_token::delimiter:
		return "delimiter";
	default:
		return "";
	}
}


std::map<std::string, token> get_token_map() {
	std::map<std::string, token> tok_Mp;
#define ADD_TOKEN(str,tok) tok_Mp.emplace(#str,tok)
	ADD_TOKEN('typedef', token::toktypedef);
	ADD_TOKEN('void', token::tokvoid);
	ADD_TOKEN('const', token::tokconst);
	ADD_TOKEN('volatile', token::tokvolatile);
	ADD_TOKEN('char', token::tokchar);
	ADD_TOKEN('int', token::tokint);
	ADD_TOKEN('unsigned', token::tokunsigned);
	ADD_TOKEN('short', token::tokshort);
	ADD_TOKEN('long', token::toklong);
	ADD_TOKEN('float', token::tokfloat);
	ADD_TOKEN('double', token::tokdouble);
	ADD_TOKEN('sizeof', token::toksizeof);
	ADD_TOKEN('struct', token::tokstruct);
	ADD_TOKEN('enum', token::tokenum);
	ADD_TOKEN('union', token::tokunion);
	ADD_TOKEN('if', token::tokif);
	ADD_TOKEN('else', token::tokelse);
	ADD_TOKEN('do', token::tokdo);
	ADD_TOKEN('for', token::tokfor);
	ADD_TOKEN('while', token::tokwhile);
	ADD_TOKEN('return', token::tokreturn);
	ADD_TOKEN('goto', token::tokgoto);
	ADD_TOKEN('switch', token::tokswitch);
	ADD_TOKEN('case', token::tokcase);
	ADD_TOKEN('default', token::tokdefault);
	ADD_TOKEN('break', token::tokbreak);
	ADD_TOKEN('continue', token::tokcontinue);
	ADD_TOKEN('auto', token::tokauto);
	ADD_TOKEN('register', token::tokregister);
	ADD_TOKEN('extern', token::tokextern);
	ADD_TOKEN('static', token::tokstatic);
	ADD_TOKEN('++', token::inc);
	ADD_TOKEN('--', token::dec);
	ADD_TOKEN('+=', token::addass);
	ADD_TOKEN('-=', token::subass);
	ADD_TOKEN('*=', token::mulass);
	ADD_TOKEN('/=', token::divass);
	ADD_TOKEN('%=', token::modass);
	ADD_TOKEN('<<=', token::shlass);
	ADD_TOKEN('>>=', token::shrass);
	ADD_TOKEN('|=', token::orass);
	ADD_TOKEN('&=', token::andass);
	ADD_TOKEN('^=', token::xorass);
	ADD_TOKEN('==', token::equal);
	ADD_TOKEN('||', token::lor);
	ADD_TOKEN('&&', token::land);
	ADD_TOKEN('!=', token::nequal);
	ADD_TOKEN('<=', token::lequal);
	ADD_TOKEN('>=', token::gequal);
	ADD_TOKEN('<<', token::shl);
	ADD_TOKEN('>>', token::shr);
	ADD_TOKEN('.', token::point);
	ADD_TOKEN('->', token::arrow);
	//ADD_TOKEN('', token::tokellipsis);
	//ADD_TOKEN('', token::hash);
	//ADD_TOKEN('', token::hashhash);
	ADD_TOKEN(';', token::semicolon);
	ADD_TOKEN('?', token::question);
	ADD_TOKEN('{', token::lbrace);
	ADD_TOKEN('}', token::rbrace);
	ADD_TOKEN('[', token::lbracket);
	ADD_TOKEN(']', token::rbracket);
	ADD_TOKEN('(', token::lparenthesis);
	ADD_TOKEN(')', token::rparenthesis);
	ADD_TOKEN('+', token::add);
	ADD_TOKEN('-', token::sub);
	ADD_TOKEN('*', token::mul);
	ADD_TOKEN('/', token::div);
	ADD_TOKEN('%', token::mod);
	ADD_TOKEN('!', token::not);
	ADD_TOKEN('~', token::bnot);
	ADD_TOKEN('&', token::band);
	ADD_TOKEN('|', token::bor);
	ADD_TOKEN('^', token::bxor);
	ADD_TOKEN('>', token::greater);
	ADD_TOKEN('<', token::less);
	ADD_TOKEN('=', token::assign);
	ADD_TOKEN(',', token::comma);
	ADD_TOKEN('dummy', token::dummy);
	//	std::string grammar::literals[] = { "int_const", "char_const","float_const","id", "string","enumeration_const" };
	ADD_TOKEN(int_const, token::int_literal);
	ADD_TOKEN(char_const, token::char_literal);
	ADD_TOKEN(float_const, token::double_literal);
	ADD_TOKEN(id, token::identifier);
	ADD_TOKEN(string, token::string_literal);
	ADD_TOKEN(enumeration_const, token::identifier);
	return tok_Mp;
}