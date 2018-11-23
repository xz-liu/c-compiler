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
/*
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
*/
void grammar::cal_first() {
	for (auto&& x : mp) {
		// First(A) = A when A is a terminator
		if (is_terminator(x.second)) first_set[x.second] = { x.second };
	}
	first_set[id_eps] = {};
	bool complete = true;
	do {
		complete = true;
		for (auto &&S : productions) {
			std::set<int>   next = first_set[S.first];
			for (auto &&exp : S.second) {
				if (exp.size()) {//when A ->Y1,Y2,...,Yk
					bool prod_all_eps = true;
					for (auto &&Yi : exp) {
						if (is_terminator(Yi)) {
							prod_all_eps = false;
							next.insert(Yi);
							break;
						}
						if (!set_contains(first_set[Yi], id_eps)) {
							prod_all_eps = false;
							next.insert(first_set[Yi].begin(), first_set[Yi].end()); break;
						}
					}
					if (prod_all_eps)next.insert(id_eps);
				} else { next.insert(id_eps); }
			}
			if (next.size() > first_set[S.first].size()) {
				first_set[S.first] = next;
				complete = false;
			} 
		}
	} while (!complete);

}
void grammar::cal_follow() {
	follow_set[id_s].insert(id_dummy);
	while (true) {
		bool new_follow = false;
		for (auto && Sp : productions) {
			int S = Sp.first;
			if (is_terminator(S))continue;
			for (auto &&exp : Sp.second) {
				if (exp.empty())continue;
				/*std::vector<int> first_pos(exp.size());
				auto with_eps=[&](int i)->bool{
					if (first_pos[i] != i)return true;
					return set_contains(first_set[exp[i]], id_eps);
				};
				int last = -1;
				for (int i = exp.size()-1; i >= 0;i--) {
					first_pos[i] = last;
					if (is_terminator(exp[i])) {
						 last = i;
					} else for(auto&& x:first_set[exp[i]])if(x!=id_eps) {
						last = i;break;
					}
					
				}*/
				//output_list(exp, [&](int i) {return get_name(i); });
				for (int i = 0; i < exp.size(); i++) {
					if (is_terminator(exp[i]))continue;
					int now = follow_set[exp[i]].size();
/*
					if (first_id==-1||with_eps(i)) {
						follow_set[exp[i]].insert(follow_set[S].begin(), follow_set[S].end());
					}
					if (first_id!=-1) {
						follow_set[exp[i]].insert(
							first_set[exp[first_id]].begin(), first_set[exp[first_id]].end()
						);
					}*/
					auto beta_1st = first_set_of_prod(exp.begin() + i + 1, exp.end());
					if(set_contains(beta_1st,id_eps)) {
						follow_set[exp[i]].insert(follow_set[S].begin(), follow_set[S].end());
					}
					follow_set[exp[i]].insert(beta_1st.begin(), beta_1st.end());
					new_follow |= follow_set[exp[i]].size() != now;
				}
			}
		}
		if (!new_follow)break;
	}
	for (auto&& i : follow_set)i.second.erase(id_eps);
}

void grammar::fill_ll1_table() {
	cal_first();
	cal_follow();
	for (auto &&all_prods : productions) {
		auto &&S = all_prods.first;
		int prod_rk = 0;
		for (auto && prods : all_prods.second) {
			bool good = false;
			auto this_first = first_set_of_prod(prods.begin(), prods.end());
			for(auto &&t:this_first) {
				if(t==id_eps) {
					for(auto&& ft: follow_set[S])
						ll1_table[
							std::make_pair(S, token_map.find(get_name(ft))->second)
						].insert(std::make_pair(S, prod_rk));
				}
				else {
					ll1_table[
						std::make_pair(S, token_map.find(get_name(t))->second)
					].insert(std::make_pair(S, prod_rk));
				}
			}
			/*for (auto && Xi : prods) {
				if (first_set[Xi].size() >= 2) {
					continue;
				} else if (first_set[Xi].size() && *first_set[Xi].begin() == id_eps) {
					continue;
				}
				for (auto &&chr : first_set[Xi])
					ll1_table[
						std::make_pair(S, token_map.find(get_name(chr))->second)
					].insert(std::make_pair(S, prod_rk));
						good = true; break;
			}
			if (!good) {
				for (auto &&chr : follow_set[S])
					ll1_table[
						std::make_pair(S, token_map.find(get_name(chr))->second)
					].insert(std::make_pair(S, prod_rk));

			}*/
			prod_rk++;
		}

	}
}

bool grammar::parse_ll1(lex_data const & data, std::stack<int>& sta, int & now) {
	int id_top = sta.top();
	while (id_top != id_dummy) {
		if (is_terminator(id_top)) {
			if (data.cmp_token(now, terminator(id_top))) {
				sta.pop();
				now++;
			} else { return false; }
		} else {
			auto r = find_ll1(id_top, data.get_token(now));
			if (r) {
				//std::cout << t << ", " << token_name[data.get_token(now)] << "-> '" << r->second << "'" << std::endl;
				sta.pop();
				for (auto it = r->begin(); it != r->end(); it++) {
					std::stack<int> tmp = sta;
					int n = now;
					auto &prod = productions[it->first][it->second];
					for (auto it = prod.rbegin(); it != prod.rend(); it++) tmp.push(*it);
					if (parse_ll1(data, tmp, n)) {
						sta = tmp; now = n;
					}
				}
			} else {
				return false;
			}
		}
		id_top = sta.top();
	}
	return true;
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
	fill_ll1_table();
}



grammar::grammar() :token_map(get_token_map()) {
	init(bnf_c);
}
grammar::grammar(std::string const& bnf) : token_map(get_token_map()) {
	init(bnf);
}


void grammar::debug() {
	using std::cout;
	using std::endl;
	cout << "Symbols" << endl;
	for (auto &&x : mp) {
		cout << "{" << x.first << "," << x.second << "}";
	}
	cout << endl;
	cout << "Productions" << endl;
	for (auto&& x : productions) {
		cout << rev_mp[x.first] << " :" << endl;

		for (auto &&y : x.second) {
			cout << "--\t";
			if (y.size() == 0) {
				cout << "EMPTY PRODUCTION";
				//return;
			}
			for (auto &&z : y)cout << "{" << rev_mp[z] << "} ";
			cout << endl;
		}
	}
	cout << "First Set" << endl;
	for (auto &&x : first_set) {
		cout << '\t' << get_name(x.first) << " :";
		for (auto&& y : x.second) {
			cout << " " << get_name(y);
		}
		cout << endl;
	}
	cout << "Follow Set" << endl;
	for (auto &&x : follow_set) {
		cout << "\t" << get_name(x.first) << " :";
		for (auto&& y : x.second) {
			cout << " " << get_name(y);
		}
		cout << endl;
	}
	/*cout << "Token of Ts" << endl;
	for (auto&& tok : token_map) {
		cout << tok.first << " => " << token_name[tok.second] << endl;
	}*/
	cout << "LL1 TABLE" << endl;
	for (auto && x : ll1_table) {
		cout << "(" << get_name(x.first.first) << "," << token_name[x.first.second] << endl;

		for (auto &&y : x.second) {
			cout << "\t" << get_name(y.first) << " => ";
			for (auto &&xi : productions[y.first][y.second])cout << get_name(xi) << " ";
			cout << endl;
		}
	}
}