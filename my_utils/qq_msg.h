/*************************************************************************
	> File Name: qq_msg.h
	> Author: wnavy
	> Mail: whjwnavy@163.com 
	> Created Time: Fri 15 Sep 2017 05:28:03 PM CST
 ************************************************************************/
#ifndef __QQ_MSG_H__
#define __QQ_MSG_H__

#include "list.h"
#include "type.h"

#define QQ_USRLST_USE_MALLOC    1
#define QQ_MSG_USE_ENCODE       1
#define QQ_MSG_ENCODE_LEN       50

#define QQ_USER_NAME_LEN        20
#define QQ_MSG_SPRT             "///"
#define QQ_MSG_SPRT_LEN         (sizeof(QQ_MSG_SPRT)-1)

#define QQ_MSG_FLAG             "@@@@@@@@"
#define QQ_MSG_FLAG_LEN         (sizeof(QQ_MSG_FLAG)-1) //uninclude '\0'

#define QQ_MSG_HEDMBR_LEN       (sizeof("FFFFFFFF")-1)//uninclude '\0'
#define QQ_MSG_HEDS_LEN         ((QQ_MSG_HEDMBR_LEN+QQ_MSG_SPRT_LEN)*4)
#define QQ_MSG_PKTS_LEN         (1024*sizeof(int8))
#define QQ_MSG_BUFFS_LEN        (QQ_MSG_FLAG_LEN+QQ_MSG_HEDS_LEN+QQ_MSG_PKTS_LEN)

typedef enum qq_msg_type_e
{
    QQ_MSG_TYPE_LOGIN       = 0X01,
    QQ_MSG_TYPE_LOGOUT      = 0X02,
    QQ_MSG_TYPE_UNICAST     = 0X04,
    QQ_MSG_TYPE_MULTICAST   = 0X08,
    QQ_MSG_TYPE_BROADCAST   = 0X10,
} qq_msg_type_t;

typedef struct qq_msg_head_s
{
    uint32  dstid;
    uint32  srcid;
    uint32  type;
    uint32  length;
}qq_msg_head_t;
#define QQ_MSG_HED_LEN          (sizeof(uint32)*4)

typedef struct qq_user_list_s
{
    uint32              usrid;
    int8                usrname[QQ_USER_NAME_LEN];
    int32               sockfd;
    struct list_head    list;
}qq_user_list_t;

extern qq_user_list_t *qq_user_find (uint32 usrid);
extern qq_user_list_t *qq_user_find_skfd (uint32 sockfd);

extern int32 qq_user_reg(qq_user_list_t* user);

extern int32 qq_user_del(uint32 usrid);

extern int32 qq_user_del_skfd(uint32 sockfd);

extern int32 qq_user_init(void);

extern int32 qq_msg_encode(qq_msg_head_t* head, int8* pkt, int8* buf);

extern int32 qq_msg_decode(int8* buf, qq_msg_head_t* head, int8* pkt);
typedef int(* qq_usrlst_foreach_func)(uint32 srcid, uint32 dstid, int8* pkt, uint32 len);
extern int32 qq_user_foreach_send(uint32 srcid, int8* pkt, uint32 len, qq_usrlst_foreach_func func);

#endif