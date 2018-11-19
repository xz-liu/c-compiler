#include "graph.h"

std::string bnf_c =
R"(translation_unit    : external_decl
            | translation_unit external_decl
            ;
external_decl       : function_definition
            | decl
            ;
function_definition : decl_specs declarator decl_list compound_stat
            |       declarator decl_list compound_stat
            | decl_specs declarator     compound_stat
            |       declarator  compound_stat
            ;
decl            : decl_specs init_declarator_list ';'
            | decl_specs            ';'
            ;
decl_list       : decl
            | decl_list decl
            ;
decl_specs      : storage_class_spec decl_specs
            | storage_class_spec
            | type_spec decl_specs
            | type_spec
            | type_qualifier decl_specs
            | type_qualifier
            ;
storage_class_spec  : '' | 'register' | 'static' | 'extern' | 'typedef'
            ;
type_spec       : 'void' | 'char' | 'short' | 'int' | 'long' | 'float'
            | 'double' | 'signed' | 'unsigned'
            | struct_or_union_spec
            | enum_spec
            | typedef_name
            ;
type_qualifier      : 'const' | 'volatile'
            ;
struct_or_union_spec    : struct_or_union id '{' struct_decl_list '}'
            | struct_or_union   '{' struct_decl_list '}'
            | struct_or_union id
            ;
struct_or_union     : 'struct' | 'union'
            ;
struct_decl_list    : struct_decl
            | struct_decl_list struct_decl
            ;
init_declarator_list    : init_declarator
            | init_declarator_list ',' init_declarator
            ;
init_declarator     : declarator
            | declarator '=' initializer
            ;
struct_decl     : spec_qualifier_list struct_declarator_list ';'
            ;
spec_qualifier_list : type_spec spec_qualifier_list
            | type_spec
            | type_qualifier spec_qualifier_list
            | type_qualifier
            ;
struct_declarator_list  : struct_declarator
            | struct_declarator_list ',' struct_declarator
            ;
struct_declarator   : declarator
            | declarator ':' const_exp
            |       ':' const_exp
            ;
enum_spec       : 'enum' id '{' enumerator_list '}'
            | 'enum'    '{' enumerator_list '}'
            | 'enum' id
            ;
enumerator_list     : enumerator
            | enumerator_list ',' enumerator
            ;
enumerator      : id
            | id '=' const_exp
            ;
declarator      : pointer direct_declarator
            |   direct_declarator
            ;
direct_declarator   : id
            | '(' declarator ')'
            | direct_declarator '[' const_exp ']'
            | direct_declarator '['     ']'
            | direct_declarator '(' param_type_list ')'
            | direct_declarator '(' id_list ')'
            | direct_declarator '('     ')'
            ;
pointer         : '*' type_qualifier_list
            | '*'
            | '*' type_qualifier_list pointer
            | '*'           pointer
            ;
type_qualifier_list : type_qualifier
            | type_qualifier_list type_qualifier
            ;
param_type_list     : param_list
            | param_list ',' '...'
            ;
param_list      : param_decl
            | param_list ',' param_decl
            ;
param_decl      : decl_specs declarator
            | decl_specs abstract_declarator
            | decl_specs
            ;
id_list         : id
            | id_list ',' id
            ;
initializer     : assignment_exp
            | '{' initializer_list '}'
            | '{' initializer_list ',' '}'
            ;
initializer_list    : initializer
            | initializer_list ',' initializer
            ;
type_name       : spec_qualifier_list abstract_declarator
            | spec_qualifier_list
            ;
abstract_declarator : pointer
            | pointer direct_abstract_declarator
            |   direct_abstract_declarator
            ;
direct_abstract_declarator: '(' abstract_declarator ')'
            | direct_abstract_declarator '[' const_exp ']'
            |               '[' const_exp ']'
            | direct_abstract_declarator '['    ']'
            |               '[' ']'
            | direct_abstract_declarator '(' param_type_list ')'
            |               '(' param_type_list ')'
            | direct_abstract_declarator '('        ')'
            |               '('     ')'
            ;
