
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include "lex\lex.h"
#include "error\error.h"
#include "parse\parse.h"
#include "parse/exp.h"

//

void debug_string(std::string const& s) {
	static grammar grm;
	using std::cout;
	using std::endl;
	cout << s << " ";
	lex_data data_c(s);
	grm.parse_ll1(s);
}
void fuck() {
	debug_string(R"(int main() {} )");
	debug_string(R"(struct A{} ;)");
	debug_string(R"(int main() {while(a-=b<4%7+3*func(a,b,c,d,e,f)*a[6]) a++;} )");
	debug_string(R"(int main() {for( a-=b<4%7+3*func(a,b,c,d,e,f)*a[6]; a; a) { a+=2;} })");
	debug_string(R"(int main() {if(a-=b<4%7+3*func(a,b,c,d,e,f)*a[6]) a; else if(a-=b<4%7+3*func(a,b,c,d,e,f)*a[6]) a; else {a-=b<4%7+3*func(a,b,c,d,e,f)*a[6] ;} })");
	debug_string(R"(int a;double b,d;)");
	debug_string(R"(int main() {if (a >= didi.xa)a = '0';
	else if (fewfe == (didi.xa + 1)) {
		while (a == b)a++;
		for (a = 4; a>8; --a) {
			didi.fuck += a;
		}
	} else {
		b = didi.fuck;
	}} )");
	debug_string(R"(struct A {
	int a, b, c;
	char f, g, h;
	long long fuck;
	char xa[10];
};
int ret(int a, char b[]) {
	return b[a];
}

int b;
int main() {
	int a;
	int b = 5, c, D = 10;
	struct A didi;
	didi.fuck = 5;
	didi.f = ret(didi.c, didi.b) + 5;
	if (a >=( didi.xa)[0])a = '0';
	else if (fewfe == ((didi.xa)[1] + 1)) {
		while (a == b)a++;
		for (a = 4; a>8; --a) {
			didi.fuck += a;
		}
	} else {
		b = didi.fuck;
	}
	return 0;
})");
}

int main() {
	grammar grm;
	grm.debug();

	std::cout << "DONE" << std::endl;
	while (1);
	return 0;
}