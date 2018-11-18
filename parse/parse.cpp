#include "parse.h"
#include "graph.h"
#include "lr.h"


void lr_closure(grammar & g, std::set<lr_item> I) {
	bool add_op = true;
	do {
		for(auto && item:I) {
			int B = g[item.exp_s][item.exp].size();
			if(B>item.pos) {
				B = g[item.exp_s][item.exp][item.pos];
				for(auto &&P:g[B]) {
					
				}
			}
			else { continue; }

		}
	} while (add_op);
}

void parser::parse() {
	//parse(result.get_root() = new ast::ast_node(), 0, "translation_unit");
}




//bool parser::parse(ast::ast_ptr pos, int now, std::string const&exp_s) {
//	for (auto && exp : grm[exp_s]) {
//		for (auto &&xi : exp) {
//			if (grm.is_terminator(xi)) {
//				if (grm.terminator(xi) == data.get_token(now)) {
//
//				}else {
//					return false;
//				}
//			} else {
//				ast::ast_node node;
//				if (parse(&node, now, grm.get_name(xi))) {
//
//				}
//			}
//		}
//	}
//}