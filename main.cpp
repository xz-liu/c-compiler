
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include "lex\lex.h"
#include "error\error.h"
#include "parse\parse.h"
int main() {
	/*freopen("D:\\lextest.c", "r", stdin);
	try {
		char c; std::string s;
		while ((c = getchar()) != EOF) {
			s.push_back(c);
		}
		lex_data data(s);
		data.debug();
		rec r(data);
		r.parse_E();
		std::cout << "�ݹ鷨" << std::endl;
		std::cout << "PARSER RESULT " << std::boolalpha << (r.good()) << std::endl;
		std::cout << "LL(1)" << std::endl;
		LL1 l(data);
		l.parse();
		std::cout << "PARSER RESULT " << std::boolalpha << (l.good()) << std::endl;

	} catch (std::regex_error e) {
		std::cout << e.what() << "\n"
			<< e.code() << std::endl;
	} catch (lex_error e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "UNKNOWN ERROR!" << std::endl;
	}*/
	grammar p(R"(
		S	: E ;
		E	: T E1 ;
		E1	: | w0 T E1  ;
		w0	: '+' | '-' ;
		T	: F T1 ;
		T1	: w1 F T1 | ;
		w1	: '*' | '/' ;
		F	: I | '(' E ')' ;
		I	: int_const | float_const | id ;
		)");
	//grammar p;
	p.debug();
	while (1);
	return 0;
}