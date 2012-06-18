#include "mhn_map.h"

typedef struct test_data_t test_data_t;

struct test_data_t
{
    int key;
    int data;
};
mhn_void test_data_free(mhn_void** elem)
{
    free (*elem);
    *elem = NULL;
}
int main(void)
{
    int i = 5;
    mhn_map_t*      map  = NULL;
    test_data_t*    data = NULL;

    mhn_rbn_data_free_pt handle_free = test_data_free;

    data = (test_data_t*)malloc(sizeof(test_data_t));

    handle_free((mhn_void**)&data);

    mhn_map_init(&map, NULL, test_data_free, mhn_compare_int);
    {
        data = (test_data_t*)malloc(sizeof(test_data_t));
        data->key = data->data = i;
        mhn_map_insert(map, (void*)&data->key, (void*)data);
        mhn_map_delete(map, (void*)&i);
    }
    mhn_map_free(&map);

    return 0;
}

