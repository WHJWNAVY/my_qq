/*************************************************************************
	> File Name: qq_msg.c
	> Author: wnavy
	> Mail: whjwnavy@163.com 
	> Created Time: Fri 15 Sep 2017 05:27:57 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qq_msg.h"

static qq_user_list_t qq_user_list;

static int32 __qq_user_init(qq_user_list_t * head)
{
    ARG_CHK_EQ(head, NULL, ERROR);
    INIT_LIST_HEAD(&(head->list));
    return OK;
}

static int32 __qq_user_add(qq_user_list_t* head, qq_user_list_t* user)
{
    ARG_CHK_EQ(head, NULL, ERROR);
    ARG_CHK_EQ(user, NULL, ERROR);
    list_add(&(user->list), &(head->list));
    return OK;
}

static int32 __qq_user_add_prev(qq_user_list_t* head, qq_user_list_t* user)
{
    ARG_CHK_EQ(head, NULL, ERROR);
    ARG_CHK_EQ(user, NULL, ERROR);
    list_add_tail(&(user->list), &(head->list));
    return OK;
}

static int32 __qq_user_del(qq_user_list_t* user)
{
    ARG_CHK_EQ(user, NULL, ERROR);
    list_del(&(user->list));
    return OK;
}
static int32 __qq_user_reg(qq_user_list_t* head, qq_user_list_t* user)
{
    qq_user_list_t* pos;
    int32 ret = 0;
    ARG_CHK_EQ(head, NULL, ERROR);
    ARG_CHK_EQ(user, NULL, ERROR);

    if(list_empty(&(head->list)))//链表为空
    {
        DEBUG_LOG("List is empty!\r\n");
        return(__qq_user_add(head, user));
    }
    else
    {
        list_for_each_entry(pos, &(head->list), list)
        {
            ret = (user->usrid - pos->usrid);
            if(ret == 0)
            {
                DEBUG_ERR(ERROR, "User:%s already exist!\r\n", user->usrname);
                return ERROR;//用户已经存在
            }
            else if(ret > 0)// 加到最后
            {
                if(list_is_last(&(pos->list), &(head->list)))
                {
                    return(__qq_user_add(pos, user));
                }
                else
                {
                    continue;
                }
            }
            else// 加到最前
            {
                return(__qq_user_add_prev(pos, user));
            }
        }
    }
}

static qq_user_list_t* __qq_user_find_byid(qq_user_list_t* head, uint32 usrid)
{
    qq_user_list_t* pos;
    ARG_CHK_EQ(head, NULL, NULL);
    ARG_CHK_LEQ(usrid, 0, NULL);
    list_for_each_entry(pos, &(head->list), list)
    {
        ARG_CHK_EQ(pos->usrid, usrid, pos);
    }
    return NULL;
}

static qq_user_list_t* __qq_user_find_byskfd(qq_user_list_t* head, uint32 sockfd)
{
    qq_user_list_t* pos;
    ARG_CHK_EQ(head, NULL, NULL);
    ARG_CHK_LEQ(sockfd, 0, NULL);
    list_for_each_entry(pos, &(head->list), list)
    {
        ARG_CHK_EQ(pos->usrid, sockfd, pos);
    }
    return NULL;
}

int32 qq_user_reg(qq_user_list_t* user)
{
    #ifndef QQ_USRLST_USE_MALLOC
    return __qq_user_reg(&qq_user_list, user);
    #else
    qq_user_list_t* user_t = NULL;
    user_t = malloc(sizeof(qq_user_list_t));
    if(user_t != NULL)
    {
        memcpy(user_t, user, sizeof(qq_user_list_t));
        if(__qq_user_reg(&qq_user_list, user_t) != OK)
        {
            free(user_t);
            return ERROR;
        }
        return OK;
    }
    else
    {
        return ERROR;
    }
    #endif
}

qq_user_list_t *qq_user_find (uint32 usrid)
{
    return __qq_user_find_byid(&qq_user_list, usrid);
}

qq_user_list_t *qq_user_find_skfd (uint32 sockfd)
{
    return __qq_user_find_byskfd(&qq_user_list, sockfd);
}

int32 qq_user_del(uint32 usrid)
{
    #ifndef QQ_USRLST_USE_MALLOC
    qq_user_list_t * user = NULL;
    user = qq_user_find(usrid);
    if(user != NULL)
    {
        return __qq_user_del(user);
    }
    else
    {
        return ERROR;
    }
    #else
    qq_user_list_t * user = NULL;
    user = qq_user_find(usrid);
    if(user != NULL)
    {
        __qq_user_del(user);
        free(user);
        return OK;
    }
    else
    {
        return ERROR;
    }
    #endif
}

int32 qq_user_del_skfd(uint32 sockfd)
{
    #ifndef QQ_USRLST_USE_MALLOC
    qq_user_list_t * user = NULL;
    user = qq_user_find_skfd(sockfd);
    return __qq_user_del(user);
    #else
    qq_user_list_t * user = NULL;
    user = qq_user_find_skfd(sockfd);
    if(user != NULL)
    {
        __qq_user_del(user);
        free(user);
        return OK;
    }
    else
    {
        return ERROR;
    }
    #endif
}

int32 qq_user_foreach_send(uint32 srcid, int8* pkt, uint32 len, qq_usrlst_foreach_func func)
{
    qq_user_list_t* pos;
    ARG_CHK_LEQ(srcid, 0, ERROR);
    ARG_CHK_LEQ(len, 0, ERROR);
    ARG_CHK_EQ(pkt, NULL, ERROR);
    ARG_CHK_EQ(func, NULL, ERROR);
    list_for_each_entry(pos, &(qq_user_list.list), list)
    {
        if(pos->usrid != srcid)
        {
            func(srcid, pos->usrid, pkt, len);
        }
    }
    return OK;
}

int32 qq_user_init(void)
{
    __qq_user_init(&qq_user_list);//初始化用户列表
    return OK;
}

static int32 __msg_encode(uint8* buf, uint32 len)
{
    uint8* buff = buf;
    uint32 i = 0;
    int32 m = 0;
    for(i=0; i<len; i++)
    {
        m = buff[i] + QQ_MSG_ENCODE_LEN;
        if(m > 255)
        {
            m -= 255;
        }
        buff[i] = m;
    }
    return OK;
}

static int32 __msg_decode(uint8* buf, uint32 len)
{
    uint8* buff = buf;
    uint32 i = 0;
    int32 m = 0;
    for(i=0; i<len; i++)
    {
        m = buff[i] - QQ_MSG_ENCODE_LEN;
        if(m <= 0)
        {
            m = (255 + m);
        }

        buff[i] = m;
    }
    return OK;
}

int32 qq_msg_encode(qq_msg_head_t* head, int8* pkt, int8* buf)
{
    int32 ret = 0;
    uint8* buff = (uint8*)buf;
    ARG_CHK_EQ(head, NULL, ERROR);
    ARG_CHK_EQ(pkt, NULL, ERROR);
    ARG_CHK_EQ(buff, NULL, ERROR);

    ARG_CHK_LT(head->dstid, 0, ERROR);
    ARG_CHK_LT(head->srcid, 0, ERROR);
    ARG_CHK_LT(head->type, 0, ERROR);
    ARG_CHK_LT(head->length, 0, ERROR);

    memset(buff, 0, QQ_MSG_BUFFS_LEN);
    
    buff += ret;
    ret = sprintf(buff, "%s%s", QQ_MSG_FLAG, QQ_MSG_SPRT);
    ARG_CHK_LEQ(ret, 0, ERROR);

    buff += ret;
    ret = sprintf(buff, "%08X%s", head->dstid, QQ_MSG_SPRT);
    ARG_CHK_LEQ(ret, 0, ERROR);
    
    buff += ret;
    ret = sprintf(buff, "%08X%s", head->srcid, QQ_MSG_SPRT);
    ARG_CHK_LEQ(ret, 0, ERROR);
    
    buff += ret;
    ret = sprintf(buff, "%08X%s", head->type, QQ_MSG_SPRT);
    ARG_CHK_LEQ(ret, 0, ERROR);
    
    buff += ret;
    ret = sprintf(buff, "%08X%s", head->length, QQ_MSG_SPRT);
    ARG_CHK_LEQ(ret, 0, ERROR);

    buff += ret;
    memcpy(buff, pkt, /*QQ_MSG_PKTS_LEN*/head->length);
    
    #ifdef QQ_MSG_USE_ENCODE
    __msg_encode(buf, QQ_MSG_BUFFS_LEN);
    #endif

    //DEBUG_LOG("QQ_MSG[%s]", buf);
    return OK;
}

