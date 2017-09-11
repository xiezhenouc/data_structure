/**
 * @filename: rb_tree.h
 * @authore: xiezhen
 * @date: Sat Sep  9 14:08:57 CST 2017
 */
#include <cstddef>
#include <iostream>

using namespace std;

#ifndef _RB_TREE_HPP_
#define _RB_TREE_HPP_

enum RBTColor {RED, BLACK};

template <typename T>
struct RBTreeNode{
    RBTreeNode(RBTColor c, T value, RBTreeNode<T> *l, RBTreeNode<T> *r, RBTreeNode<T> *p)
    :color(c), key(value), lchild(l), rchild(r), parent(p) {}    

    RBTColor color;
    T key;
    RBTreeNode *lchild;
    RBTreeNode *rchild;
    RBTreeNode *parent;
};

template <typename T>
struct RBTree{
    RBTree()
    :root(NULL) {}          
    ~RBTree() {}         
public:
    RBTreeNode<T> *root;

public:
    RBTreeNode<T> *minimum(RBTreeNode<T> *root);
    RBTreeNode<T> *maximum(RBTreeNode<T> *root);

    void pre_order(RBTreeNode<T> *root) const;
    void in_order(RBTreeNode<T> *root) const;
    void post_order(RBTreeNode<T> *root) const;

    void print(RBTreeNode<T> *root, T key, int direction) const;
    void destroy(RBTreeNode<T> *&root);

    void insert(RBTreeNode<T> *&root, RBTreeNode<T>* node);
    void insert_fixup(RBTreeNode<T> *&root, RBTreeNode<T>* node);

    void remove(RBTreeNode<T> *&root, RBTreeNode<T>* node);
    void remove_fixup(RBTreeNode<T> *&root, RBTreeNode<T>* node, RBTreeNode<T>* parent);

    void left_rotation(RBTreeNode<T>* &root, RBTreeNode<T>* x);
    void right_rotation(RBTreeNode<T>* &root, RBTreeNode<T>* y);
};

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color == RED)
#define rb_is_black(r) ((r)->color == BLACK)
#define rb_set_red(r) do { (r)->color = RED; } while(0)
#define rb_set_black(r) do { (r)->color = BLACK; } while(0)
#define rb_set_parent(r, p) do { (r)->parent = (p); } while(0)
#define rb_set_color(r, c) do { (r)->color = (c); } while(0)

template<typename T>
void RBTree<T>::pre_order(RBTreeNode<T> *root) const
{
    if(root == NULL) 
    {
        return ;
    }
    cout << root->key << " ";
    pre_order(root->lchild);
    pre_order(root->rchild);
}

template<typename T>
void RBTree<T>::in_order(RBTreeNode<T> *root) const
{
    if(root == NULL)
    {
        return ;
    }
    in_order(root->lchild);
    cout << root->key << " ";
    in_order(root->rchild);
}

template<typename T>
void RBTree<T>::post_order(RBTreeNode<T> *root) const
{    
    if(root == NULL)
    {
        return ;
    }
    post_order(root->lchild);
    post_order(root->rchild);
    cout << root->key << " ";
}

