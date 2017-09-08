/*************************************************************************
	> File Name: test_server.c
	> Author: wnavy
	> Mail: whjwnavy@163.com 
	> Created Time: Fri 01 Sep 2017 03:33:09 PM CST
 ************************************************************************/

#include<stdio.h>
#include "my_socket.h"

int server_recv_func(int fd, mysock_buff_t* buff)
{
    int recv_len = 0;
    memset(buff->buff, 0, buff->len);
    recv_len = recv(fd, buff->buff, buff->len, 0/*MSG_WAITALL*/);
    //recv_len = mysock_read_pkts(fd, buff->buff, buff->len);
    if(recv_len  < 0)
    {
        printf("recv from [%d] error\n", fd);
        return -1;
    }
    else if(recv_len == 0)
    {
        //printf("client[%d] is closed\n", fd);
        return 0;
    }
    else
    {
        printf("recv [%d] bytes from [%d]\n", recv_len, fd);
        //mysock_print_pkts(buff->buff, recv_len, 0);
        
        if(send(fd, buff->buff, recv_len, 0) <= 0)
        //if(mysock_write_pkts(fd, buff->buff, recv_len) < 0)
        {
            printf("send to [%d] error\n", fd);
            return -1;
        }
    }
    return recv_len;
}

int main(int argc, char* argv[])
{
    char ipaddr_str[16] = {0};
    int port_num = 0;
    mysock_addr_t addr = {0};
    mysock_buff_t buff = {0};
    char recv_buff[1024] = {0};

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

    MYSOCK_FILL_BUFF_T(buff, recv_buff, sizeof(recv_buff));
    MYSOCK_FILL_ADDR_T(addr, port_num, ipaddr_str);

    my_sock_tcp_epolls(&addr, NULL, NULL, server_recv_func, &buff);
    return 0;
}

