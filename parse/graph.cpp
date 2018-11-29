#include "graph.h"

std::string bnf_c =
R"()";

std::string grammar::literals[] = { "int_const", "char_const","float_const","id", "string","enumeration_const" };

bool grammar::ll1_table_product_cmp(product_reference const & a, product_reference const & b) {
	return	prod_index[std::make_pair(a.first, a.second)] >
			prod_index[std::make_pair(b.first,b.second)];
}

void grammar::cal_first() {
	for (auto&& x : mp) {
		// First(A) = A when A is a terminator
		if (is_semantic_action(x.second))continue;
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
						if (is_semantic_action(Yi))continue;
						if (is_terminator(Yi)) {
							prod_all_eps = false;
							next.insert(Yi);
							break;
						}
						next.insert(first_set[Yi].begin(), first_set[Yi].end());
						if (first_set[Yi].size()&& !set_contains(first_set[Yi], id_eps)) {
							prod_all_eps = false;
							break;
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
			if (is_semantic_action(S))continue;
			if (is_terminator(S))continue;
			for (auto &&exp : Sp.second) {
				if (exp.empty())continue;
				for (int i = 0; i < exp.size(); i++) {
					if (is_semantic_action(exp[i]))continue;;
					if (is_terminator(exp[i]))continue;
					int now = follow_set[exp[i]].size();
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

int grammar::cal_prod_index(int S,production const & prod) {
	int ind = 0;
	for(auto&& item:prod) {
		if (is_semantic_action(item))ind++;
		else if (item == id_eps)ind--;
		else if (is_terminator(item))ind++;
		else if (item == S)ind--;
	}
	return ind;
}

void grammar::fill_ll1_table() {
	cal_first();
	cal_follow();
	auto pthis = this;
	auto ll1_table_insert=[&](ll1_table_pred const& p, product_reference const& i) {
		auto it = ll1_table.find(p);
		if (it == ll1_table.end()) {
			ll1_table.emplace(p,ll1_table_item ([&](product_reference const&a,product_reference const &b) {
				return ll1_table_product_cmp(a, b);
			}));
			it = ll1_table.find(p);
		}
		it->second.insert(i);
	};

	for (auto &&all_prods : productions) {
		auto &&S = all_prods.first;
		if (is_semantic_action(S))continue;
		int prod_rk = 0;
		for (auto && prods : all_prods.second) {
			bool good = false;
			auto this_first = first_set_of_prod(prods.begin(), prods.end());
			for(auto &&t:this_first) {
				if(t==id_eps) {
					for (auto&& ft : follow_set[S])
						ll1_table_insert(
							std::make_pair(S, token_map.find(get_name(ft))->second), 
							std::make_pair(S, prod_rk)
						);
				}
				else {
					ll1_table_insert(
						std::make_pair(S, token_map.find(get_name(t))->second),
						std::make_pair(S, prod_rk)
					);
				}
			}
			prod_rk++;
		}

	}
}
//
//#define _MYDEBUG

bool grammar::parse_ll1(lex_data const & data, std::stack<grammar::ll1_stack_element>& sta, int & now,int now_w) {
	auto id_top = sta.top();
	while (id_top != id_dummy) {
#ifdef _MYDEBUG
		std::cout << "CURRENT _STACK TOP___ " << get_name(id_top)<<" ";// << std::endl;
#endif
		if (is_semantic_action(id_top)) {
#ifdef _MYDEBUG
			std::cout << "call func " << get_name(id_top) << std::endl;
#endif
			action[get_name(id_top)](data, now_w);
			sta.pop();
			id_top = sta.top();
			continue;
		}
		if (is_terminator(id_top)) {
#ifdef _MYDEBUG
			std::cout << "terminator "<< get_name(id_top)<< " " << data.get_token_name(now) ;
#endif
			if (data.cmp_token(now, terminator(id_top))) {
				sta.pop();
				now_w = now;
				now++;
#ifdef _MYDEBUG
				std::cout << " !!!!!!!accept" << std::endl;
#endif
			} else {
#ifdef _MYDEBUG
				std::cout << " reject" << std::endl;
#endif
				return false;
			}
		} else {

#ifdef _MYDEBUG
			std::cout << "!! "<< get_name(id_top)<< " "<< data.get_token_name(now) << std::endl;
#endif
			auto r = find_ll1(id_top, data.get_token(now));
			if (r) {
				bool good = false;
				for (auto it = r->begin(); it != r->end(); it++) {
					std::stack<ll1_stack_element> tmp = sta; 
					tmp.pop();
					int n = now;
					auto &prod = productions[it->first][it->second];

#ifdef _MYDEBUG
					std::cout << "!! try prod " << get_name(it->first) << "=>";
					for (auto && p : prod) std::cout << "{" << get_name(p) << "}";
					std::cout << std::endl;
#endif

					for (auto it = prod.rbegin(); it != prod.rend(); it++) tmp.push(*it);
					
					if (parse_ll1(data, tmp, n,now_w)) {
						if (id_top != id_s || n == data.lex_result.size()) {
							sta = tmp; now = n; good = true;
#ifdef _MYDEBUG				
							std::cout << "-- select this" << std::endl;
#endif
							break;
						}
					}
				}
				if(!good) {
#ifdef _MYDEBUG				
					std::cout << "-- reject -- all productions tried" << std::endl;
#endif
					return false;
				}
			} else {
#ifdef _MYDEBUG
				std::cout << " reject - no possible way" << std::endl;
#endif
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
		if (_1st) {
			_1st = false;
			S = s;
		}
		while (t != ";") {
			std::vector<std::string> vec;
			while (true) {
				cin >> t;
				std::cout << t << std::endl;
				if (t == "|" || t == ";")break;
				vec.push_back(t);
			}
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



grammar::grammar() 
:token_map(get_token_map()) {
	init(bnf_c);
}
grammar::grammar(std::string const& bnf) 
: token_map(get_token_map()) {
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
		cout <<" ["<< rev_mp[x.first]<<"] " << " :" << endl;

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
	cout << "LL1 TABLE" << endl;
	for (auto && x : ll1_table) {
		cout << "(" << get_name(x.first.first) << "," << token_name[x.first.second] << endl;

		for (auto &&y : x.second) {
			cout << "\t" << get_name(y.first) << " => ";
			for (auto &&xi : productions[y.first][y.second])cout << get_name(xi) << " ";
			cout << endl;
		}
	}
	cout << "Terminators" << endl;
	for(auto && x: mp) {
		if(this->operator[](x.second).empty()) {
			cout << x.first << " " ;
			if(!set_contains(token_map,x.first)) {
				cout << "FUCK!!!!!!!" << endl;
			}
			cout << endl;
		}
	}
}