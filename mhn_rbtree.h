/// @file     mhn_rbtree.h
/// @brief    red-black tree
/// @author   birdyfj@gmail.com
/// @version  1.0-c
/// @date     2011-04-13

#ifndef MHN_RBTREE_H
#define MHN_RBTREE_H

#include "mhn_types.h"

/// @typedef
typedef struct mhn_rbt_node_t   mhn_rbt_node_t;     ///< red-black tree node structure
typedef enum   mhn_rbt_color_t  mhn_rbt_color_t;    ///< red-black tree node color

typedef mhn_bool (*mhn_rbn_data_init_pt)(mhn_void** elem);
typedef mhn_void (*mhn_rbn_data_free_pt)(mhn_void** elem);
/// @return -1, key1 < key2; 0, key1 == key2; 1, key1 > key2
typedef mhn_int  (*mhn_rbt_key_compare_pt)(const mhn_void*, const mhn_void*);

/// @enum
enum   mhn_rbt_color_t
{
    RBT_RED,
    RBT_BLACK
};

/// @struct
struct mhn_rbt_node_t
{
    const mhn_int   *m_key;
//    const mhn_void *m_key;              ///< key
    mhn_void       *m_data;             ///< data
    mhn_rbt_node_t *m_left, *m_right;   ///< sons
    mhn_rbt_node_t *m_parent;           ///< parent
    mhn_rbt_color_t m_color;            ///< node color
};

/// @fn
/// create red-black tree node
mhn_bool  mhn_rbt_node_init (mhn_rbt_node_t**, mhn_rbn_data_init_pt, const void*, void*, mhn_rbt_node_t*);
/// destroy red-black tree node
mhn_void  mhn_rbt_node_free (mhn_rbt_node_t**, mhn_rbn_data_free_pt);
/// search node
/// @return node data
mhn_void* mhn_rbt_search (mhn_rbt_node_t* , mhn_rbt_key_compare_pt, const void*);
/// insert node
mhn_bool  mhn_rbt_insert (mhn_rbt_node_t**, mhn_rbt_key_compare_pt, mhn_rbn_data_init_pt, const void*, void*);
/// delete node by key
mhn_bool  mhn_rbt_delete (mhn_rbt_node_t**, mhn_rbt_key_compare_pt, mhn_rbn_data_free_pt, const void*);
/// delete node by node
mhn_bool  mhn_rbt_delete_by_node (mhn_rbt_node_t**, mhn_rbn_data_free_pt, mhn_rbt_node_t*);
#endif // MHN_RBTREE_H
