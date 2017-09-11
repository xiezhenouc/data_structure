#include"avl_tree.h"

void print_tree(AVLTree<int> *p_cur_tree)
{
    cout << "----------pre_order-------------" << endl;
    p_cur_tree->pre_order(p_cur_tree->root);
    cout << "--------------------------------" << endl;

    cout << "-----------in_order-------------" << endl;
    p_cur_tree->in_order(p_cur_tree->root);
    cout << "--------------------------------" << endl;

    cout << "---------post_order-------------" << endl;
    p_cur_tree->post_order(p_cur_tree->root);
    cout << "--------------------------------" << endl;
}

void test_all()
{
    /** tree:
    *                    5
    *                  /   \
    *                3        7
    *              /   \     /  \
    *             2     4   6    8
    */ 
    AVLTreeNode<int> *p_val_2 = new AVLTreeNode<int>(2, NULL, NULL);
    AVLTreeNode<int> *p_val_4 = new AVLTreeNode<int>(4, NULL, NULL);
    AVLTreeNode<int> *p_val_6 = new AVLTreeNode<int>(6, NULL, NULL);
    AVLTreeNode<int> *p_val_8 = new AVLTreeNode<int>(8, NULL, NULL);
    AVLTreeNode<int> *p_val_3 = new AVLTreeNode<int>(3, p_val_2, p_val_4);
    AVLTreeNode<int> *p_val_7 = new AVLTreeNode<int>(7, p_val_6, p_val_8);
    AVLTreeNode<int> *p_val_5 = new AVLTreeNode<int>(5, p_val_3, p_val_7);

    AVLTree<int> *p_cur_tree = new AVLTree<int>();
    p_cur_tree->root = p_val_5;

    print_tree(p_cur_tree);
}

void test_left_rotation()
{
    /** tree:
    *    1                  
    *      \                  
    *         2       ->         2     
    *           \              /   \
    *             3           1      3
    */ 
    AVLTreeNode<int> *p_val_3 = new AVLTreeNode<int>(3, NULL, NULL);
    AVLTreeNode<int> *p_val_2 = new AVLTreeNode<int>(2, NULL, p_val_3);
    AVLTreeNode<int> *p_val_1 = new AVLTreeNode<int>(1, NULL, p_val_2);

    AVLTree<int> *p_cur_tree = new AVLTree<int>();
    p_cur_tree->root = p_val_1;

    print_tree(p_cur_tree);
    cout << "before left rotation" << endl;
    p_cur_tree->root = p_cur_tree->left_rotation(p_cur_tree->root);
    cout << "after left rotation" << endl;
    print_tree(p_cur_tree);
}

void test_right_rotation()
{
    /** tree:
    *            3               
    *          /               
    *         2       ->         2     
    *       /                  /   \
    *     1                   1      3
    */ 

    AVLTreeNode<int> *p_val_1 = new AVLTreeNode<int>(1, NULL, NULL);
    AVLTreeNode<int> *p_val_2 = new AVLTreeNode<int>(2, p_val_1, NULL);
    AVLTreeNode<int> *p_val_3 = new AVLTreeNode<int>(3, p_val_2, NULL);

    AVLTree<int> *p_cur_tree = new AVLTree<int>();
    p_cur_tree->root = p_val_3;

    print_tree(p_cur_tree);
    cout << "before right_rotation" << endl;
    p_cur_tree->root = p_cur_tree->right_rotation(p_cur_tree->root);
    cout << "after right_rotation" << endl;
    print_tree(p_cur_tree);
}

void test_left_right_rotation()
{
    /** tree:
    *            3                  3
    *          /                  / 
    *         2       ->        1      ->      1    
    *          \               /             /   \
    *            1           2              2      3
    */ 

    AVLTreeNode<int> *p_val_1 = new AVLTreeNode<int>(1, NULL, NULL);
    AVLTreeNode<int> *p_val_2 = new AVLTreeNode<int>(2, NULL, p_val_1);
    AVLTreeNode<int> *p_val_3 = new AVLTreeNode<int>(3, p_val_2, NULL);

    AVLTree<int> *p_cur_tree = new AVLTree<int>();
    p_cur_tree->root = p_val_3;

    print_tree(p_cur_tree);
    cout << "before test_left_right_rotation" << endl;
    p_cur_tree->root = p_cur_tree->left_right_rotation(p_cur_tree->root);
    cout << "after test_left_right_rotation" << endl;
    print_tree(p_cur_tree);
}

void test_right_left_rotation()
{
    /** tree:
    *     3               3                        
    *       \               \              
    *         2       ->       1        ->         1     
    *       /                    \               /   \
    *     1                        2            3      2
    */ 

    AVLTreeNode<int> *p_val_1 = new AVLTreeNode<int>(1, NULL, NULL);
    AVLTreeNode<int> *p_val_2 = new AVLTreeNode<int>(2, p_val_1, NULL);
    AVLTreeNode<int> *p_val_3 = new AVLTreeNode<int>(3, NULL, p_val_2);

    AVLTree<int> *p_cur_tree = new AVLTree<int>();
    p_cur_tree->root = p_val_3;

    print_tree(p_cur_tree);
    cout << "before right_left_rotation" << endl;
    p_cur_tree->root = p_cur_tree->right_left_rotation(p_cur_tree->root);
    cout << "after right_left_rotation" << endl;
    print_tree(p_cur_tree);
}

void test_insert_remove()
{
    AVLTree<int> *p_cur_tree = new AVLTree<int>();
    p_cur_tree->root = NULL;
    int keys_set[] = {4, 5, 6, 3, 2, 8, 7, 0, 1};
    
    for(int i = 0; i < 9; i++)
    {   
        p_cur_tree->insert(p_cur_tree->root, keys_set[i]);
    }
    cout << "test insert" << endl;
    print_tree(p_cur_tree);
  
    cout << "test remove" << endl;
    p_cur_tree->remove(p_cur_tree->root, 5);
    print_tree(p_cur_tree);
}

int main()
{
    //test_all();

    //test_left_rotation();
    
    //test_right_rotation();

    //test_left_right_rotation();

    //test_right_left_rotation();
    
    test_insert_remove();

    return 0;
}
