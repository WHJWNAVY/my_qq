/*************************************************************************
	> File Name: test_client.c
	> Author: wnavy
	> Mail: whjwnavy@163.com 
	> Created Time: Fri 01 Sep 2017 03:33:21 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "my_socket.h"

int main(int argc, char* argv[])
{
    char ipaddr_str[16] = {0};
    int port_num = 0, i = 0;
    mysock_addr_t addr = {0};
    char send_buff[1024] = {0};
    char recv_buff[1024] = {0};
    int client_fd = 0, recv_len = 0;

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

    MYSOCK_FILL_ADDR_T(addr, port_num, ipaddr_str);

    memset(send_buff, '\0', 1024);
    char aa = 'A';
    for(i=0; i<100; i++)
    {
        send_buff[i] = aa++;
        if(aa > 'Z')
        {
            aa = 'A';
        }
    }
    send_buff[i] = '\0';

    //for(aa = 0; aa < 3; aa++)
    for( ; ; )
    {
        client_fd = mysock_tcp_cinit(&addr);
        if(client_fd  < 0)
        {
            printf("client init error\n");
            goto client_err;
        }

        for(i=0; i<3; i++)
        {
            recv_len = send(client_fd, send_buff, strlen(send_buff), 0);
            if(recv_len <= 0)
            {
                printf("client[%d] send error\n", client_fd);
                close(client_fd);
                goto client_err;
            }
            memset(recv_buff, '\0', 1024);
            recv_len = recv(client_fd, recv_buff, sizeof(recv_buff), 0);
            if(recv_len <= 0)
            {
                printf("client[%d] recv error\n", client_fd);
                close(client_fd);
                goto client_err;
            }
            printf("recv [%d] bytes from [%d]\n", recv_len, client_fd);
            mysock_print_pkts(recv_buff, recv_len, 1);
            usleep(10*1000);
        }

        close(client_fd);
    }

    return 0;
client_err:
    return -1;
}
