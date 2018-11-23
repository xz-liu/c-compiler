#pragma once
#include "../lex/lex.h"
#include "../basic/bin_tree.h"
//
struct grammar {
private:
	static std::string literals[];
	std::map<std::string, int> mp;
	const std::map < std::string, token > token_map;
	std::vector<std::string> rev_mp;
	std::map<int, std::vector<std::vector<int>>> productions;
	std::map<int, std::set<int>> first_set;
	std::map<int, std::set<int>> follow_set;
	std::map<std::pair<int, token>, std::set<std::pair<int, int>>> ll1_table;
	template<class It>
	std::set<int> first_set_of_prod(It begin,It end) {
		std::set<int> ans;
		bool fucking_good = false;
		for (; begin != end;++begin) {
			bool good = true;
			if (first_set[*begin].empty()) {
				continue;
			} else for (auto && x : first_set[*begin]) {
				if (x != id_eps) {
					ans.insert(x);
				} else { good = false; }
			}
			if (good) {
				fucking_good = true;
				break;
			}
		}
		if (!fucking_good)ans.insert(id_eps);
		return ans;
	}
	void cal_first();
	void cal_follow();
	/*std::set<int> first_set(int S, int prod) {
		for (auto &&Xi :productions[S][prod]) {
			if (first[Xi].empty())continue;
			if(first[Xi].size()==1&&first[Xi])
		}
	}*/
	void fill_ll1_table();
	std::set<std::pair<int, int>> const* find_ll1(int top, token now) {
		auto it = ll1_table.find(std::make_pair(top, now));
		if (it != ll1_table.end())  return &it->second;
		return nullptr;
	}
	bool parse_ll1(lex_data const& data, std::stack<int> &sta, int &now);
	
	int cnt;
	int get_tok(std::string const&s) {
		auto it = mp.find(s);
		if (it != mp.end())return it->second;
		rev_mp.push_back(s);
		mp.emplace(s, cnt++);
		return cnt - 1;
	}
	int get_tok(std::string const& s)const {
		auto it = mp.find(s);
		if (it != mp.end())return it->second;
		return -1;
	}
	void init(std::string const& s);
public:
	int id_eps, id_dummy, id_s;
	std::string const& get_name(int t) const {
		return rev_mp[t];
	}
	grammar(std::string const& s);
	grammar(); 
	bool parse_ll1(lex_data const& data) {
		std::stack<int> sta;
		sta.push(id_dummy);
		sta.push(id_s);
		int now = 0;
		return parse_ll1(data, sta, now);
	}
	void debug();
	int add_symbol(std::string const& s) {
		int t = get_tok(s);
		productions[t].clear();
		return t;
	}
	void add_production(std::string const&s, std::vector<std::string> const&exp) {
		int S = get_tok(s);
		std::vector<int> vec;
		for (auto &&i : exp)vec.push_back(get_tok(i));
		productions[S].push_back(vec);
	}
	void add_production(std::string const& s, std::initializer_list<std::string> && exp) {
		add_production(s, exp);
	}
	std::vector<std::vector<int>> const& operator[](std::string const&S)const {
		return this->operator[](get_tok(S));
	}
	std::vector<std::vector<int>> const& operator[](int S)const {
		static const std::vector<std::vector<int>> dummy;
		auto it = productions.find(S);
		if (it != productions.end())return it->second;
		return dummy;
	}
	token terminator(int i) const {
		return terminator(get_name(i));
	}
	bool is_terminator(int i) const {
		if (i == id_eps || i == id_dummy)return true;
		return is_terminator(get_name(i));
	}
	bool is_terminator(std::string const& s) const {
		auto it = mp.find(s);
		if (it != mp.end())if (it->second == id_eps || it->second == id_dummy)return true;
		if (s[0] == '\'')return true;
		return token_map.find(s) != token_map.end();
	}
	token terminator(std::string const&t) const {
		//std::cout << t << std::endl;
		auto it = token_map.find(t);
		if (it == token_map.end())return token::dummy;
		else return it->second;
	}
};

struct ast :bin_tree<std::string> {
private:
	using _Base = bin_tree<std::string>;
public:
	using ast_node = _Base::node;
	using ast_ptr = _Base::ptr;

	ast() :_Base() {}
	static ast_ptr add_child(ast_ptr & n, const std::string &s) {
		if (n->has_lchild())return nullptr;
		else return n->insert_as_lchild(s);
	}
	static ast_ptr add_sibling(ast_ptr & n, const std::string &s) {
		if (n->has_rchild())return nullptr;
		else return n->insert_as_rchild(s);
	}
	static	ast_ptr child(ast_ptr & n) {
		return n->lc;
	}
	static ast_ptr sibling(ast_ptr & n) {
		return n->rc;
	}
	static std::string & dump(ast_ptr& n) {
		return n->val;
	}
	void debug(ast_ptr n) {
		using std::cout;
		using std::endl;
		if (!n)return;
		dump(n);
		debug(sibling(n));
		cout << "{" << endl;
		debug(child(n));
		cout << "}" << endl;
	}
	void debug() {
		debug(root);
	}
};

