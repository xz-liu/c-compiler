#pragma once
#include "../lex/lex.h"
#include "../basic/bin_tree.h"

struct grammar {
private:
	std::map<std::string, int> mp;
	std::map < std::string , token > token_map;
	std::vector<std::string> rev_mp;
	std::map<int, std::vector<std::vector<int>>> productions;
	std::map<int, std::set<int>> first;
	std::map<int, std::set<int>> follow;
	void cal_first(int);
	void cal_follow(int S) {
		 
	}
	int cnt;
	int get_tok(std::string const&s) {
		auto it = mp.find(s);
		if (it != mp.end())return it->second;
		rev_mp.push_back(s);
		mp.emplace(s, cnt++);
		return cnt - 1;
	}
public:
	std::string const& get_name(int t) const{
		return rev_mp[t];
	}
	grammar();
	void debug() {
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
			if(x.second.size()==0) {
				cout << "EMPTY!!!!!!!!!!!!!!!!!!!!" << endl;
				return;
			}
			for (auto &&y : x.second) {
				cout << "\t";
				for (auto &&z : y)cout << rev_mp[z] << " ";
				cout << endl;
			}
		}
	}
	int add_symbol(std::string const& s) {
		int t = get_tok(s);
		productions[t].clear();
		return t;
	}
	void add_production(std::string const&s, std::vector<std::string> const&exp){
		int S = get_tok(s);
		std::vector<int> vec;
		for (auto &&i : exp)vec.push_back(get_tok(i));
		productions[S].push_back(vec);
	}
	void add_production(std::string const& s, std::initializer_list<std::string> && exp) {
		add_production(s, exp);
	}
	std::vector<std::vector<int>> & operator[](std::string const&S) {
		return productions[get_tok(S)];
	}
	std::vector<std::vector<int>> & operator[](int S) {
		return productions[S];
	}


	token terminator(int i) const{
		return terminator(get_name(i));
	}
	bool is_terminator(int i) const {
		return is_terminator(get_name(i));
	}
	bool is_terminator(std::string const& s) const{
		return s[0] == '\'';
	}
	token terminator(std::string const&t) const {
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
	static ast_ptr add_child(ast_ptr & n,const std::string &s) {
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
	static std::string & dump(ast_ptr& n){
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

