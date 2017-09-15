#include<cstdio>
#include<cmath>

inline int get_mid(int x, int y)
{
    return x + (y - x) / 2;
}

int construct_segment_tree_core(int arr[], int arr_left, int arr_right, int *src_data, int src_index)
{
    // leaf node
    if(arr_left == arr_right)
    {
        src_data[src_index] = arr[arr_left];
        return arr[arr_left];
    }
    // split [arr_left, arr_right]
    int mid = get_mid(arr_left, arr_right);
    // cur: src_index, left_child: src_index * 2 + 1, right_child: src_index * 2 + 2
    // cur node = left child node + right child node
    src_data[src_index] = construct_segment_tree_core(arr, arr_left, mid, src_data, src_index * 2 + 1) +
                          construct_segment_tree_core(arr, mid + 1, arr_right, src_data, src_index * 2 + 2);

    return src_data[src_index];
}

int* construct_segment_tree(int arr[], int n)
{
    int x = (int)(ceil(log2(n)));
    int max_size = 2 * (int)pow(2, x) - 1;
    int *src_data = new int[max_size];

    construct_segment_tree_core(arr, 0, n - 1, src_data, 0);

    return src_data;
}

int get_sum_core(int src_data[], int src_index, int arr_left, int arr_right, int query_left, int query_right)
{
    // 1 [query_left, query_right] contains [arr_left, arr_right]
    if(query_left <= arr_left && query_right >= arr_right)
    {
        return src_data[src_index];
    } 
    // 2 [query_left, query_right] does not touch with [arr_left, arr_right]
    if(query_left > arr_right || query_right < arr_left)
    {
        return 0; 
    }
    // 3 [query_left, query_right] does touch with [arr_left, arr_right]
    // split [arr_left, arr_right]
    int mid = get_mid(arr_left, arr_right);
    return get_sum_core(src_data, src_index * 2 + 1, arr_left, mid, query_left, query_right) +
           get_sum_core(src_data, src_index * 2 + 2, mid + 1, arr_right, query_left, query_right);

}

int get_sum(int src_data[], int n, int query_left, int query_right)
{
    get_sum_core(src_data, 0, 0, n - 1, query_left, query_right); 
}

void update_value_core(int *src_data, int arr_left, int arr_right, int arr_index, int diff, int src_index)
{
    if(arr_index < arr_left || arr_index > arr_right) return ;
    
    src_data[src_index] += diff;
    //arr_left == arr_right, we have add diff in update_value
    if(arr_left != arr_right)
    {
        int mid = get_mid(arr_left, arr_right);
        update_value_core(src_data, arr_left, mid, arr_index, diff, 2 * src_index + 1);
        update_value_core(src_data, mid + 1, arr_right, arr_index, diff, 2 * src_index + 2);
    }
}

void update_value(int arr[], int *src_data, int n, int arr_index, int new_value)
{
    int diff = new_value - arr[arr_index];
    arr[arr_index] = new_value;
    
    update_value_core(src_data, 0, n - 1, arr_index, diff, 0);
}

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    int *src_data = construct_segment_tree(arr, n);

    printf("%d\n", get_sum(src_data, n, 1, 3));
    update_value(arr, src_data, n, 1, 10);
    printf("%d\n", get_sum(src_data, n, 1, 3));

    return 0;
}
