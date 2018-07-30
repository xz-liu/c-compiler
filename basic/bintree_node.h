//
// Created by joker on 2017/11/7.
//

#ifndef COMPILER_BINTREE_NODE_H
#define COMPILER_BINTREE_NODE_H

#include <functional>
#include <optional>
#include <cstdlib>
#include <queue>
#include "basic.h"
/**
 * binary node class template
 * T for data, and S for node status(optional)
 * node for all binary trees
 * implements lots of ordinary binary tree operations
 */
template <class T,class S=void>
struct bintree_node {
    using bnode_ptr=bintree_node *;
    using const_bnode_ptr=const bintree_node *;
    using visit_func=std::function<void(T &)> ;
	using const_visit_func=std::function<void(const T &)> ;
    T val;
	//an optional status type
	//if not needed 
	//the second template parameter should be void
	template<class _T>
	struct optional_status{
		_T _val;
		//check if status is needed
		static constexpr bool is_used(){return true;}
		template <class _InputTy>//assign a value to status
		void assign(const _InputTy& v){_val = v;}
		//get status value
	 	_T& val() { return _val; }
		operator _T () { return val(); };
		template <class _InputTy>
		optional_status& operator=(_InputTy const& v) 
		{ assign(v); }
	};
	template<>struct optional_status<void> {
		//status is not used
		static constexpr bool is_used() {return false;}
	};
	optional_status<S> status;
	//parent,lchild,rchild
	bintree_node *parent, *lc, *rc;
	int height;//node height
	//define the height for null node as -1 
    static int stature(bnode_ptr ptr) {
        return ptr ? ptr->height : -1;
    }

    bintree_node()
    : parent(nullptr), lc(nullptr), rc(nullptr), height(0){}

    explicit bintree_node(const T &val, bnode_ptr parent = nullptr,
                bnode_ptr lchild = nullptr, bnode_ptr rchild = nullptr,
                int height = 0)
    : val(val), parent(parent), lc(lchild), rc(rchild), height(height){}

    static void move_to_lc(bnode_ptr &ptr) { ptr = ptr->lc; }

    static void move_to_rc(bnode_ptr &ptr) { ptr = ptr->rc; }

    static void move_to_parent(bnode_ptr &ptr) { ptr = ptr->parent; }

    bool has_parent() const { if(!this)return true;return  parent; }

    bool is_root()const { return !has_parent(); }

	bool is_child() const { return !this || is_child() || is_rchild(); }

    bool is_lchild() const{ return !is_root() && (this == parent->lc); }

    bool is_rchild() const{ return !is_root() && (this == parent->rc); }

    bool has_lchild() const{ return lc; }

    bool has_rchild() const{ return rc; }

    bool has_child() const{ return has_lchild() || has_rchild(); }

    bool has_all_children() const{ return has_rchild() && has_rchild(); }

    bool is_leaf() const{ return !(this&&has_child()); }

    bnode_ptr& sibling() { return is_lchild() ? parent->rc : parent->lc; }

    bnode_ptr& uncle() {return parent->is_lchild() ? parent->parent->rc : parent->parent->lc; }

	//set the parent's reference of this node to another node
	bnode_ptr set_parent_ref(bnode_ptr ptr) {
		if (!this)return nullptr;
		if (is_root())return this;
		if (is_lchild())return parent->lc = ptr;
		return parent->rc = ptr;
	}  
	//get size (this as root)
    int size() {
        int size_now = 1;
        if (lc)size_now += lc->size();
        if (rc)size_now += rc->size();
        return size_now;
    }
	//inorder predecessor
	//used in iterator (++)
	bnode_ptr prev() {
		bnode_ptr s = this;
		if (rc) {
			s = rc;
			while (s->has_rchild())move_to_rc(s);
		} else {
			while (s->is_lchild())move_to_parent(s);
			move_to_parent(s);
		}
		return s;
    }
	//inorder successor
	//used in iterator (--)
    bnode_ptr next() {
        bnode_ptr s = this;
        if (rc) {
            s = rc;
            while (s->has_lchild())move_to_lc(s);
        } else {
            while (s->is_rchild())move_to_parent(s);
            move_to_parent(s);
        }
        return s;
    }

	const_bnode_ptr& next()const { return (const_cast<bnode_ptr >(this))->next(); }

	const_bnode_ptr& prev()const { return (const_cast<bnode_ptr >(this))->prev(); }

    bnode_ptr& insert_as_lchild(T const &val) { return lc = new bintree_node(val, this); }

    bnode_ptr& insert_as_rchild(T const &val) { return rc = new bintree_node(val, this); }

    bool operator<(bintree_node const &bn) const { return val < bn.val; }

    bool operator==(bintree_node const &bn) const { return val == bn.val; }

//implementing traversal
#define _BASE if (!this)return;
#define _VIS visit(val);
#define _NEXT_CHILD(child_type,trav_type) \
    child_type->trav_##trav_type##_order(visit);

#define _BINTREE_NODE_TRAV(trav_type,body)\
    void trav_##trav_type##_order(visit_func visit) {_BASE body } \
    void trav_##trav_type##_order(const_visit_func visit) const {_BASE body}

    _BINTREE_NODE_TRAV(in, _NEXT_CHILD(lc,in) _VIS _NEXT_CHILD(rc,in))
    _BINTREE_NODE_TRAV(pre, _VIS _NEXT_CHILD(lc,pre)_NEXT_CHILD(rc,pre))
    _BINTREE_NODE_TRAV(post, _NEXT_CHILD(lc,post)_NEXT_CHILD(rc,post)_VIS)

#undef _BINTREE_NODE_TRAV
//level traversal
#define _BINTREE_NODE_TRAV_LEVEL(prefix,attr)\
    void trav_level(prefix##visit_func visit) attr{\
        std::queue<prefix##bnode_ptr> Q;Q.push(this);\
        while (!Q.empty()){\
            prefix##bnode_ptr x=Q.front();\
            Q.pop();visit(x->val);\
            if(x->has_lchild()){ Q.push(x->lc); }\
            if(x->has_rchild()){ Q.push(x->rc); }\
        }\
    }

    _BINTREE_NODE_TRAV_LEVEL(,)
    _BINTREE_NODE_TRAV_LEVEL(const_, const)

#undef _BINTREE_NODE_TRAV_LEVEL
#undef _NEXT_CHILD
#undef _VIS
#undef _BASE
};

#endif //COMPILER_BINTREE_NODE_H