typedef_name        : id
            ;
stat            : labeled_stat
            | exp_stat
            | compound_stat
            | selection_stat
            | iteration_stat
            | jump_stat
            ;
labeled_stat        : id ':' stat
            | 'case' const_exp ':' stat
            | 'default' ':' stat
            ;
exp_stat        : exp ';'
            |   ';'
            ;
compound_stat       : '{' decl_list stat_list '}'
            | '{'       stat_list '}'
            | '{' decl_list     '}'
            | '{'           '}'
            ;
stat_list       : stat
            | stat_list stat
            ;
selection_stat      : 'if' '(' exp ')' stat
            | 'if' '(' exp ')' stat 'else' stat
            | 'switch' '(' exp ')' stat
            ;
iteration_stat      : 'while' '(' exp ')' stat
            | 'do' stat 'while' '(' exp ')' ';'
            | 'for' '(' exp ';' exp ';' exp ')' stat
            | 'for' '(' exp ';' exp ';' ')' stat
            | 'for' '(' exp ';' ';' exp ')' stat
            | 'for' '(' exp ';' ';' ')' stat
            | 'for' '(' ';' exp ';' exp ')' stat
            | 'for' '(' ';' exp ';' ')' stat
            | 'for' '(' ';' ';' exp ')' stat
            | 'for' '(' ';' ';' ')' stat
            ;
jump_stat       : 'goto' id ';'
            | 'continue' ';'
            | 'break' ';'
            | 'return' exp ';'
            | 'return'  ';'
            ;
exp         : assignment_exp
            | exp ',' assignment_exp
            ;
assignment_exp      : conditional_exp
            | unary_exp assignment_operator assignment_exp
            ;
assignment_operator : '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<='
            | '>>=' | '&=' | '^=' | '|='
            ;
conditional_exp     : logical_or_exp
            | logical_or_exp '?' exp ':' conditional_exp
            ;
const_exp       : conditional_exp
            ;
logical_or_exp      : logical_and_exp
            | logical_or_exp '||' logical_and_exp
            ;
logical_and_exp     : inclusive_or_exp
            | logical_and_exp '&&' inclusive_or_exp
            ;
inclusive_or_exp    : exclusive_or_exp
            | inclusive_or_exp '|' exclusive_or_exp
            ;
exclusive_or_exp    : and_exp
            | exclusive_or_exp '^' and_exp
            ;
and_exp         : equality_exp
            | and_exp '&' equality_exp
            ;
equality_exp        : relational_exp
            | equality_exp '==' relational_exp
            | equality_exp '!=' relational_exp
            ;
relational_exp      : shift_expression
            | relational_exp '<' shift_expression
            | relational_exp '>' shift_expression
            | relational_exp '<=' shift_expression
            | relational_exp '>=' shift_expression
            ;
shift_expression    : additive_exp
            | shift_expression '<<' additive_exp
            | shift_expression '>>' additive_exp
            ;
additive_exp        : mult_exp
            | additive_exp '+' mult_exp
            | additive_exp '-' mult_exp
            ;
mult_exp        : cast_exp
            | mult_exp '*' cast_exp
            | mult_exp '/' cast_exp
            | mult_exp '%' cast_exp
            ;
cast_exp        : unary_exp
            | '(' type_name ')' cast_exp
            ;
unary_exp       : postfix_exp
            | '++' unary_exp
            | '--' unary_exp
            | unary_operator cast_exp
            | 'sizeof' unary_exp
            | 'sizeof' '(' type_name ')'
            ;
unary_operator      : '&' | '*' | '+' | '-' | '~' | '!'
            ;
postfix_exp     : primary_exp
            | postfix_exp '[' exp ']'
            | postfix_exp '(' argument_exp_list ')'
            | postfix_exp '('           ')'
            | postfix_exp '.' id
            | postfix_exp '->' id
            | postfix_exp '++'
            | postfix_exp '--'
            ;
primary_exp     : id
            | const
            | string
            | '(' exp ')'
            ;
