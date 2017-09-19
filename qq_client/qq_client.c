/*************************************************************************
	> File Name: test_client.c
	> Author: wnavy
	> Mail: whjwnavy@163.com 
	> Created Time: Fri 01 Sep 2017 03:33:21 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_socket.h"
#include "qq_msg.h"
#include <time.h>

uint32 get_src_id(void)
{
    srand(time(0));
    return (uint32)(0x0000ffff + rand()%(0xfffffff0-0x0000ffff+1));
}

int main(int argc, char* argv[])
{
    char ipaddr_str[16] = {0};
    int port_num = 0, i = 0;
    mysock_addr_t addr = {0};

    qq_msg_head_t head = {0};
    char msg_buff[QQ_MSG_BUFFS_LEN] = {0};
    char msg_pkt[QQ_MSG_PKTS_LEN] = {0};
    char msg_rbuff[QQ_MSG_BUFFS_LEN] = {0};
    int client_fd = 0, recv_len = 0;
    
    char uname[QQ_USER_NAME_LEN] = {0};
    char* send_str = NULL;

    if(argc >= 3)
    {
        strcpy(ipaddr_str, argv[1]);
        sscanf(argv[2], "%d", &port_num);
        if(argc == 4)
        {
            send_str = argv[3];
        }
    }
    else
    {
        strcpy(ipaddr_str, "127.0.0.1");
        port_num = 1024;

        if(argc > 1)
        {
            send_str = argv[1];
        }
        else
        {

            send_str = "Hello World!";
        }
    }

    MYSOCK_FILL_ADDR_T(addr, port_num, ipaddr_str);

    memset(msg_pkt, 0, QQ_MSG_PKTS_LEN);
    memcpy(msg_pkt, send_str, strlen(send_str));

    client_fd = mysock_tcp_cinit(&addr);
    if(client_fd  < 0)
    {
        printf("client init error\n");
        goto client_err;
    }

    head.dstid = 0;
    head.srcid = get_src_id();
    head.type = QQ_MSG_TYPE_LOGIN;
    sprintf(uname, "usr_%010d", head.srcid);
    head.length = strlen(uname);
    qq_msg_encode(&head, uname, msg_buff);

    recv_len = send(client_fd, msg_buff, QQ_MSG_BUFFS_LEN, 0);
    if(recv_len <= 0)
    {
        printf("client[%d] send error\n", client_fd);
        close(client_fd);
        goto client_err;
    }

    head.type = QQ_MSG_TYPE_MULTICAST;
    head.length = strlen(msg_pkt);
    qq_msg_encode(&head, msg_pkt, msg_buff);

    //for(aa = 0; aa < 3; aa++)
    for( ; ; )
    {
        recv_len = send(client_fd, msg_buff, QQ_MSG_BUFFS_LEN, 0);
        if(recv_len <= 0)
        {
            printf("client[%d] send error\n", client_fd);
            //close(client_fd);
            //goto client_err;
        }

        memset(&head, 0, QQ_MSG_HED_LEN);
        memset(msg_pkt, 0, QQ_MSG_PKTS_LEN);
        memset(msg_rbuff, 0, QQ_MSG_BUFFS_LEN);

        recv_len = recv(client_fd, msg_rbuff, QQ_MSG_BUFFS_LEN, 0);
        if(recv_len <= 0)
        {
            printf("client[%d] recv error\n", client_fd);
            //close(client_fd);
            //goto client_err;
        }

        qq_msg_decode(msg_rbuff, &head, msg_pkt);
        printf("msg from %08x:", head.srcid);
        mysock_print_pkts(msg_pkt, strlen(msg_pkt), 1);
        usleep(90000);
       
    }

    close(client_fd);
client_err:
    return 0;
}
