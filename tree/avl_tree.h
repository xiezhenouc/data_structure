/**
 * @filename: avl_tree.h
 * @authore: xiezhen
 * @date: Fri Sep  8 12:43:35 CST 2017
 */
#include <cstddef>
#include <iostream>

using namespace std;

#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

template <typename T>
struct AVLTreeNode{
    AVLTreeNode(T value, AVLTreeNode<T> *l, AVLTreeNode<T> *r)
    :key(value), lchild(l), rchild(r) {}    

    T key;
    int height;
    AVLTreeNode *lchild;
    AVLTreeNode *rchild;
};

template <typename T>
struct AVLTree{
    AVLTree() {}          
    ~AVLTree() {}         
public:
    AVLTreeNode<T> *root;

public:
    int max(int a, int b);
    int height(AVLTreeNode<T> *pnode);

    AVLTreeNode<T> *minimum(AVLTreeNode<T> *pnode) const;
    AVLTreeNode<T> *maximum(AVLTreeNode<T> *pnode) const;

    void pre_order(AVLTreeNode<T> *pnode) const;
    void in_order(AVLTreeNode<T> *pnode) const;
    void post_order(AVLTreeNode<T> *pnode) const;

    void print(AVLTreeNode<T> *pnode, T key, int direction) const;
    void destroy(AVLTreeNode<T> *&pnode);

    AVLTreeNode<T>* insert(AVLTreeNode<T> *&pnode, T key);
    AVLTreeNode<T>* remove(AVLTreeNode<T> *&pnode, T key);

    AVLTreeNode<T> *left_rotation(AVLTreeNode<T> *pnode);
    AVLTreeNode<T> *right_rotation(AVLTreeNode<T> *pnode);
    AVLTreeNode<T> *left_right_rotation(AVLTreeNode<T> *pnode);
    AVLTreeNode<T> *right_left_rotation(AVLTreeNode<T> *pnode);
};

template<typename T>
int AVLTree<T>::max(int a, int b)
{
    return a > b ? a : b;
}

