#include "mhn_rbtree.h"

/// rotate right
/*-----------------------------------------------------------
  (0)               (1)           (2)           (3)
       ||                                          ||
      node            ||             ||           temp
     //  \\          node           temp         //  \\
   temp   c   ==>   //  \\   ==>   //      ==>   a   node
  //  \\            b    c         a                //  \\
  a    b                                            b    c
-----------------------------------------------------------*/
static mhn_void mhn_rbt_rotate_right (mhn_rbt_node_t** root, mhn_rbt_node_t* node)
{
    mhn_rbt_node_t* temp = node->m_left;

    /// (1)
    if (NULL != (node->m_left = temp->m_right))
    {
        temp->m_right->m_parent = node;
    }

    /// (2)
    if (NULL != (temp->m_parent = node->m_parent))
    {
        if (node->m_parent->m_left == node)
        {
            node->m_parent->m_left = temp;
        }
        else
        {
            node->m_parent->m_right = temp;
        }
    }
    else
    {
        *root = temp;
    }

    /// (3)
    temp->m_right  = node;
    node->m_parent = temp;
}
/// rotate left
/*-----------------------------------------------------------
  (0)               (1)            (2)           (3)
    ||                                               ||
   node               ||            ||               ri
  //  \\             node           ri             //  \\
  a    ri     ==>   //  \\   ==>      \\   ==>    node  c
     //  \\         a    b             c         //  \\
     b    c                                      a    b
-----------------------------------------------------------*/
static mhn_void mhn_rbt_rotate_left  (mhn_rbt_node_t** root, mhn_rbt_node_t* node)
{
    mhn_rbt_node_t* right  = node->m_right;

    /// (1)
    if (NULL != (node->m_right = right->m_left))
    {
        right->m_left->m_parent = node;
    }

    /// (2)
    if (NULL != (right->m_parent = node->m_parent))
    {
        if (node->m_parent->m_left == node)
        {
            node->m_parent->m_left = right;
        }
        else
        {
            node->m_parent->m_right = right;
        }
    }
    else
    {
        *root = right;
    }

    /// (3)
    right->m_left  = node;
    node->m_parent = right;
}
/// search node (keep positions of node and parent)
static mhn_void mhn_rbt_search_auxiliary (mhn_rbt_node_t*  root, mhn_rbt_node_t** node, mhn_rbt_node_t** parent\
    , mhn_rbt_key_compare_pt compare_handler, const void* key)
{
    mhn_int ret;
    mhn_rbt_node_t* save = NULL;

    *node   = root;

    while (*node != NULL)
    {
        save = *node;
        ret = compare_handler(key, (*node)->m_key);
        if (ret > 0)
        {
            *node   = (*node)->m_right;
        }
        else if (ret < 0)
        {
            *node   = (*node)->m_left;
        }
        else
        {
            break;
        }
    }

    if (parent != NULL)
    {
        *parent = save;
    }
}
/// insert node and rebalence
static mhn_void mhn_rbt_insert_rebalence (mhn_rbt_node_t** root, mhn_rbt_node_t* node)
{
    mhn_rbt_node_t* p_node = NULL;
    mhn_rbt_node_t* u_node = NULL;
    mhn_rbt_node_t* g_node = NULL;

    while ((NULL != (p_node = node->m_parent)) && p_node->m_color == RBT_RED)
    {
        g_node = p_node->m_parent;
        if (p_node == g_node->m_left)
        {
            u_node = g_node->m_right;
            /*-----------------------------------
                   G(B)               P(B)
                  //  \\             //  \\
                P(R)  U(B)   ==>   N(R)  G(R)
                //                         \\
               N(R)                        U(B)
            -----------------------------------*/
            if (u_node == NULL || u_node->m_color == RBT_BLACK)
            {
                if (node == g_node->m_right)
                {
                    mhn_rbt_node_t* temp;
                    mhn_rbt_rotate_left(root, p_node);
                    temp = node;
                    node = p_node;
                    p_node = temp;
                }
                p_node->m_color = RBT_BLACK;
                g_node->m_color = RBT_RED;
                mhn_rbt_rotate_right(root, g_node);
            }
            /*-----------------------------------
                   G(B)               G(R)
                  //  \\             //  \\
                P(R)  U(R)   ==>   P(B)  U(B)
                //                 //
               N(R)               N(R)
            -----------------------------------*/
            else
            {
                p_node->m_color = RBT_BLACK;
                u_node->m_color = RBT_BLACK;
                g_node->m_color = RBT_RED;
                node = g_node;
            }
        }
        else
        {
            /*-----------------------------------
                   G(B)               P(B)
                  //  \\             //  \\
                U(B)  P(R)   ==>   G(R)  N(R)
                        \\         //
                        N(R)      U(B)
            -----------------------------------*/
            u_node = g_node->m_left;
            if (u_node == NULL || u_node->m_color == RBT_BLACK)
            {
                if (node == p_node->m_left)
                {
                    mhn_rbt_node_t* temp;
                    mhn_rbt_rotate_right(root, p_node);
                    temp = node;
                    node = p_node;
                    p_node = temp;
                }
                p_node->m_color = RBT_BLACK;
                g_node->m_color = RBT_RED;
                mhn_rbt_rotate_left(root, g_node);
            }
            else
            {
                p_node->m_color = RBT_BLACK;
                u_node->m_color = RBT_BLACK;
                g_node->m_color = RBT_RED;
                node = g_node;
            }
        }
    }

    (*root)->m_color = RBT_BLACK;
}
/// delete node and rebalence
static mhn_void mhn_rbt_delete_rebalence (mhn_rbt_node_t** root, mhn_rbt_node_t* node, mhn_rbt_node_t* parent)
{
    mhn_rbt_node_t* other;
    mhn_rbt_node_t* o_left;
    mhn_rbt_node_t* o_right;

    while ((node == NULL || node->m_color == RBT_BLACK) && node != *root)
    {
        if (parent->m_left == node)
        {
            other = parent->m_right;
            if (other->m_color == RBT_RED)
            {
                other->m_color = RBT_BLACK;
                parent->m_color = RBT_RED;
                mhn_rbt_rotate_left(root, parent);
                other = parent->m_right;
            }
            if ((!other->m_left  || other->m_left->m_color  == RBT_BLACK) &&
                (!other->m_right || other->m_right->m_color == RBT_BLACK))
            {
                other->m_color = RBT_RED;
                node = parent;
                parent = node->m_parent;
            }
            else
            {
                if (!other->m_right || other->m_right->m_color == RBT_BLACK)
                {
                    if ((o_left = other->m_left))
                    {
                        o_left->m_color = RBT_BLACK;
                    }
                    other->m_color = RBT_RED;
                    mhn_rbt_rotate_right(root, other);
                    other = parent->m_right;
                }
                other->m_color = parent->m_color;
                parent->m_color = RBT_BLACK;
                if (other->m_right)
                {
                    other->m_right->m_color = RBT_BLACK;
                }
                mhn_rbt_rotate_left(root, parent);
                node = *root;
                break;
            }
        }
        else
        {
            other = parent->m_left;
            if (other->m_color == RBT_RED)
            {
                other->m_color = RBT_BLACK;
                parent->m_color = RBT_RED;
                mhn_rbt_rotate_right(root, parent);
                other = parent->m_left;
            }
            if ((!other->m_left  || other->m_left->m_color  == RBT_BLACK)\
             && (!other->m_right || other->m_right->m_color == RBT_BLACK))
            {
                other->m_color = RBT_RED;
                node = parent;
                parent = node->m_parent;
            }
            else
            {
                if (!other->m_left || other->m_left->m_color == RBT_BLACK)
                {
                    if ((o_right = other->m_right))
                    {
                        o_right->m_color = RBT_BLACK;
                    }
                    other->m_color = RBT_RED;
                    mhn_rbt_rotate_left(root, other);
                    other = parent->m_left;
                }
                other->m_color = parent->m_color;
                parent->m_color = RBT_BLACK;
                if (other->m_left)
                {
                    other->m_left->m_color = RBT_BLACK;
                }
                mhn_rbt_rotate_right(root, parent);
                node = (*root);
                break;
            }
        }
    }

    if (node != NULL)
    {
        node->m_color = RBT_BLACK;
    }
}

