
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include "lex\lex.h"
#include "error\error.h"
#include "parse\parse.h"
#include "parse/exp.h"

void debug_exp() {
	freopen("debug.c", "r", stdin);
	using std::cout;
	using std::endl;
	try {
		char c; std::string s;
		while ((c = getchar()) != EOF) {
			s.push_back(c);
		}
		lex_data data(s);

		//data.debug();

		/*rec r(data);
		r.parse_E();
		std::cout << "�ݹ鷨" << std::endl;
		std::cout << "PARSER RESULT " << std::boolalpha << (r.good()) << std::endl;
		std::cout << "LL(1)" << std::endl;
		LL1 l(data);
		l.parse();
		std::cout << "PARSER RESULT " << std::boolalpha << (l.good()) << std::endl;

		*/
		//grammar p2;
		//p2.debug();//	cout<<p2.parse_ll1(data);
		sem_stack numbers;
		int tmp_cnt = 0;
		auto gen_q = [&](char c) {
			cout << "{" << c << " , ";
			for (int i = 0; i < 2; i++) {
				switch (numbers.now()) {
				case type_token::identifier:
					cout << numbers.id_stack.top();
					numbers.id_stack.pop();
					break;
				case type_token::int_literal:
					cout << numbers.const_int.top();
					numbers.const_int.pop();
					break;
				case type_token::double_literal:
					cout << numbers.const_float.top();
					numbers.const_float.pop();
					break;
				}
				numbers.now_type.pop();
				cout << " , ";
			}
			std::string now_id = std::string("_TMP_NO_") + std::to_string(tmp_cnt++);
			cout << now_id << " }" << endl;
			numbers.push_id(now_id);

		};
		grammar grm(R"(
			E	: T E1 ;
			E1	: '+' T {GEQ_ADD} E1 
				| '-' T {GEQ_SUB} E1
				|
				;
			T	: F T1 ;
			T1	: '*' F {GEQ_MUL} T1 
				| '/' F {GEQ_DIV} T1
				|
				;
			F	: I | '(' E ')' ;
			I	: int_const {PUSH_INT_CONST} |
				 float_const {PUSH_FLOAT_CONST} |
				 id  {PUSH_ID} ;
		)");
		//grm.debug();
		grm.assign_action("{PUSH_ID}", [&](lex_data const& data, int now) {
			numbers.push_id(data.get_id(now));
		});
		grm.assign_action("{PUSH_INT_CONST}", [&](lex_data const& data, int now) {
			numbers.push_int(data.get_int(now));
		});
		grm.assign_action("{PUSH_FLOAT_CONST}", [&](lex_data const& data, int now) {
			numbers.push_float(data.get_double(now));
		});
		grm.assign_action("{GEQ_MUL}", [&](lex_data const& data, int now) {
			gen_q('*');
		});
		grm.assign_action("{GEQ_DIV}", [&](lex_data const& data, int now) {
			gen_q('/');
		});
		grm.assign_action("{GEQ_ADD}", [&](lex_data const& data, int now) {
			gen_q('+');
		});
		grm.assign_action("{GEQ_SUB}", [&](lex_data const& data, int now) {
			gen_q('-');
		});

		parser parse(data);
		//p.debug();
		std::cout << parse(grm) << grm.parse_ll1(data) << std::endl;
	} catch (std::regex_error e) {
		std::cout << e.what() << "\n"
			<< e.code() << std::endl;
	} catch (lex_error e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "UNKNOWN ERROR!" << std::endl;
	}

}
void debug_2() {
	using std::cout;
	using std::endl;
	grammar grm2;
	lex_data data_c(R"(
int main(){
	int a;
	int b,c,d;
	return 0;			
}
		)");
	grm2.debug();
	grm2.parse_ll1(data_c);
	
}

int main() {
	debug_exp();
	while (1);
	return 0;
}