//
// Created by joker on 2017/11/7.
//

#ifndef COMPILER_BIN_TREE_H
#define COMPILER_BIN_TREE_H

#include "bintree_node.h"
#include <algorithm>
/**
 * binary tree class template
 * T for data, and S for node status(optional)
 * base for all binary trees
 * implements lots of ordinary binary tree operations
 */
template <class T,class S=void>
class bin_tree {
protected:
	//bintree node type
    typedef bintree_node<T,S> node;
	//node pointer type
    using ptr=typename bintree_node<T,S>::bnode_ptr;
    using const_ptr=typename bintree_node<T,S>::const_bnode_ptr;
	//size of the tree
    int tree_size;
	//root node pointer
    ptr root;
	//update height of a node after insertion/deletion
    virtual int update_height(ptr x){
        return x->height=
          1+std::max(node::stature(x->lc),node::stature(x->rc));
    }
	//update height above the node x
    void update_height_above(ptr x){
        while (x){
            update_height(x);
            node::move_to_parent(x);
        }
    }
	//leftmost node in a tree
	//used in implementing iterator(begin)
    ptr& begin_node()const{
        ptr& x= const_cast<ptr&>(root);
        while (x->has_lchild())node::move_to_lc(x);
        return x;
    }
	//rightmost node in a tree
	//used in implementing iterator(rbegin)
    ptr& end_node()const {
		ptr& x = const_cast<ptr&>(root);
        while (x->has_rchild())node::move_to_rc(x);
        return x;
    }
	//pre-order init a binary tree
	//deprecated
    template <class CharT>
    void pre_order_init(std::basic_istream<CharT> &in,
                        typename bintree_node<T,S>::bnode_ptr &now,
                        typename bintree_node<T,S>::bnode_ptr parent,
                        int& size,const T &sepreator) {
        T x;if (!(in >> x)) return;
        if (x == sepreator)
        { now = nullptr;return; }
        size++;now = (new bintree_node<T,S>(x,parent));
        pre_order_init(in, now->lc,now,size, sepreator);
        pre_order_init(in, now->rc,now,size,sepreator);

    }

public:
	//visit function type 
    using visit_func=typename node::visit_func;
    using const_visit_func=typename node::const_visit_func;
    //type alias for node pointer
	using position= bintree_node<T,S>*;
    using const_position= const bintree_node<T,S>*;

	//default constructor
    bin_tree():tree_size(0),root(nullptr){}
	
	//destructor
    virtual ~bin_tree(){clear();}

	//pre-order init a binary tree
	//deprecated
    template <class CharT=char>
    void pre_order_init(std::basic_istream<CharT> &in,const T &sepreator){
        this->clear();
        pre_order_init(in,root, nullptr,tree_size,sepreator);
        in.clear();
    }

	//copy data from another binary tree
	//implementation of operator= and copy constructor
	bin_tree& copy_from(const bin_tree& rhs) {
		root = nullptr;//reset root
		copy_from(root, nullptr, rhs.root);
		tree_size = rhs.tree_size;//copy size
		return *this;
    }
	static void copy_from(ptr& dst,ptr parent,ptr src) {
		if (!src)return;//trivial cases(when reach null node)
		//construct a new node from src
		dst = new bintree_node<T, S>(src->val,parent,nullptr,nullptr,src->height);
		//init status(if used)
		if constexpr (src->status.is_used()&&dst->status.is_used())
    		dst->status.assign(src->status.val());
		//pre order trav
		copy_from(dst->lc, dst, src->lc);
		copy_from(dst->rc, dst, src->rc);
    }

	virtual bin_tree& operator=(const bin_tree& rhs) {
		clear();
		return copy_from(rhs);
	}

	bin_tree(const bin_tree& rhs){
	   	copy_from(rhs);
    }
	
	// deletes all tree nodes
	void clear_tree(position ptr) {
	    if(ptr) {
			clear_tree(ptr->lc);
			clear_tree(ptr->rc);
			delete ptr;
	    }
    }
	//clear the tree
    virtual void clear(){
		clear_tree(root);
		root = nullptr;
		tree_size = 0;
    }

//traversal 
//calls traversal function of root
#define BINTREE_TRAV(type_name)\
void trav_##type_name(visit_func vis)\
{if(root)root->trav_##type_name(vis);}\
void trav_##type_name(const_visit_func vis)const\
{if(root)root->trav_##type_name(vis);}

    BINTREE_TRAV(level)//level traversal
    BINTREE_TRAV(in_order)//in order traversal
    BINTREE_TRAV(pre_order)//pre order traversal
    BINTREE_TRAV(post_order)//post order traversal

#undef BINTREE_TRAV

	//front node
    T& front(){ return **begin_node(); }
    const T& front()const { return **end_node();}
	//end node
	T& back(){return **end_node()}
    const T& back()const {	return **end_node();}
	//...
    position& get_root(){ return root; }
    const_position get_root()const { return root;}
};

#endif //DATA_STRUCTURE_EXP_BIN_TREE_H