mhn_bool  mhn_rbt_node_init (mhn_rbt_node_t** node, mhn_rbn_data_init_pt init_handler, const void* key, void* data\
    , mhn_rbt_node_t* parent)
{
    if (*node == NULL)
    {
        (*node) = (mhn_rbt_node_t*)malloc(sizeof(mhn_rbt_node_t));
        if (*node == NULL)
        {
            return MHN_RET_FAIL;
        }
    }
    if (init_handler != NULL && MHN_RET_FAIL == init_handler(&data))
    {
        free (*node);
        *node = NULL;
        return MHN_RET_FAIL;
    }

    (*node)->m_color  = RBT_RED;
    (*node)->m_data   = data;
    (*node)->m_key    = key;
    (*node)->m_parent = parent;
    (*node)->m_left   = NULL;
    (*node)->m_right  = NULL;

    return MHN_RET_SUCCESS;
}
mhn_void  mhn_rbt_node_free (mhn_rbt_node_t** node, mhn_rbn_data_free_pt free_handler)
{
    if (*node != NULL)
    {
        if (free_handler != NULL)
        {
            free_handler(&(*node)->m_data);
        }
        free (*node);
        *node = NULL;
    }
}
mhn_void* mhn_rbt_search (mhn_rbt_node_t*  root, mhn_rbt_key_compare_pt compare_handler, const void* key)
{
    mhn_rbt_node_t* node = NULL;
    mhn_rbt_search_auxiliary(root, &node, NULL, key, compare_handler);
    if (node == NULL)
    {
        return NULL;
    }
    return node->m_data;
}
mhn_bool  mhn_rbt_insert (mhn_rbt_node_t** root, mhn_rbt_key_compare_pt compare_handler\
    , mhn_rbn_data_init_pt init_handler, const void* key, void* data)
{
    mhn_rbt_node_t* parent = NULL;
    mhn_rbt_node_t* node   = NULL;

    mhn_rbt_search_auxiliary(*root, &node, &parent, compare_handler, key);
    if (node != NULL)
    {
        return MHN_RET_FAIL;
    }

    if (MHN_RET_FAIL == mhn_rbt_node_init(&node, init_handler, key, data, parent))
    {
        return MHN_RET_FAIL;
    }

    if (parent == NULL)
    {
        *root = node;
    }
    else
    {
        int ret = compare_handler(key, parent->m_key);
        if (ret > 0)
        {
            parent->m_right = node;
        }
        else
        {
            parent->m_left  = node;
        }
    }

    mhn_rbt_insert_rebalence(root, node);
    return MHN_RET_SUCCESS;
}
mhn_bool  mhn_rbt_delete (mhn_rbt_node_t** root, mhn_rbt_key_compare_pt compare_handler\
    , mhn_rbn_data_free_pt free_handler, const void* key)
{
    mhn_rbt_node_t* node   = NULL;

    mhn_rbt_search_auxiliary (*root, &node, NULL, compare_handler, key);
    if (node == NULL)
    {
        return MHN_RET_FAIL;
    }

    return mhn_rbt_delete_by_node(root, free_handler, node);
}
mhn_bool  mhn_rbt_delete_by_node (mhn_rbt_node_t** root, mhn_rbn_data_free_pt free_handler, mhn_rbt_node_t* node)
{
    mhn_rbt_node_t* old;
    mhn_rbt_node_t* parent;
    mhn_rbt_node_t* child;
    mhn_rbt_color_t color;

    if (node == NULL)
    {
        return MHN_RET_FAIL;
    }

    old = node;

    if (node->m_left != NULL && node->m_right != NULL)
    {
        node = node->m_right;
        while (node->m_left != NULL)
        {
            node = node->m_left;
        }
        child   = node->m_right;
        parent  = node->m_parent;
        color   = node->m_color;

        if (child != NULL)
        {
            child->m_parent = parent;
        }
        if (parent != NULL)
        {
            if (node == parent->m_left)
            {
                parent->m_left  = child;
            }
            else
            {
                parent->m_right = child;
            }
        }
        else
        {
            *root = child;
        }

        if (free_handler != NULL)
        {
            free_handler(&old->m_data);
        }
        old->m_key    = node->m_key;
        old->m_data   = node->m_data;
        node->m_data  = NULL;
        mhn_rbt_node_free(&node, free_handler);
    }
    else
    {
        if (node->m_left == NULL)
        {
            child = node->m_right;
        }
        else
        {
            child = node->m_left;
        }
        parent  = node->m_parent;
        color   = node->m_color;

        if (child != NULL)
        {
            child->m_parent = parent;
        }
        if (parent != NULL)
        {
            if (node == parent->m_left)
            {
                parent->m_left  = child;
            }
            else
            {
                parent->m_right = child;
            }
        }
        else
        {
            *root = child;
        }
    }

    if (color == RBT_BLACK)
    {
        mhn_rbt_delete_rebalence(root, child, parent);
    }
    return MHN_RET_SUCCESS;
}

