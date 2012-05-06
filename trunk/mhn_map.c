#include "mhn_map.h"

static mhn_void  mhn_rbt_free (mhn_rbt_node_t** root, mhn_rbn_data_free_pt free_handler)
{
    if (*root != NULL)
    {
        if ((*root)->m_left != NULL)
        {
            mhn_rbt_free(&(*root)->m_left, free_handler);
        }
        if ((*root)->m_right != NULL)
        {
            mhn_rbt_free(&(*root)->m_right, free_handler);
        }
        if (free_handler != NULL)
        {
            mhn_rbt_node_free(root, free_handler);
        }
    }
}
mhn_bool  mhn_map_init (mhn_map_t** map, mhn_rbn_data_init_pt init_handler, mhn_rbn_data_free_pt free_handler\
    , mhn_rbt_key_compare_pt compare_handler)
{
    if (*map == NULL)
    {
        *map = (mhn_map_t*)malloc(sizeof(mhn_map_t));
        if (*map == NULL)
        {
            return MHN_RET_FAIL;
        }
    }
    (*map)->m_root = NULL;
    (*map)->m_data_init_handler = init_handler;
    (*map)->m_data_free_handler = free_handler;
    (*map)->m_compare_handler   = compare_handler;

    return MHN_RET_SUCCESS;
}
mhn_void  mhn_map_free (mhn_map_t** map)
{
    if(*map != NULL)
    {
        if ((*map)->m_root != NULL)
        {
            mhn_rbt_free(&(*map)->m_root, (*map)->m_data_free_handler);
        }
        free (*map);
        *map = NULL;
    }
}
mhn_void* mhn_map_search (mhn_map_t* map, const void* key)
{
    mhn_rbt_node_t* node;
    node = mhn_rbt_search(map->m_root, map->m_compare_handler, key);
    if (node == NULL)
    {
        return NULL;
    }
    return node->m_data;
}
mhn_bool  mhn_map_insert (mhn_map_t* map, const void* key, void* data)
{
    return mhn_rbt_insert(&map->m_root, map->m_compare_handler, map->m_data_init_handler, key, data);
}
mhn_bool  mhn_map_delete (mhn_map_t* map, const void* key)
{
    return mhn_rbt_delete(&map->m_root, map->m_compare_handler, map->m_data_free_handler, key);
}
mhn_bool  mhn_map_delete_by_node (mhn_map_t* map, mhn_rbt_node_t* node)
{
    return mhn_rbt_delete_by_node(&map->m_root, map->m_data_free_handler, node);
}


