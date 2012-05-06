/// @file     mhn_buffer.h
/// @brief    buffer object, buffer object set
/// @author   birdyfj@gmail.com
/// @version  1.0-c
/// @date     2011-03-23

#ifndef MHN_BUFFER_H
#define MHN_BUFFER_H

#include "mhn_types.h"
#include "mhn_queue.h"

/// @def
#define MHN_CIRCLE_BUFFER_SIZE 23040    ///< circle buffer length
#define MHN_FIXED_LEN_BUF_SIZE 1152     ///< fixed-length buffer length
#define MHN_SEND_QUEUE_MAX_LEN 4        ///< max number of buffer objects in send queue

/// @typedef
typedef enum   mhn_io_option_t  mhn_io_option_t;    ///< net io option
typedef struct mhn_buffer_t     mhn_buffer_t;       ///< buffer object structure
typedef struct mhn_buffer_set_t mhn_buffer_set_t;   ///< buffer object set structure

/// @enum
enum   mhn_io_option_t
{
    IOOPTION_TCP_ACPT   = 001,
    IOOPTION_TCP_RECV   = 002,
    IOOPTION_UDP_RECV   = 004,
    IOOPTION_TCP_CONN   = 010,
    IOOPTION_TCP_SEND   = 020,
    IOOPTION_UDP_SEND   = 040,
    IOOPTION_RECV       = 007,
    IOOPTION_SEND       = 070,
    IOOPTION_TCP        = 033,
    IOOPTION_UDP        = 044
};

/// @struct
struct mhn_buffer_t
{
    mhn_io_option_t m_option;           ///< net io option see #mhn_io_option_e
    mhn_ui8*        m_buffer;           ///< buffer space
    mhn_ui32        m_length;           ///< buffer space length
    mhn_ui32        m_data_size;        ///< buffer data size , just for udp send
    mhn_ui32        m_read_pos;         ///< read  position, just for tcp receive
    mhn_ui32        m_write_pos;        ///< write position, just for tcp receive
    mhn_ui32        m_last_write_pos;   ///< last write position, just for tcp receive
    union
    {
        mhn_int     m_error_flag;       ///< error flag
        mhn_int     m_client_socket;    ///< client socket fd, for accept at server peer
    };
    sockaddr        m_peer_addr;        ///< peer ipv4 address structure
};
struct mhn_buffer_set_t
{
    mhn_buffer_t*   m_recv_obj;         ///< receive buffer object
    mhn_queue_t*    m_send_queue;       ///< send queue
};

/// @fn about buffer object
/// create buffer object
mhn_bool mhn_buffer_init (mhn_buffer_t** buf, mhn_io_option_t option);
static __inline mhn_bool mhn_buffer_init_for_tcp_send (void** buf)
{
    return mhn_buffer_init ((mhn_buffer_t**)buf, IOOPTION_TCP_SEND);
}
static __inline mhn_bool mhn_buffer_init_for_tcp_recv (void** buf)
{
    return mhn_buffer_init ((mhn_buffer_t**)buf, IOOPTION_TCP_RECV);
}
static __inline mhn_bool mhn_buffer_init_for_udp_send (void** buf)
{
    return mhn_buffer_init ((mhn_buffer_t**)buf, IOOPTION_UDP_SEND);
}
static __inline mhn_bool mhn_buffer_init_for_udp_recv (void** buf)
{
    return mhn_buffer_init ((mhn_buffer_t**)buf, IOOPTION_UDP_RECV);
}
/// destroy buffer object
mhn_void mhn_buffer_free (mhn_buffer_t** buf);
static __inline mhn_void mhn_buffer_free_handler (void** buf)
{
    mhn_buffer_free((mhn_buffer_t**)buf);
}
/// update buffer object after reading
mhn_void mhn_buf_update_after_reading (mhn_buffer_t* buf, mhn_ui32 size);
/// update buffer object after writing
mhn_void mhn_buf_update_after_writing (mhn_buffer_t* buf, mhn_ui32 size);
/// get buffer read position
/// @return length can read
mhn_ui32 mhn_buf_get_rd_pos (mhn_buffer_t* buf, mhn_ui8** data);
/// get buffer write position
/// @return length can write
mhn_ui32 mhn_buf_get_wr_pos (mhn_buffer_t* buf, mhn_ui8** data);

/// @fn about buffer set
/// create buffer set
mhn_bool mhn_buffer_set_init (mhn_buffer_set_t** bufset, int protocol);
/// destroy buffer set
mhn_void mhn_buffer_set_free (mhn_buffer_set_t** bufset);

#endif/*MOHO_BUFFER_H*/
