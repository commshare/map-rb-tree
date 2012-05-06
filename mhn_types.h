/// @file     mhn_types.h
/// @brief    data type definition
/// @author   birdyfj@gmail.com
/// @version  1.0-c
/// @date     2011-03-21

#ifndef MHN_TYPES_H
#define MHN_TYPES_H

#include <time.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

/// @def
#define MHN_BOOL_TRUE           0                       ///< boolean value : true
#define MHN_BOOL_FALSE          -1                      ///< boolean value : false
#define MHN_RET_SUCCESS         0                       ///< return value : success
#define MHN_RET_FAIL            -1                      ///< return value : fail
#define mhn_sleep(n)            usleep(n)               ///< sleep n microsecond
#define MHN_MAX(a,b)            (((a)>(b))?(a):(b))     ///< return the lager value between a and b
#define MHN_MIN(a,b)            (((a)>(b))?(b):(a))     ///< return the smaller value between a and b
#define MHN_EXCHANGE(a,b)                               \
    ({                                                  \
        (a) = (a) ^ (b);                                \
        (a) = (a) ^ (b);                                \
        (b) = (a) ^ (b);                                \
    })                                                  ///< exchange a and b
#define MHN_LAST_ERROR          errno                   ///< error code
#define MHN_IS_IO_BLOCKED                               \
    ((errno == EWOULDBLOCK)||(errno == EAGAIN)          \
    ||(errno == EWOULDBLOCK))                           ///< indicate if net io is blocked
#define MHN_CURRENT_TIME_TICK                           \
    ({                                                  \
        struct timeval t;                               \
        gettimeofday(&t, 0);                            \
        ((t.tv_sec * 1000000ULL + t.tv_usec)/1000);     \
    })                                                  ///< get current time tick
#define MAX_SCHEDULE_TASK         16                    ///< max schedule task count
#define MHN_RES_PIECE_LENGTH    1024                    ///< resource data piece length
#define MHN_PKT_PREFIX_LEN        16                    ///< protocol prefix length


/// @typedef
typedef void                        mhn_void;
typedef char              mhn_char, mhn_i8;
typedef short                       mhn_i16;
typedef int               mhn_bool, mhn_int;
typedef long                        mhn_i32;
typedef long long                   mhn_i64;
typedef unsigned char    mhn_uchar, mhn_ui8;
typedef unsigned short              mhn_ui16;
typedef unsigned int                mhn_uint;
typedef unsigned long               mhn_ui32;
typedef unsigned long long          mhn_ui64;
typedef FILE*                       mhn_file_pt;
typedef struct sockaddr             sockaddr;
typedef struct sockaddr_in          sockaddr_in;

typedef enum   mhn_data_t           mhn_data_t;         ///< moho protocol data type
typedef struct mhn_data_prefix_t    mhn_data_prefix_t;  ///< moho protocol prefix
typedef enum   mhn_dt_nat_t         mhn_dt_nat_t;       ///< NAT type
typedef enum   mhn_dt_node_t        mhn_dt_node_t;      ///< net node type
typedef struct mhn_dt_dsn_node_t    mhn_dt_dsn_node_t;  ///< DSN node information
typedef enum   mhn_dt_res_err_t     mhn_dt_res_err_t;   ///< resource error code type
typedef enum   mhn_dt_res_trans_t   mhn_dt_res_trans_t; ///< resource data transmission type
typedef struct mhn_dt_owner_node_t  mhn_dt_owner_node_t;///< resource data owner information

typedef struct mhn_dt_login_requ_t          mhn_dt_login_requ_t;                ///< log in tracker request
typedef struct mhn_dt_login_resp_t          mhn_dt_login_resp_t;                ///< log in tracker response
typedef struct mhn_dt_connect_requ_t        mhn_dt_connect_requ_t;              ///< connect to dsn reqeust
typedef struct mhn_dt_connect_resp_t        mhn_dt_connect_resp_t;              ///< connect to dsn response
typedef struct mhn_dt_res_search_requ_t     mhn_dt_res_search_requ_t;           ///< resource search reqeust
typedef struct mhn_dt_res_search_requ_t     mhn_dt_res_search_resp_file_info_t; ///< resource search response by file information
typedef struct mhn_dt_res_search_requ_t     mhn_dt_res_search_resp_owners_t;    ///< resource search response by resource owners
typedef struct mhn_dt_res_data_requ_t       mhn_dt_res_data_requ_t;             ///< resource data reqeust
typedef struct mhn_dt_res_data_piece_resp_t mhn_dt_res_data_piece_resp_t;       ///< resource data response
typedef struct mhn_dt_res_err_resp_t        mhn_dt_res_err_resp_t;              ///< resource data transe error response