argument_exp_list   : assignment_exp
            | argument_exp_list ',' assignment_exp
            ;
const           : int_const
            | char_const
            | float_const
            | enumeration_const
            ;)";

std::string grammar::literals[] = { "int_const", "char_const","float_const","id", "string","enumeration_const" };

void grammar::cal_first(int S) {
	if (is_terminator(S)) {
		first[S] = { S };// First(A) = A when A is a terminator
	} else {
		for (auto &&exp : this->operator[](S)) {
			if (exp.size()) {//when A ->Y1,Y2,...,Yk
				int k = 0;
				while (k < exp.size()) {
					cal_first(exp[k]);
					if (first[exp[k]].find(id_eps) == first[exp[k]].end()) {
						break;
					}
				};
				if (k == exp.size())first[S].insert(id_eps);// Y1...Yk has eps
				else first[S].insert(first[exp[k]].begin(), first[exp[k]].end());// Yk hasn't eps
			} else first[S].insert(id_eps);//A -> eps
		}
	}
}
void grammar::cal_first() {
	for (auto&& x : mp) {
		if (is_terminator(x.second)) first[x.second] = { x.second };
	}		
	first[id_eps] = {};
	bool complete = false;
	while(!complete) {
		for(auto &&S:productions) {
			std::set<int>   next = first[S.first];
			for(auto &&exp:S.second) {
				if (exp.size()) {
					for (auto &&Yi : exp) {
						if (is_terminator(Yi)) {
							next.insert(Yi);
							break;
						}
						if (!set_contains(first[Yi], id_eps)) {
							next.insert(Yi); break;
						}
					}
				}
				else { next.insert(id_eps); }
			}
			if(next.size()>first[S.first].size()) {
				first[S.first] = next;
			}
			else { complete = true; }
		}
	}


}
void grammar::cal_follow() {
	follow[id_s].insert(id_dummy);
	while (true) {
		bool new_follow = false;
		for (auto && Sp : mp) {
			int S = Sp.second;
			if (is_terminator(S))continue;
			for (auto &&exp : this->operator[](S)) {
				for (int i = 0; i < exp.size(); i++) {
					int now = follow[exp[i]].size();
					if ((i == exp.size() - 1) ||
						first[exp[i + 1]].find(id_eps) != first[exp[i + 1]].end()) {
						follow[exp[i]].insert(follow[S].begin(), follow[S].end());
					} else {
						follow[exp[i]].insert(first[exp[i + 1]].begin(), first[exp[i + 1]].end());
					}
					new_follow |= follow[exp[i]].size() != now;
				}
			}
		}
		if (!new_follow)break;
	}
	for (auto&& i : follow)i.second.erase(id_eps);
}

void grammar::init(std::string const & bnf) {
	cnt = 0;
	std::string s, S;
	std::stringstream cin(bnf);
	bool _1st = true;
	while (cin >> s) {
		std::string t; cin >> t; // :
								 /*std::cout << "\tNEW S" << s << " " << t << std::endl;*/
		if (_1st) {
			_1st = false;
			S = s;
		}
		while (t != ";") {
			std::vector<std::string> vec;
			while (1) {
				cin >> t;
				/*std::cout << t << std::endl;*/
				if (t == "|" || t == ";")break;
				vec.push_back(t);
			};
			/*std::cout << "addPROD " << s<<" ->";
			for (auto x : vec)std::cout << " " << x;
			std::cout<< std::endl;*/
			add_production(s, vec);
		}
	}
	add_symbol("'dummy'");
	add_symbol("_Eps");
	id_eps = get_tok("_Eps");
	id_dummy = get_tok("'dummy'");
	id_s = get_tok(S);
#define ADD_TOKEN(str,tok) token_map.emplace(#str,tok)
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
	//for (auto&& x : mp)if ((x.second != id_dummy) && (x.second != id_eps))cal_first(x.second);
	//cal_first(id_s);
	;
	cal_first();
	cal_follow();
}

grammar::grammar() {
	init(bnf_c);
}
grammar::grammar(std::string const& bnf) {
	init(bnf);
}