template<typename T>
int AVLTree<T>::height(AVLTreeNode<T> *pnode)
{
    return pnode != NULL ? pnode->height: 0;
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::minimum(AVLTreeNode<T> *pnode) const
{
    if(pnode != NULL)
    {
        while(pnode->lchild != NULL)
        {
            pnode = pnode->lchild;
        }
    }
    return pnode;
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::maximum(AVLTreeNode<T> *pnode) const
{
    if(pnode != NULL)
    {
        while(pnode->rchild != NULL)
        {
            pnode = pnode->rchild;
        }
    }
    return pnode;

}

template<typename T>
void AVLTree<T>::pre_order(AVLTreeNode<T> *pnode) const
{
    if(pnode == NULL) 
    {
        return ;
    }
    cout << pnode->key << endl;
    pre_order(pnode->lchild);
    pre_order(pnode->rchild);
}

template<typename T>
void AVLTree<T>::in_order(AVLTreeNode<T> *pnode) const
{
    if(pnode == NULL)
    {
        return ;
    }
    in_order(pnode->lchild);
    cout << pnode->key << endl;
    in_order(pnode->rchild);
}

template<typename T>
void AVLTree<T>::post_order(AVLTreeNode<T> *pnode) const
{
    if(pnode == NULL)
    {
        return ;
    }
    post_order(pnode->lchild);
    post_order(pnode->rchild);
    cout << pnode->key << endl;
}

template<typename T>
void AVLTree<T>::print(AVLTreeNode<T> *pnode, T key, int direction) const
{
}

template<typename T>
void AVLTree<T>::destroy(AVLTreeNode<T> *&pnode)
{
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T> *&pnode, T key)
{
    if(pnode == NULL)
    {
        //create node
        pnode = new AVLTreeNode<T>(key, NULL, NULL);
    }   
    else if(key < pnode->key)
    {
        //left child tree
        pnode->lchild = insert(pnode->lchild, key);
        if(height(pnode->lchild) - height(pnode->rchild) == 2)
        {
            // left left
            if(key < pnode->lchild->key)
            {
                pnode = right_rotation(pnode);
            }
            // left right
            else
            {
                pnode = left_right_rotation(pnode);
            }
        }
        
    }      
    else if(key > pnode->key)
    { 
        //right child tree
        pnode->rchild = insert(pnode->rchild, key);
        if(height(pnode->rchild) - height(pnode->lchild) == 2)
        {
            // right left
            if(key < pnode->rchild->key)
            {
                pnode = right_left_rotation(pnode);
            }
            // right right
            else
            {
                pnode = left_rotation(pnode);
            }
        }
    }
    else
    {
        //key == pnode->key 
        //error
        cout << "error" << endl;
    }

    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    return pnode;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T> *&pnode, T key)
{
    if(pnode != NULL)
    {
        //find remove element
        if(key == pnode->key)
        {
            // left child and right child both are not NULL
            if(pnode->lchild != NULL && pnode->rchild != NULL)
            {
                // left child tree height > right child tree height
                // pnode->key = left child tree maximum element
                // delete left child tree maximum element
                if(height(pnode->lchild) > height(pnode->rchild))
                {
                    AVLTreeNode<T>* ppre = maximum(pnode->lchild);
                    pnode->key = ppre->key;
                    pnode->lchild = remove(pnode->lchild, ppre->key);
                }
                // left child tree height < right child tree height
                // pnode->key = right child tree minimum element
                // delete right child tree minimum element
                else
                {
                    AVLTreeNode<T>* psuc = minimum(pnode->rchild);
                    pnode->key = psuc->key;
                    pnode->rchild = remove(pnode->rchild, psuc->key);
                }
            }
            // left child or right child is not NULL
            else
            {
                AVLTreeNode<T> *ptemp = pnode;
                if(pnode->lchild != NULL)
                {
                    pnode = pnode->lchild;
                }
                else if(pnode->rchild != NULL)
                {
                    pnode = pnode->rchild;
                }
                delete ptemp;
                return NULL;
            }
        }
        // go to right child tree
        else if(key > pnode->key)
        {
            pnode->rchild = remove(pnode->rchild, key);
            // remove results to not balance == add element results to not balance
            if(height(pnode->lchild) - height(pnode->rchild) == 2)
            {
                // left and left 
                if(height(pnode->lchild->lchild) > height(pnode->lchild->rchild))
                {
                    pnode = right_rotation(pnode);
                }    
                // left and right
                else
                {
                    pnode = left_right_rotation(pnode);
                }
            }
        }
        // go to left child tree
        else
        {
            pnode->lchild = remove(pnode->lchild, key);
            // remove results to not balance == add element results to not balance
            if(height(pnode->rchild) - height(pnode->lchild) == 2)
            {
                // right and left
                if(height(pnode->rchild->lchild) > height(pnode->rchild->rchild))
                {
                    pnode = right_left_rotation(pnode);
                }    
                // right and right
                else
                {
                    pnode = left_rotation(pnode);
                }
            }
        }
        return pnode;
    }
    return NULL;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::left_rotation(AVLTreeNode<T> *pnode)
{
    if(pnode == NULL || pnode->rchild == NULL)
    {
        return pnode;
    }

    AVLTreeNode<T> *pnode_rchild = pnode->rchild;
    pnode->rchild = pnode_rchild->lchild;
    pnode_rchild->lchild = pnode;

    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    pnode_rchild->height = max(height(pnode_rchild->lchild), height(pnode_rchild->rchild)) + 1;

    return pnode_rchild;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::right_rotation(AVLTreeNode<T> *pnode)
{
    if(pnode == NULL || pnode->lchild == NULL)
    {
        return pnode;
    }

    AVLTreeNode<T> *pnode_lchild = pnode->lchild;
    pnode->lchild = pnode_lchild->rchild;
    pnode_lchild->rchild = pnode;

    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    pnode_lchild->height = max(height(pnode_lchild->lchild), height(pnode_lchild->rchild)) + 1;

    return pnode_lchild;

}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::left_right_rotation(AVLTreeNode<T> *pnode)
{
    if(pnode == NULL)
    {
        return NULL;
    }
    pnode->lchild = left_rotation(pnode->lchild); 
    return right_rotation(pnode);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::right_left_rotation(AVLTreeNode<T> *pnode)
{
    if(pnode == NULL)
    {
        return NULL;
    }
    pnode->rchild = right_rotation(pnode->rchild);
    return left_rotation(pnode);
}

#endif