template<typename T>
RBTreeNode<T>* RBTree<T>::minimum(RBTreeNode<T> *root)
{
    if(root != NULL)
    {
        while(root->lchild != NULL)
        {
            root = root->lchild;
        }
    }
    return root;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::maximum(RBTreeNode<T> *root)
{    
    if(root != NULL)
    {
        while(root->rchild != NULL)
        {
            root = root->rchild;
        }
    }
    return root;
}

/*
 *             px                              px
 *            +                               +  
 *           x                               y                
 *          /  +               ->           + \             
 *         lx   y                          x  ry     
 *            +   \                       /  + 
 *           ly   ry                     lx  ly   
 *
 * */
template<typename T>
void RBTree<T>::left_rotation(RBTreeNode<T>* &root, RBTreeNode<T>* x)
{
    //root not null
    //x not null
    //y not null
    RBTreeNode<T>* y = x->rchild;
    
    // x and ly
    x->rchild = y->lchild;
    if(y->lchild != NULL)
    {
        y->lchild->parent = x;
    }

    // y and px
    y->parent = x->parent;
    if(x->parent == NULL)
    {
        // x is root
        root = y;
    }
    else
    {
        if(x->parent->lchild == x)
        {
            x->parent->lchild = y;
        }
        else
        {
            x->parent->rchild = y;
        }
    }

    // x and y
    y->lchild = x;
    x->parent = y;
}

/*
 *                  py                               py
 *                 +                                + 
 *                y                                x                  
 *               +  \               ->            /  +                  
 *              x   ry                           lx   y  
 *             / +                                   + \           
 *            lx  rx                                rx  ry
 */
template<typename T>
void RBTree<T>::right_rotation(RBTreeNode<T>* &root, RBTreeNode<T>* y)
{
    //root not null
    //x not null
    //y not null
    RBTreeNode<T>* x = y->lchild;
    
    // y and rx
    y->lchild = x->rchild;
    if(x->rchild != NULL)
    {
        x->rchild->parent = y;
    }

    // x and py
    x->parent = y->parent;
    if(y->parent == NULL)
    {
        // y is root
        root = x;
    }
    else
    {
        if(y->parent->lchild == y)
        {
            y->parent->lchild = x;
        }
        else
        {
            y->parent->rchild = x;
        }
    }

    // x and y
    x->rchild = y;
    y->parent = x;
}

template<typename T>
void RBTree<T>::insert(RBTreeNode<T> *&root, RBTreeNode<T>* node)
{
    RBTreeNode<T> *y = NULL;
    RBTreeNode<T> *x = root;

    // 1 add node in to rb_tree 
    while(x != NULL)
    {
        y = x;
        if(node->key < x->key)
        {
            x = x->lchild;
        }
        else
        {
            x = x->rchild;
        }
    }

    node->parent = y;
    // tree have no nodes
    if(y == NULL)
    {
        root = node;
    }
    else
    {
        if(node->key < y->key)
        {
            y->lchild = node;
        }
        else
        {
            y->rchild = node;
        }
    }

    // 2 set node color to RED
    rb_set_red(node);

    // 3 key point. fix it and keep it to a rb_tree again
    insert_fixup(root, node);
}

template<typename T>
void RBTree<T>::insert_fixup(RBTreeNode<T> *&root, RBTreeNode<T>* node)
{
    RBTreeNode<T> *parent, *gparent;

    // if node's parent not null and node's parent is red 
    // do this while, else return
    while((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);
    
        // parent is left child of gparent
        if(parent == gparent->lchild)
        {
            RBTreeNode<T>* uncle = gparent->rchild;
            // case 1 : uncle is red
            if(uncle && rb_is_red(uncle))
            {
                rb_set_black(uncle);
                rb_set_black(parent);
                rb_set_red(gparent);
                node = gparent;
            }
            // notice!!!
            // case 2 and case 3 include uncle is null
            // case 2 : uncle is black and node is right child of parent
            else if(node == parent->rchild)
            {
                left_rotation(root, parent);

                // exchange parent and child
                RBTreeNode<T>* tmp = parent;
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // case 3 : uncle is black and node is left child of parent
            else{
                rb_set_black(parent);
                rb_set_red(gparent);
                right_rotation(root, gparent);
            }
        }
        // parent is right child of gparent
        else
        {
            RBTreeNode<T>* uncle = gparent->lchild;
            // case 1 : uncle is red
            if(uncle && rb_is_red(uncle))
            {
                rb_set_black(uncle);
                rb_set_black(parent);
                rb_set_red(gparent);
                node = gparent;
            }
            // case 2 : uncle is black and node is left child of parent
            else if(uncle && rb_is_black(uncle) && node == parent->lchild)
            {
                right_rotation(root, parent);

                // exchange parent and child
                RBTreeNode<T>* tmp = parent;
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // case 3 : uncle is black and node is right child of parent
            else{
                rb_set_black(parent);
                rb_set_red(gparent);
                left_rotation(root, gparent);
            }
        }
    }
    
    // set root node to black
    rb_set_black(root);
}

template<typename T>
void RBTree<T>::remove(RBTreeNode<T> *&root, RBTreeNode<T>* node)
{
    RBTreeNode<T> *child, *parent;
    RBTColor color;

    if(node->lchild != NULL && node->rchild != NULL)
    {
        // replace is smallest(leftest) element in node's right child tree
        RBTreeNode<T> *replace = node;
        
        replace = replace->rchild;
        while(replace->lchild != NULL) 
        {
            replace = replace->lchild;
        }

        //node's parent and replace
        if(rb_parent(node) != NULL)
        {
            //node is not root, update node parent's lchild and rchild
            if(rb_parent(node)->lchild == node)
            {
                rb_parent(node)->lchild = replace;
            }
            else
            {
                rb_parent(node)->rchild = replace;
            }
        }
        else
        {
            //node is root, node have no parents, so it does not need update 
            //parents, but we need update root
            root = replace;
        }

        // save rchild, parent and color of replace
        // replace have no lchild
        child = replace->rchild;
        parent = rb_parent(replace);
        color = rb_color(replace);

        if(parent == node) 
        {
            // replace become old replace's parent
            parent = replace;
        }
        else
        {
            //replace's child and replace's parent
            //child not NULL
            if(child != NULL)
            {
                rb_set_parent(child, parent);
            }
            parent->lchild = child;

            //replace and node's rchild
            replace->rchild = node->rchild;
            rb_set_parent(node->rchild, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->lchild = node->lchild;
        replace->lchild->parent = replace;
    
        if(color == BLACK)
        {
            remove_fixup(root, child, parent);
        }

        delete node;
        return ;
    }

    if(node->lchild != NULL)
    {
        child = node->lchild;
    }
    else
    {
        child = node->rchild;
    }

    parent = node->parent;
    color = node->color;
    if(child != NULL)
    {
        child->parent = parent;
    }
    
    if(parent != NULL)
    {
        if(parent->lchild == node)
        {
            parent->lchild = child;
        }
        else
        {
            parent->rchild = child;
        }
    }
    else
    {
        root = child;
    }   
    
    if(color == BLACK)
    {
        remove_fixup(root, child, parent);
    }
    delete node;
}

template<typename T>
void RBTree<T>::remove_fixup(RBTreeNode<T> *&root, RBTreeNode<T>* node, RBTreeNode<T>* parent)
{
    RBTreeNode<T> *other;
    
    // little question : while node is NULL can be here ?
    while(node == NULL || rb_is_black(node) && node != root)
    {
        if(parent->lchild == node)
        {   
            other = parent->rchild;
            if(rb_is_red(other))
            {
                // case 1: x's bro is red
                rb_set_black(other);
                rb_set_red(parent);
                left_rotation(root, parent);
                other = parent->rchild;
            }
            if((other->lchild != NULL || rb_is_black(other->lchild)) &&
               (other->rchild != NULL || rb_is_black(other->rchild))) 
            {
                // case 2: x's bro is black, and lchild and rchild is black
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {   
                if(other->rchild != NULL || rb_is_black(other->rchild))   
                {
                    // case 3 : x's bro is black, and lchild is red, rchild is black
                    rb_set_black(other->lchild);
                    rb_set_red(other);
                    right_rotation(root, other);
                    other = parent->rchild;
                }
                // case 4 : x's bro is black, and rchild is red, lchild can be black or red
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->rchild);
                left_rotation(root, parent);
                node = root;
                break;
            }
        }
        else
        {       
            other = parent->lchild;
            if(rb_is_red(other))
            {
                // case 1: x's bro is red
                rb_set_black(other);
                rb_set_red(parent);
                right_rotation(root, parent);
                other = parent->lchild;
            }
            if((other->lchild != NULL || rb_is_black(other->lchild)) &&
               (other->rchild != NULL || rb_is_black(other->rchild))) 
            {
                // case 2: x's bro is black, and lchild and rchild is black
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {   
                if(other->lchild != NULL || rb_is_black(other->lchild))   
                {
                    // case 3 : x's bro is black, and lchild is black, lchild is red 
                    rb_set_black(other->rchild);
                    rb_set_red(other);
                    left_rotation(root, other);
                    other = parent->lchild;
                }
                // case 4 : x's bro is black, and lchild is red, rchild can be black or red
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->lchild);
                right_rotation(root, parent);
                node = root;
                break;
            }

        }
    }
    if(node != NULL)
    {
        rb_set_black(node);
    }
}

#endif




























