#include "mhn_types.h"

/// @fn value compare
mhn_int mhn_compare_int   (const void* key1, const void* key2)
{
    mhn_int _key1 = (*(mhn_int*)key1);
    mhn_int _key2 = (*(mhn_int*)key2);
    if (_key1 >  _key2) {return  1;}
    else if (_key1 == _key2) {return  0;}
    return -1;
}
mhn_int mhn_compare_long  (const void* key1, const void* key2)
{
    mhn_i32 _key1 = (*(mhn_i32*)key1);
    mhn_i32 _key2 = (*(mhn_i32*)key2);
    if (_key1 >  _key2) {return  1;}
    else if (_key1 == _key2) {return  0;}
    return -1;
}
mhn_int mhn_compare_i64   (const void* key1, const void* key2)
{
    mhn_i64 _key1 = (*(mhn_i64*)key1);
    mhn_i64 _key2 = (*(mhn_i64*)key2);
    if (_key1 >  _key2) {return  1;}
    else if (_key1 == _key2) {return  0;}
    return -1;
}
mhn_int mhn_compare_uint  (const void* key1, const void* key2)
{
    mhn_uint _key1 = (*(mhn_uint*)key1);
    mhn_uint _key2 = (*(mhn_uint*)key2);
    if (_key1 >  _key2) {return  1;}
    else if (_key1 == _key2) {return  0;}
    return -1;
}
mhn_int mhn_compare_ulong (const void* key1, const void* key2)
{
    mhn_ui32 _key1 = (*(mhn_ui32*)key1);
    mhn_ui32 _key2 = (*(mhn_ui32*)key2);
    if (_key1 >  _key2) {return  1;}
    else if (_key1 == _key2) {return  0;}
    return -1;
}
mhn_int mhn_compare_ui64  (const void* key1, const void* key2)
{
    mhn_ui64 _key1 = (*(mhn_ui64*)key1);
    mhn_ui64 _key2 = (*(mhn_ui64*)key2);
    if (_key1 >  _key2) {return  1;}
    else if (_key1 == _key2) {return  0;}
    return -1;
}