/// @enum
enum   mhn_data_t
{
    MHN_DT_LOGIN_REQU               = 0x00010007,
    MHN_DT_LOGIN_RESP               = 0x00010002,
    MHN_DT_CONNECT_REQU             = 0x00010003,
    MHN_DT_CONNECT_RESP             = 0x00010004,
    MHN_DT_NAT_BURROWING_REQU       = 0x00020001,
    MHN_DT_NAT_BURROWING_RESP       = 0x00020002,
    MHN_DT_NAT_KEEP_LIVE_RESP       = 0x00020003,
    MHN_DT_RES_SEARCH_REQU          = 0x00030007,
    MHN_DT_RES_SEARCH_RESP_OWNERS   = 0x00030004,
    MHN_DT_RES_SEARCH_RESP_INFO     = 0x0003000D,
    MHN_DT_FILE_DATA_REQU           = 0x00030006,
    MHN_DT_FILE_DATA_PIECE_RESP     = 0x00030005,
    MHN_DT_RES_ERR_RESP             = 0x000300FF
};
enum   mhn_dt_nat_t
{
    MHN_NAT_UNKNOWN  = 0,
    MHN_NAT_PUBLIC,
    MHN_NAT_FULL_CONE,
    MHN_NAT_RESTRICT_FULL,
    MHN_NAT_RESTRICT_PORT,
    MHN_NAT_SYMMETRIC
};
enum   mhn_dt_node_t
{
    MHN_NODE_UNKNOWN = 0,
    MHN_NODE_DSN_HUB,
    MHN_NODE_LEAVES,
    MHN_NODE_DEFAULT_HUB,
    MHN_NODE_NAT_CHECKER
};
enum   mhn_dt_res_err_t
{
    MHN_RES_ERR_SUCCESS             = 0x00,
    MHN_RES_ERR_TOO_MANY_TASKS      = 0x01,
    MHN_RES_ERR_FILE_HANDLER        = 0x02,
    MHN_RES_ERR_FILE_INVALID        = 0x03,
    MHN_RES_ERR_TOO_MANY_SLOTS      = 0x04,
    MHN_RES_ERR_READ_FILE           = 0x05,
    MHN_RES_ERR_TOO_MANY_TRANS      = 0x06,
    MHN_RES_ERR_PROTOCOL_REFUSED    = 0x07,
    MHN_RES_ERR_REQUEST_PARAMETER   = 0x08,
    MHN_RES_ERR_FILE_DELETED        = 0x09,
    MHN_RES_ERR_OTHER               = 0xFF
};
enum mhn_dt_res_trans_t
{
    MHN_RES_TRANS_REDO,     ///< re-transe it
    MHN_RES_TRANS_NORMAL,   ///< add task to the end of the send queue at server peer
    MHN_RES_TRANS_SEEK      ///< skip all the previous reqeust and start data transmission from this request
};

/// @struct
#pragma pack(push, 4)
struct mhn_data_prefix_t
{
    mhn_ui32    m_type;     ///< moho protocol data type
    mhn_ui32    m_length;   ///< pakcet length
    mhn_ui64    m_uid;      ///< user id
};
struct mhn_dt_dsn_node_t
{
    mhn_ui64    m_dsn_uid;  ///< dsn user id
    mhn_ui32    m_dsn_ip;   ///< dsn ip
};
struct mhn_dt_owner_node_t
{
    mhn_ui64    m_owner_uid;    ///< owner user id
    mhn_ui32    m_owner_ip;     ///< owner ip
    mhn_ui16    m_owner_port;   ///< owner port
};
struct mhn_dt_login_requ_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui16            m_username_len;
    mhn_ui16            m_password_len;
};
struct mhn_dt_login_resp_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui64            m_uid;
    mhn_ui64            m_server_time;      ///< server time tick
    mhn_ui32            m_dsn_list_len;     ///< dsn list length
};
struct mhn_dt_connect_requ_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui32            m_my_udp_ip;        ///< local ip
    mhn_ui16            m_my_udp_port;      ///< local udp port
};
struct mhn_dt_connect_resp_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui32            m_nat_type;         ///< local NAT type
};
struct mhn_dt_res_search_requ_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui64            m_resource_id;      ///< resource id = 32-bit file id + 32bit block (2MB) id
};
struct mhn_dt_res_data_requ_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui64            m_resource_id;
    mhn_ui16            m_start_position;   ///< request start position in one block
    mhn_ui16            m_end_position;     ///< request end position in one block
    mhn_ui16            m_trans_type;       ///< transmission type; see #mhn_dt_res_trans_s
    mhn_ui32            m_trans_mask;       ///< transmission mask; 1, request it; 0, skip it
};
struct mhn_dt_res_data_piece_resp_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui64            m_resource_id;      ///< resource id
    mhn_ui16            m_piece_id;         ///< resource data piece (1KB) ed, between 0 and 2047
};
struct mhn_dt_res_err_resp_t
{
    mhn_data_prefix_t   m_prefix;
    mhn_ui64            m_resource_id;
    mhn_ui16            m_error_position;   ///< transmission error position by resource data piece id
    mhn_dt_res_err_t    m_error_code;
};
#pragma pack(pop)

/// @fn
mhn_int mhn_compare_int   (const void* key1, const void* key2);
mhn_int mhn_compare_long  (const void* key1, const void* key2);
mhn_int mhn_compare_i64   (const void* key1, const void* key2);
mhn_int mhn_compare_uint  (const void* key1, const void* key2);
mhn_int mhn_compare_ulong (const void* key1, const void* key2);
mhn_int mhn_compare_ui64  (const void* key1, const void* key2);

#endif/*MHN_TYPES_H*/
