/*************************************************************************
	> File Name: test_server.c
	> Author: wnavy
	> Mail: whjwnavy@163.com 
	> Created Time: Fri 01 Sep 2017 03:33:09 PM CST
 ************************************************************************/

#include <stdio.h>
#include "my_socket.h"
#include "qq_msg.h"

int32 qq_msg_send(uint32 srcid, uint32 dstid, int8* pkt, uint32 len)
{
    qq_msg_head_t head;
    qq_user_list_t* tousr;
    char qq_buff[QQ_MSG_BUFFS_LEN] = {0};

    tousr = qq_user_find(dstid);
    ARG_CHK_EQ(tousr, NULL, ERROR);

    head.dstid = dstid;
    head.srcid = srcid;
    head.type = QQ_MSG_TYPE_UNICAST;
    head.length = len;
    ARG_CHK_EQ(qq_msg_encode(&head, pkt, qq_buff), ERROR, ERROR);

    if(send(tousr->sockfd, qq_buff, QQ_MSG_BUFFS_LEN, 0) <= 0)
    {
        DEBUG_LOG("send to [%s:%08X:%08X] error\n", tousr->usrname, tousr->sockfd, head.dstid);
        return ERROR;
    }

    return OK;
}



int32 qq_msg_deal(int fd, qq_msg_head_t* head, int8* pkt)
{
    qq_user_list_t user;

    user.sockfd = fd;
    user.usrid = head->srcid;
    strncpy(user.usrname, pkt, QQ_USER_NAME_LEN);

    switch (head->type)
    {
    case QQ_MSG_TYPE_LOGIN:
        DEBUG_LOG("User Login [%s:%08X]", user.usrname, user.usrid);
        ARG_CHK_NEQ(qq_user_reg(&user), OK, ERROR);
        break;
    case QQ_MSG_TYPE_LOGOUT:
        DEBUG_LOG("User Logout [%s:%08X]", user.usrname, user.usrid);
        ARG_CHK_NEQ(qq_user_del(user.usrid), OK, ERROR);
        break;
    case QQ_MSG_TYPE_UNICAST:
        DEBUG_LOG("User Send Unicast [%s:%08X]", user.usrname, user.usrid);
        /*ARG_CHK_NEQ(*/qq_msg_send(head->srcid, head->dstid, pkt, head->length)/*,OK,ERROR)*/;
        break;
    case QQ_MSG_TYPE_MULTICAST:
    case QQ_MSG_TYPE_BROADCAST:
        DEBUG_LOG("User Send Broadcast [%s:%08X]", user.usrname, user.usrid);
        qq_user_foreach_send(head->srcid, pkt, head->length, qq_msg_send);
        break;
     default:
        break;
    }
    return OK;
}

int server_recv_func(int fd, mysock_buff_t* buff)
{
    int recv_len = 0;
    qq_msg_head_t qq_head = {0};
    char qq_pkt[QQ_MSG_PKTS_LEN] = {0};
    memset(buff->buff, 0, buff->len);
    recv_len = recv(fd, buff->buff, buff->len, 0/*MSG_WAITALL*/);
    //recv_len = mysock_read_pkts(fd, buff->buff, buff->len);
    if(recv_len  < 0)
    {
        DEBUG_LOG("recv from [%d] error\n", fd);
        qq_user_del_skfd(fd);
        return -1;
    }
    else if(recv_len == 0)
    {
        //DEBUG_LOG("client[%d] is closed\n", fd);
        qq_user_del_skfd(fd);
        return 0;
    }
    else
    {
        //DEBUG_LOG("recv [%d] bytes from [%d]\n", recv_len, fd);
        //mysock_print_pkts(buff->buff, recv_len, 0);
        #if 0
        if(send(fd, buff->buff, recv_len, 0) <= 0)
        //if(mysock_write_pkts(fd, buff->buff, recv_len) < 0)
        {
            DEBUG_LOG("send to [%d] error\n", fd);
            return -1;
        }
        #endif
        /*ARG_CHK_NEQ(*/qq_msg_decode(buff->buff, &qq_head, qq_pkt)/*, OK, ERROR)*/;
        mysock_print_pkts(qq_pkt, strlen(qq_pkt), 1);
        /*ARG_CHK_NEQ(*/qq_msg_deal(fd, &qq_head, qq_pkt)/*, OK, ERROR)*/;
    }
    return recv_len;
}

int main(int argc, char* argv[])
{
    char ipaddr_str[16] = {0};
    int port_num = 0;
    mysock_addr_t addr = {0};
    mysock_buff_t buff = {0};
    char recv_buff[QQ_MSG_BUFFS_LEN] = {0};

    if(argc == 3)
    {
        strcpy(ipaddr_str, argv[1]);
        sscanf(argv[2], "%d", &port_num);
    }
    else
    {
        strcpy(ipaddr_str, "127.0.0.1");
        port_num = 1024;
    }

    qq_user_init();

    MYSOCK_FILL_BUFF_T(buff, recv_buff, sizeof(recv_buff));
    MYSOCK_FILL_ADDR_T(addr, port_num, ipaddr_str);

    my_sock_tcp_epolls(&addr, NULL, NULL, server_recv_func, &buff);
    return 0;
}

