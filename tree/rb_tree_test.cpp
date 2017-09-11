#include"rb_tree.h"

void print_tree(RBTree<int> *p_cur_tree)
{
    cout << endl << "----------pre_order-------------" << endl;
    p_cur_tree->pre_order(p_cur_tree->root);

    cout << endl << "-----------in_order-------------" << endl;
    p_cur_tree->in_order(p_cur_tree->root);

    cout << endl << "---------post_order-------------" << endl;
    p_cur_tree->post_order(p_cur_tree->root);

    cout << endl;
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
    RBTreeNode<int> *p_val_2 = new RBTreeNode<int>(BLACK, 2, NULL, NULL, NULL);
    RBTreeNode<int> *p_val_4 = new RBTreeNode<int>(BLACK, 4, NULL, NULL, NULL);
    RBTreeNode<int> *p_val_6 = new RBTreeNode<int>(BLACK, 6, NULL, NULL, NULL);
    RBTreeNode<int> *p_val_8 = new RBTreeNode<int>(BLACK, 8, NULL, NULL, NULL);
    RBTreeNode<int> *p_val_3 = new RBTreeNode<int>(RED, 3, p_val_2, p_val_4, NULL);
    RBTreeNode<int> *p_val_7 = new RBTreeNode<int>(RED, 7, p_val_6, p_val_8, NULL);
    RBTreeNode<int> *p_val_5 = new RBTreeNode<int>(BLACK, 5, p_val_3, p_val_7, NULL);
   
    //set parent
    rb_set_parent(p_val_2, p_val_3);
    rb_set_parent(p_val_4, p_val_3);
    rb_set_parent(p_val_6, p_val_7);
    rb_set_parent(p_val_8, p_val_7);
    rb_set_parent(p_val_3, p_val_5);
    rb_set_parent(p_val_7, p_val_5);

    RBTree<int> *p_cur_tree = new RBTree<int>();
    p_cur_tree->root = p_val_5;

    print_tree(p_cur_tree);
    
    //test max 
    cout << "max: " << (p_cur_tree->maximum(p_cur_tree->root))->key << endl;
    //test min
    cout << "max: " << (p_cur_tree->minimum(p_cur_tree->root))->key << endl;

    //test left rotation
    p_cur_tree->left_rotation(p_cur_tree->root, p_val_5);
    cout << "after left rotation: " << endl;
    print_tree(p_cur_tree);

    //test right rotation
    p_cur_tree->right_rotation(p_cur_tree->root, p_val_7);
    cout << "after right rotation: " << endl;
    print_tree(p_cur_tree);
}

void test_insert_remove()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int arr_len = sizeof(a) / sizeof(a[0]); 
    RBTree<int> *p_cur_tree = new RBTree<int>();
    p_cur_tree->root = NULL;

    cout << "start insert:" << endl;
    for(int i = 0; i < arr_len; i++)
    {
        RBTreeNode<int> *p_tmp = new RBTreeNode<int>(BLACK, a[i], NULL, NULL, NULL);
        p_cur_tree->insert(p_cur_tree->root, p_tmp); 
    }
    cout << "after insert: " << endl;
    print_tree(p_cur_tree);

    RBTreeNode<int> *p_tmp_remove = new RBTreeNode<int>(BLACK, 100, NULL, NULL, NULL);
    p_cur_tree->insert(p_cur_tree->root, p_tmp_remove); 

    cout << "before remove: " << endl;
    print_tree(p_cur_tree);
    p_cur_tree->remove(p_cur_tree->root, p_tmp_remove);
    cout << "after remove: " << endl;
    print_tree(p_cur_tree);
}
int main()
{
    //test_all();

    test_insert_remove();

    return 0;
}

