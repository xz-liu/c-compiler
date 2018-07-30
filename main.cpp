
#pragma warning(disable:4996)
	
#include "lex\lex.h"

int main() {
	freopen("D:\\lextest.txt", "r", stdin);
	try {
		char c; std::string s;
		while ((c = getchar()) != EOF) {
			s.push_back(c);
		}
		lex(s);
	} catch (std::regex_error e) {
		std::cout << e.what() << "\n"
			<< e.code() << std::endl;
	}
	catch (...) {

	}
	return 0;
}