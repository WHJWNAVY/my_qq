#ifndef __MYSOCK_H__
#define __MYSOCK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define MYSOCK_DEBUG 1

#define MYSOCK_DFT_DOMAIN       AF_INET//ipv4
//#define MYSOCK_DFT_DOMAIN     AF_INET6//ipv6
#define MYSOCK_DFT_BACKLOG      100//listen backlog
#define MYSOCK_DFT_MAX_EVENTS   100

#define MYSOCK_FILL_ADDR_T(addr,port,ipstr) \
do                                          \
{                                           \
    addr.port_num = port;                   \
    strcpy(addr.ipv4_str, ipstr);           \
}while(0)

#define MYSOCK_FILL_BUFF_T(buff,b,l)        \
do                                          \
{                                           \
    buff.buff = b;                          \
    buff.len = l;                           \
}while(0)

typedef struct mysock_addr_s
{
    /* Fill it by user before use it!!! */
    char            ipv4_str[16];
    unsigned short  port_num;

    /* Don't need to fill it by user!!! */
    int             sock_type;
    struct sockaddr_in  sock_addr;
} mysock_addr_t;

typedef struct mysock_buff_s
{
    char*   buff;
    long    len;
}mysock_buff_t;

/* Callback function Type:
 *      mysock_fdhandle_func
 * Description:
 *      Callback function of recv deal.
 * Input:
 *      sock_fd  - recv socket fd
 *      buff     - recv buff
 * Output:
 *      None
 * Return:
 *      >  0                 - ok
 *      =  0                 - socket closed
 *      = -1                 - fail
 * Note:
 *      None
 */
typedef int(* mysock_recv_handle_func)(int sock_fd, mysock_buff_t* buff);

/* Function Name:
 *      mysock_tcp_sinit
 * Description:
 *      Init a tcp server.
 * Input:
 *      addr_t  - ip addr string and port num
 * Output:
 *      None
 * Return:
 *      >  0                 - server fd
 *      = -1                 - fail
 * Note:
 *      None
 */
extern int mysock_tcp_sinit(mysock_addr_t* addr_t);

/* Function Name:
 *      mysock_tcp_accept
 * Description:
 *      Accept a tcp client.
 * Input:
 *      listenfd  - socket fd
 * Output:
 *      None
 * Return:
 *      >  0                 - client fd
 *      = -1                 - fail
 * Note:
 *      None
 */
extern int mysock_tcp_accept(int listenfd);

/* Function Name:
 *      mysock_tcp_cinit
 * Description:
 *      Init a tcp client.
 * Input:
 *      addr_t  - ip addr string and port num
 * Output:
 *      None
 * Return:
 *      >  0                 - client fd
 *      = -1                 - fail
 * Note:
 *      None
 */
extern int mysock_tcp_cinit(mysock_addr_t* addr_t);

/* Function Name:
 *      mysock_udp_sinit
 * Description:
 *      Init a udp server.
 * Input:
 *      addr_t  - ip addr string and port num
 * Output:
 *      None
 * Return:
 *      >  0                 - server fd
 *      = -1                 - fail
 * Note:
 *      None
 */
extern int mysock_udp_sinit(mysock_addr_t* addr_t);

/* Function Name:
 *      mysock_udp_cinit
 * Description:
 *      Init a udp client.
 * Input:
 *      addr_t  - ip addr string and port num
 * Output:
 *      None
 * Return:
 *      >  0                 - client fd
 *      = -1                 - fail
 * Note:
 *      None
 */
extern int mysock_udp_cinit(mysock_addr_t* addr_t);

/* Function Name:
 *      mysock_print_pkts
 * Description:
 *      print packet.
 * Input:
 *      pkt       - point to packet
 *      len       - packet length
 *      is_ascii  - print with ascii mode(1) or not(0)
 * Output:
 *      None
 * Return:
 *      =  0                 - ok
 * Note:
 *      None
 */
extern int mysock_print_pkts(char* pkt, int len, int is_ascii);

/* Function Name:
 *      mysock_write_pkts
 * Description:
 *      write packet to socket fd.
 * Input:
 *      fd         - socket to write
 *      buff       - point to packet buffer
 *      len        - packet length
 * Output:
 *      None
 * Return:
 *      =  0                 - ok
 *      =  -1                - error
 * Note:
 *      None
 */
extern int mysock_write_pkts(int fd, void* buff, int len);

/* Function Name:
 *      mysock_read_pkts
 * Description:
 *      read packet from socket fd.
 * Input:
 *      fd         - socket to read
 *      buff       - point to packet buffer
 *      len        - packet length
 * Output:
 *      None
 * Return:
 *      >  0                 - read bytes
 *      =  0                 - fd closed
 *      =  -1                - error
 * Note:
 *      None
 */
extern int mysock_read_pkts(int fd, void* buff, int len);

/* Function Name:
 *      my_sock_tcp_epolls
 * Description:
 *      create a tcp  epoll sever
 * Input:
 *      addr_t         - ip addr string and port num
 *      stdin_f        - stdin in callback function
 *      stdin_b        - stdin recv buffer
 *      recv_f         - recv in callback function
 *      recv_b         - recv buffer
 * Output:
 *      None
 * Return:
 *      =  0                 - ok
 *      =  -1                - error
 * Note:
 *      forver loop, no return.
 */
extern int my_sock_tcp_epolls
(
    mysock_addr_t* addr_t, 
    mysock_recv_handle_func stdin_f, mysock_buff_t* stdin_b,
    mysock_recv_handle_func recv_f,  mysock_buff_t* recv_b
);

#endif