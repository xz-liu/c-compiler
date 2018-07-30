#include "token.h"
#include "lex.h"

regex_table::regex_table() :table{
	make_pair(std::regex(R"fuck(typedef)fuck"),token::toktypedef),
	make_pair(std::regex(R"fuck(void)fuck"),token::tokvoid),
	make_pair(std::regex(R"fuck(const)fuck"),token::tokconst),
	make_pair(std::regex(R"fuck(char)fuck"),token::tokchar),
	make_pair(std::regex(R"fuck(int)fuck"),token::tokint),
	make_pair(std::regex(R"fuck(unsigned)fuck"),token::tokunsigned),
	make_pair(std::regex(R"fuck(short)fuck"),token::tokshort),
	make_pair(std::regex(R"fuck(long)fuck"),token::toklong),
	make_pair(std::regex(R"fuck(float)fuck"),token::tokfloat),
	make_pair(std::regex(R"fuck(double)fuck"),token::tokdouble),
	make_pair(std::regex(R"fuck(sizeof)fuck"),token::toksizeof),
	make_pair(std::regex(R"fuck(struct)fuck"),token::tokstruct),
	make_pair(std::regex(R"fuck(enum)fuck"),token::tokenum),
	make_pair(std::regex(R"fuck(union)fuck"),token::tokunion),
	make_pair(std::regex(R"fuck(if)fuck"),token::tokif),
	make_pair(std::regex(R"fuck(else)fuck"),token::tokelse),
	make_pair(std::regex(R"fuck(do)fuck"),token::tokdo),
	make_pair(std::regex(R"fuck(for)fuck"),token::tokfor),
	make_pair(std::regex(R"fuck(while)fuck"),token::tokwhile),
	make_pair(std::regex(R"fuck(return)fuck"),token::tokreturn),
	make_pair(std::regex(R"fuck(goto)fuck"),token::tokgoto),
	make_pair(std::regex(R"fuck(switch)fuck"),token::tokswitch),
	make_pair(std::regex(R"fuck(case)fuck"),token::tokcase),
	make_pair(std::regex(R"fuck(default)fuck"),token::tokdefault),
	make_pair(std::regex(R"fuck(break)fuck"),token::tokbreak),
	make_pair(std::regex(R"fuck(continue)fuck"),token::tokcontinue),
	make_pair(std::regex(R"fuck(auto)fuck"),token::tokauto),
	make_pair(std::regex(R"fuck(extern)fuck"),token::tokextern),
	make_pair(std::regex(R"fuck(static)fuck"),token::tokstatic),	
	make_pair(std::regex(R"fuck(-?[0-9]+((\.[0-9]+)([eE]-?[0-9]+)|(\.[0-9]+)|([eE]-?[0-9]+))[fF]?)fuck"),token::double_literal),
	make_pair(std::regex(R"fuck(-?(0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+)[uU]?[lL]{0,2})fuck"),token::int_literal),
	make_pair(std::regex(R"fuck('.')fuck"),token::char_literal),
	make_pair(std::regex(R"fuck(".*")fuck"),token::string_literal),
	make_pair(std::regex(R"fuck([a-zA-Z_][0-9a-zA-Z_]*)fuck"),token::identifier),
	make_pair(std::regex(R"fuck(\+\+)fuck"),token::inc),
	make_pair(std::regex(R"fuck(--)fuck"),token::dec),
	make_pair(std::regex(R"fuck(\+=)fuck"),token::addass),
	make_pair(std::regex(R"fuck(-=)fuck"),token::subass),
	make_pair(std::regex(R"fuck(\*=)fuck"),token::mulass),
	make_pair(std::regex(R"fuck(/=)fuck"),token::divass),
	make_pair(std::regex(R"fuck(%=)fuck"),token::modass),
	make_pair(std::regex(R"fuck(<<=)fuck"),token::shlass),
	make_pair(std::regex(R"fuck(>>=)fuck"),token::shrass),
	make_pair(std::regex(R"fuck(\|=)fuck"),token::orass),
	make_pair(std::regex(R"fuck(&=)fuck"),token::andass),
	make_pair(std::regex(R"fuck(\^=)fuck"),token::xorass),
	make_pair(std::regex(R"fuck(==)fuck"),token::equal),
	make_pair(std::regex(R"fuck(\|\|)fuck"),token::lor),
	make_pair(std::regex(R"fuck(&&)fuck"),token::land),
	make_pair(std::regex(R"fuck(!=)fuck"),token::nequal),
	make_pair(std::regex(R"fuck(<=)fuck"),token::lequal),
	make_pair(std::regex(R"fuck(>=)fuck"),token::gequal),
	make_pair(std::regex(R"fuck(<<)fuck"),token::shl),
	make_pair(std::regex(R"fuck(>>)fuck"),token::shr),
	make_pair(std::regex(R"fuck(\.)fuck"),token::point),
	make_pair(std::regex(R"fuck(->)fuck"),token::arrow),
	make_pair(std::regex(R"fuck(\.{3})fuck"),token::tokellipsis),
	make_pair(std::regex(R"fuck(;)fuck"),token::semicolon),
	make_pair(std::regex(R"fuck(:)fuck"),token::colon),
	make_pair(std::regex(R"fuck(\?)fuck"),token::question),
	make_pair(std::regex(R"fuck(\{)fuck"),token::lbrace),
	make_pair(std::regex(R"fuck(\})fuck"),token::rbrace),
	make_pair(std::regex(R"fuck(\[)fuck"),token::lbracket),
	make_pair(std::regex(R"fuck(\])fuck"),token::rbracket),
	make_pair(std::regex(R"fuck(\()fuck"),token::lparenthesis),
	make_pair(std::regex(R"fuck(\))fuck"),token::rparenthesis),
	make_pair(std::regex(R"fuck(\+)fuck"),token::add),
	make_pair(std::regex(R"fuck(-)fuck"),token::sub),
	make_pair(std::regex(R"fuck(\*)fuck"),token::mul),
	make_pair(std::regex(R"fuck(/)fuck"),token::div),
	make_pair(std::regex(R"fuck(%)fuck"),token::mod),
	make_pair(std::regex(R"fuck(!)fuck"),token::not),
	make_pair(std::regex(R"fuck(~)fuck"),token::bnot),
	make_pair(std::regex(R"fuck(&)fuck"),token::band),
	make_pair(std::regex(R"fuck(\|)fuck"),token::bor),
	make_pair(std::regex(R"fuck(>)fuck"),token::greater),
	make_pair(std::regex(R"fuck(<)fuck"),token::less),
	make_pair(std::regex(R"fuck(=)fuck"),token::assign),
	make_pair(std::regex(R"fuck([\r\n\t\s]+)fuck"),token::whitespace),
	make_pair(std::regex(R"fuck(,)fuck"),token::comma)
} {
	name.emplace(token::toktypedef, "toktypedef");
	name.emplace(token::tokvoid, "tokvoid");
	name.emplace(token::tokconst, "tokconst");
	name.emplace(token::tokchar, "tokchar");
	name.emplace(token::tokint, "tokint");
	name.emplace(token::tokunsigned, "tokunsigned");
	name.emplace(token::tokshort, "tokshort");
	name.emplace(token::toklong, "toklong");
	name.emplace(token::tokfloat, "tokfloat");
	name.emplace(token::tokdouble, "tokdouble");
	name.emplace(token::toksizeof, "toksizeof");
	name.emplace(token::tokstruct, "tokstruct");
	name.emplace(token::tokenum, "tokenum");
	name.emplace(token::tokunion, "tokunion");
	name.emplace(token::tokif, "tokif");
	name.emplace(token::tokelse, "tokelse");
	name.emplace(token::tokdo, "tokdo");
	name.emplace(token::tokfor, "tokfor");
	name.emplace(token::tokwhile, "tokwhile");
	name.emplace(token::tokreturn, "tokreturn");
	name.emplace(token::tokgoto, "tokgoto");
	name.emplace(token::tokswitch, "tokswitch");
	name.emplace(token::tokcase, "tokcase");
	name.emplace(token::tokdefault, "tokdefault");
	name.emplace(token::tokbreak, "tokbreak");
	name.emplace(token::tokcontinue, "tokcontinue");
	name.emplace(token::tokauto, "tokauto");
	name.emplace(token::tokextern, "tokextern");
	name.emplace(token::tokstatic, "tokstatic");
	name.emplace(token::int_literal, "int_literal");
	name.emplace(token::double_literal, "double_literal");
	name.emplace(token::char_literal, "char_literal");
	name.emplace(token::string_literal, "string_literal");
	name.emplace(token::identifier, "identifier");
	name.emplace(token::inc, "inc");
	name.emplace(token::dec, "dec");
	name.emplace(token::addass, "addass");
	name.emplace(token::subass, "subass");
	name.emplace(token::mulass, "mulass");
	name.emplace(token::divass, "divass");
	name.emplace(token::modass, "modass");
	name.emplace(token::shlass, "shlass");
	name.emplace(token::shrass, "shrass");
	name.emplace(token::orass, "orass");
	name.emplace(token::andass, "andass");
	name.emplace(token::xorass, "xorass");
	name.emplace(token::equal, "equal");
	name.emplace(token::lor, "lor");
	name.emplace(token::land, "land");
	name.emplace(token::nequal, "nequal");
	name.emplace(token::lequal, "lequal");
	name.emplace(token::gequal, "gequal");
	name.emplace(token::shl, "shl");
	name.emplace(token::shr, "shr");
	name.emplace(token::point, "point");
	name.emplace(token::arrow, "arrow");
	name.emplace(token::tokellipsis, "tokellipsis");
	name.emplace(token::semicolon, "semicolon");
	name.emplace(token::colon, "colon");
	name.emplace(token::question, "question");
	name.emplace(token::lbrace, "lbrace");
	name.emplace(token::rbrace, "rbrace");
	name.emplace(token::lbracket, "lbracket");
	name.emplace(token::rbracket, "rbracket");
	name.emplace(token::lparenthesis, "lparenthesis");
	name.emplace(token::rparenthesis, "rparenthesis");
	name.emplace(token::add, "add");
	name.emplace(token::sub, "sub");
	name.emplace(token::mul, "mul");
	name.emplace(token::div, "div");
	name.emplace(token::mod, "mod");
	name.emplace(token::not, "not");
	name.emplace(token::bnot, "bnot");
	name.emplace(token::band, "band");
	name.emplace(token::bor, "bor");
	name.emplace(token::greater, "greater");
	name.emplace(token::less, "less");
	name.emplace(token::assign, "assign");
	name.emplace(token::whitespace, "whitespace");
	name.emplace(token::comma, "comma");
}

std::vector<std::pair<token, std::string>>
lex(std::string const& s) {
	static regex_table reg;
	std::vector<std::pair<token, std::string>> res;
	auto it = s.begin();
	while (it != s.end()) {
		bool unsucc = true;
		for (auto& e : reg.table) {
			std::smatch m;
			if (std::regex_search(it, s.end(), m, e.first, std::regex_constants::match_continuous)) {
				std::string str = m[0].str();
				res.emplace_back(e.second, str);
				//std::cerr << reg.name[e.second] << " \"" << str <<"\""<< std::endl;
				it += str.size();
				unsucc = false; break;
			}
		}
		if (unsucc) {
			while (it != s.end())std:: cout << *it++;
			throw("REJECTED!");
		}
	}
	for (auto m : res) {
		std::cerr <<"{"<< reg.name[m.first] << " ,\"" << m.second << "\"}," ;
	}
	return res;
}