int32 qq_msg_decode(int8* buf, qq_msg_head_t* head, int8* pkt)
{
    int32 ret = 0;
    uint8* buff = (uint8*)buf;
    //int8 buff[QQ_MSG_BUFFS_LEN] = {0};
    ARG_CHK_EQ(head, NULL, ERROR);
    ARG_CHK_EQ(pkt, NULL, ERROR);
    ARG_CHK_EQ(buff, NULL, ERROR);

    memset(head, 0, QQ_MSG_HED_LEN);
    memset(pkt, 0, QQ_MSG_PKTS_LEN);
    //memcpy(buff, buf, QQ_MSG_BUFFS_LEN);

    #ifdef QQ_MSG_USE_ENCODE
    __msg_decode(buff, QQ_MSG_BUFFS_LEN);
    #endif

    // check header flag
    ARG_CHK_NEQ(memcmp(buff, QQ_MSG_FLAG, QQ_MSG_FLAG_LEN), 0, ERROR);

    buff += (QQ_MSG_FLAG_LEN + QQ_MSG_SPRT_LEN);
    //buff[QQ_MSG_HEDMBR_LEN] = '\0';
    ARG_CHK_NEQ(memcmp(buff+QQ_MSG_HEDMBR_LEN, QQ_MSG_SPRT, QQ_MSG_SPRT_LEN), 0, ERROR);
    ret = sscanf(buff, "%08X"QQ_MSG_SPRT, &(head->dstid));
    ARG_CHK_LEQ(ret, 0, ERROR);
    ARG_CHK_LT(head->dstid, 0, ERROR);
    
    buff += (QQ_MSG_HEDMBR_LEN + QQ_MSG_SPRT_LEN);
    //buff[QQ_MSG_HEDMBR_LEN] = '\0';
    ARG_CHK_NEQ(memcmp(buff+QQ_MSG_HEDMBR_LEN, QQ_MSG_SPRT, QQ_MSG_SPRT_LEN), 0, ERROR);
    ret = sscanf(buff, "%08X"QQ_MSG_SPRT, &(head->srcid));
    ARG_CHK_LEQ(ret, 0, ERROR);
    ARG_CHK_LT(head->srcid, 0, ERROR);
    
    buff += (QQ_MSG_HEDMBR_LEN + QQ_MSG_SPRT_LEN);
    //buff[QQ_MSG_HEDMBR_LEN] = '\0';
    ARG_CHK_NEQ(memcmp(buff+QQ_MSG_HEDMBR_LEN, QQ_MSG_SPRT, QQ_MSG_SPRT_LEN), 0, ERROR);
    ret = sscanf(buff, "%08X"QQ_MSG_SPRT, &(head->type));
    ARG_CHK_LEQ(ret, 0, ERROR);
    ARG_CHK_LT(head->type, 0, ERROR);
    
    buff += (QQ_MSG_HEDMBR_LEN + QQ_MSG_SPRT_LEN);
    //buff[QQ_MSG_HEDMBR_LEN] = '\0';
    ARG_CHK_NEQ(memcmp(buff+QQ_MSG_HEDMBR_LEN, QQ_MSG_SPRT, QQ_MSG_SPRT_LEN), 0, ERROR);
    ret = sscanf(buff, "%08X"QQ_MSG_SPRT, &(head->length));
    ARG_CHK_LEQ(ret, 0, ERROR);
    ARG_CHK_LT(head->length, 0, ERROR);

    buff += (QQ_MSG_HEDMBR_LEN + QQ_MSG_SPRT_LEN);
    memcpy(pkt, buff, /*QQ_MSG_PKTS_LEN*/head->length);
    //pkt = buff;

    //DEBUG_LOG("QQ_MSG[%s]", buf);

    return OK;
}