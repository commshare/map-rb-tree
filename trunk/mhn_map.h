/// @file     mhn_map.h
/// @brief    map
/// @author   birdyfj@gmail.com
/// @version  1.0-c
/// @date     2011-04-19

#ifndef MHN_MAP_H
#define MHN_MAP_H

#include "mhn_rbtree.h"

/// @typedef
typedef struct mhn_map_t mhn_map_t;

/// @struct
struct mhn_map_t
{
    mhn_rbt_node_t*         m_root;
    mhn_rbn_data_init_pt    m_data_init_handler;    ///< element initialization handler
    mhn_rbn_data_free_pt    m_data_free_handler;    ///< element destruction handler
    mhn_rbt_key_compare_pt  m_compare_handler;      ///< key value comparing handler
};

/// @fn
/// initialization map
mhn_bool  mhn_map_init (mhn_map_t** map
    , mhn_rbn_data_init_pt   init_handler
    , mhn_rbn_data_free_pt   free_handler
    , mhn_rbt_key_compare_pt compare_handler);
/// destruction map
mhn_void  mhn_map_free (mhn_map_t** map);
/// search by key and return data
mhn_void* mhn_map_search (mhn_map_t* map, const void *key);
/// insert
mhn_bool  mhn_map_insert (mhn_map_t* map, const void* key, void* data);
/// delete
mhn_bool  mhn_map_delete (mhn_map_t* map, const void *key);
/// delete by node
mhn_bool  mhn_map_delete_by_node (mhn_map_t* map, mhn_rbt_node_t* node);

#endif/*MHN_MAP_H*/
