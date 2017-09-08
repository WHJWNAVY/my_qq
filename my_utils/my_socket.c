#include "my_socket.h"

//#define MY_SOCK_ERR -1
//#define MY_SOCK_OK  0

#define MYSOCK_TYPE_TCP     SOCK_STREAM//tcp
#define MYSOCK_TYPE_UDP     SOCK_DGRAM//udp

#define SOCKADDR_IN_LEN     (sizeof(struct sockaddr_in))

#ifdef MYSOCK_DEBUG
#define MYSOCK_DEBUG_ERR(fmt, args...) \
    do{printf("\n######[%s:%d]:"fmt"######\n", __FUNCTION__,__LINE__, ##args);}while(0)
#else
#define MYSOCK_DEBUG_ERR(fmt, arg...)
#endif

#define MYSOCK_CLOSEFD(fd)  do{if(fd>0)close(fd);}while(0)

/* Function Name:
 *      _is_ipv4addr
 * Description:
 *      Check the ip addr string is valid or not.
 * Input:
 *      ipaddr_str  - ip addr string
 * Output:
 *      None
 * Return:
 *      0                   - valid
 *      -1                  - invalid
 * Note:
 *      None
 */
static int _is_ipv4addr(const char *ipaddr_str)
{
    char *ipv4 = (char *)ipaddr_str;
    int ipdot = 0, ipnum = 0;
    if(ipv4 == NULL)
    {
        return -1;
    }
    if((strlen(ipv4) < strlen("0.0.0.0")) || (strlen(ipv4) > strlen("255.255.255.255")))
    {
        return -1;
    }
    while((*ipv4) != '\0')
    {
        switch(*ipv4)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            ipnum = (ipnum * 10) + (*ipv4 - '0');
            if(ipnum > 255)//数字大于255
            {
                return -1;
            }
            ipv4++;
            break;
        }
        case '.':
        {
            ipdot++;
            if(ipdot > 3)//点的个数大于3个
            {
                return -1;
            }
            if(*(ipv4 + 1) == '.') //连续的点
            {
                return -1;
            }
            ipnum = 0;
            ipv4++;
            break;
        }
        default:
        {
            return -1;
        }
        }
    }

    if(ipdot != 3)
    {
        return -1;
    }

    return 0;
}

/* Function Name:
 *      _mysock_int
 * Description:
 *      Create a socket.
 * Input:
 *      addr_t  - ip addr string and port num
 * Output:
 *      None
 * Return:
 *      >  0                 - socket fd
 *      = -1                 - fail
 * Note:
 *      None
 */
static int _mysock_int(mysock_addr_t* addr_t)
{
    int listenfd = 0;
    unsigned short portn;
    char* ipstr;
    int type;
    struct sockaddr_in* addr;
    struct sockaddr_in saddr;

    if(addr_t == NULL)
    {
        MYSOCK_DEBUG_ERR("addr_t == NULL");
        return -1;
    }

    portn   = addr_t->port_num;
    ipstr   = &(addr_t->ipv4_str[0]);
    type    = addr_t->sock_type;
    addr    = &(addr_t->sock_addr);

    if((portn <= 0) || (type < 0))
    {
        MYSOCK_DEBUG_ERR("port[%d], type[%d]", portn, type);
        return -1;
    }

    if(_is_ipv4addr(ipstr) < 0)
    {
        MYSOCK_DEBUG_ERR("check ip string error");
        return -1;
    }

    if((listenfd = socket(MYSOCK_DFT_DOMAIN ,type, 0)) < 0)
    {
        MYSOCK_DEBUG_ERR("Socket error,[%d]", listenfd);
        return -1;
    }

    //MYSOCK_DEBUG_ERR("Socket success,[%d]", listenfd);

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = MYSOCK_DFT_DOMAIN;
    saddr.sin_port = htons(portn);
    saddr.sin_addr.s_addr = inet_addr(ipstr);

    memcpy(addr, &saddr, sizeof(saddr));

    return listenfd;
}

/* Function Name:
 *      _mysock_epoll_add
 * Description:
 *      Add a fd to epoll event.
 * Input:
 *      epfd  - epoll event fd.
 *      fd    - fd to add.
 * Output:
 *      None
 * Return:
 *      =  0                 - ok
 *      = -1                 - fail
 * Note:
 *      None
 */
static int _mysock_epoll_add(int epfd, int fd, unsigned int events)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0)
    {
        MYSOCK_DEBUG_ERR("Epoll add error");
        return -1;
    }
    return 0;
}

/* Function Name:
 *      _mysock_epoll_del
 * Description:
 *      Del a fd from epoll event.
 * Input:
 *      epfd  - epoll event fd.
 *      fd    - fd to del.
 * Output:
 *      None
 * Return:
 *      =  0                 - ok
 *      = -1                 - fail
 * Note:
 *      None
 */
static int _mysock_epoll_del(int epfd, int fd)
{
    if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) < 0)
    {
        MYSOCK_DEBUG_ERR("Epoll del error");
        return -1;
    }
    return 0;
}

/* Function Name:
 *      _mysock_nonblocking_set
 * Description:
 *      set a socket to nonblocking
 * Input:
 *      sockfd  - sockfd.
 * Output:
 *      None
 * Return:
 *      =  0                 - ok
 *      = -1                 - fail
 * Note:
 *      None
 */
static int _mysock_nonblocking_set(int sockfd)
{
    int opts;
    opts = fcntl(sockfd, F_GETFL);
    if(opts < 0)
    {
        MYSOCK_DEBUG_ERR("fcntl(sockfd, F_GETFL)");
        return -1;
    }

    opts = opts|O_NONBLOCK;
    if(fcntl(sockfd, F_SETFL, opts) < 0)
    {
        MYSOCK_DEBUG_ERR("fcntl(sockfd, F_SETFL, opts)");
        return -1;
    }

    return 0;
}

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
int mysock_tcp_sinit(mysock_addr_t* addr_t)
{
    int listenfd;
    addr_t->sock_type = MYSOCK_TYPE_TCP;
    if((listenfd = _mysock_int(addr_t)) < 0)
    {
        goto tcps_err;
    }

    if(bind(listenfd, (struct sockaddr*)&(addr_t->sock_addr), SOCKADDR_IN_LEN) < 0)
    {
        MYSOCK_DEBUG_ERR("Bind error");
        goto tcps_err;
    }

    //MYSOCK_DEBUG_ERR("Bind success");

    if(listen(listenfd , MYSOCK_DFT_BACKLOG) < 0)
    {
        MYSOCK_DEBUG_ERR("Listen error");
        goto tcps_err;
    }

    //MYSOCK_DEBUG_ERR("Listen success");
    return listenfd;

tcps_err:
    MYSOCK_CLOSEFD(listenfd);
    return -1;
}

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
int mysock_tcp_accept(int listenfd)
{
    int connfd;
    /*struct sockaddr_in saddr;
    int slen = sizeof(saddr);*/
    if((connfd = accept(listenfd , /*(struct sockaddr *)(&saddr)*/NULL , /*&slen*/NULL)) < 0)
    {
        MYSOCK_DEBUG_ERR("Accept error, [%d]", connfd);
        return -1;
    }
    //MYSOCK_DEBUG_ERR("Accept success, [%d]", connfd);
    return connfd;
}

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
int mysock_tcp_cinit(mysock_addr_t* addr_t)
{
    int connfd = 0;
    addr_t->sock_type = MYSOCK_TYPE_TCP;
    if((connfd = _mysock_int(addr_t)) < 0)
    {
        goto conn_err;
    }

    if (connect(connfd, (struct sockaddr*)&(addr_t->sock_addr), SOCKADDR_IN_LEN) < 0)
    {
        MYSOCK_DEBUG_ERR("Connect error");
        goto conn_err;
    }

    return connfd;

conn_err:
    MYSOCK_CLOSEFD(connfd);
    return -1;
}

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
int mysock_udp_sinit(mysock_addr_t* addr_t)
{
    int udpsfd = 0;
    addr_t->sock_type = MYSOCK_TYPE_UDP;
    if((udpsfd = _mysock_int(addr_t)) < 0)
    {
        goto udps_err;
    }

    if (bind(udpsfd, (struct sockaddr*)&(addr_t->sock_addr), SOCKADDR_IN_LEN) < 0)
    {
        MYSOCK_DEBUG_ERR("Bind error");
        goto udps_err;
    }
    //MYSOCK_DEBUG_ERR("Bind success");

    return udpsfd;

udps_err:
    MYSOCK_CLOSEFD(udpsfd);
    return -1;
}

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
int mysock_udp_cinit(mysock_addr_t* addr_t)
{
    int udpcfd = 0;
    addr_t->sock_type = MYSOCK_TYPE_UDP;
    if((udpcfd = _mysock_int(addr_t)) < 0)
    {
        return -1;
    }

    return udpcfd;
}

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
int mysock_print_pkts(char* pkt, int len, int is_ascii)
{
    int n = 0, l = 0, w = 0;
    char* fmt = NULL;
    fmt = (is_ascii) ? "%c" : "0x%02X, ";
    w = (is_ascii) ? 80 : 16;
    
    printf("\n");
    for(n=0; n<len; n++)
    {
        printf(fmt, (unsigned char)pkt[n]);
        if((l++) > w)
        {
            printf("\n");
            l = 0;
        }
    }
    printf("\n");
    return 0;
}

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
int mysock_write_pkts(int fd, void* buff, int len)
{
    int bytes_left;
    int written_bytes;
    char *ptr;

    if((fd < 0) || (buff == NULL) || (len <= 0))
    {
        return -1;
    }

    ptr = buff;
    bytes_left = len;

    while(bytes_left > 0)
    {
        written_bytes = write(fd, ptr, bytes_left);
        if(written_bytes <= 0)
        {
            /*if(errno == EINTR)
            {
                written_bytes = 0;
            }
            else*/
            {
                return -1;
            }
        }
        bytes_left -= written_bytes;
        ptr += written_bytes;
    }

    return 0;
}

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
int mysock_read_pkts(int fd, void* buff, int len)
{
    int bytes_left;
    int bytes_read;
    char *ptr;

    if((fd < 0) || (buff == NULL) || (len <= 0))
    {
        return -1;
    }

    ptr = buff;
    bytes_left = len;

    while(bytes_left > 0)
    {
        bytes_read = read(fd, ptr, bytes_left);
        if(bytes_read < 0)
        {
            if(errno == EINTR)
            {
                bytes_read = 0;
            }
            else
            {
                return -1;
            }
        }
        else if(bytes_read == 0)
        {
            break;
        }
        bytes_left -= bytes_read;
        ptr += bytes_read;
    }
    return (len - bytes_left);
}

static int MySockListenFd = 0;
static int MySockEpollFd = 0;
static void _mysock_epoll_exit(int no)
{
    MYSOCK_DEBUG_ERR("signal from [%d]", no);
    MYSOCK_CLOSEFD(MySockListenFd);
    MYSOCK_CLOSEFD(MySockEpollFd);
    MYSOCK_DEBUG_ERR("close listenfd[%d]-epollfd[%d], exit(0)", 
        MySockListenFd, MySockEpollFd);
    exit(0);
}

static int _mysock_epoll_regsig_exit(int listenfd, int epollfd)
{
    MySockListenFd = listenfd;
    MySockEpollFd = epollfd;
    signal(SIGINT, _mysock_epoll_exit);
    signal(SIGQUIT, _mysock_epoll_exit);
    signal(SIGTERM, _mysock_epoll_exit);
    return 0;
}

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
int my_sock_tcp_epolls
(
    mysock_addr_t* addr_t, 
    mysock_recv_handle_func stdin_f, mysock_buff_t* stdin_b,
    mysock_recv_handle_func recv_f,  mysock_buff_t* recv_b
)
{
    int listenfd = 0, conn_sock = 0, epollfd = 0;
    int nfds = 0, n = 0, eventfd, recv_len;
    struct epoll_event events[MYSOCK_DFT_MAX_EVENTS];

    /* Code to set up listening socket, 'listen_sock',
       (socket(), bind(), listen()) omitted */
    if((listenfd = mysock_tcp_sinit(addr_t)) < 0)
    {
        goto epoll_err;
    }

    MYSOCK_DEBUG_ERR("create socket success, [%d]", listenfd);

    epollfd = epoll_create(MYSOCK_DFT_MAX_EVENTS);
    if (epollfd < 0)
    {
        MYSOCK_DEBUG_ERR("epoll_create error, [%d]", epollfd);
        goto epoll_err;
    }

    MYSOCK_DEBUG_ERR("create epoll success, [%d]", epollfd);

    _mysock_epoll_regsig_exit(listenfd, epollfd);

    _mysock_epoll_add(epollfd, listenfd, EPOLLIN);

    if((stdin_f != NULL) && (stdin_b != NULL))
    {
        _mysock_epoll_add(epollfd, STDIN_FILENO, EPOLLIN);
    }

    for (;;)
    {
        nfds = epoll_wait(epollfd, events, MYSOCK_DFT_MAX_EVENTS, -1);
        if (nfds < 0)
        {
            MYSOCK_DEBUG_ERR("epoll_wait error");
            goto epoll_err;
        }
        else if(nfds == 0)
        {
            MYSOCK_DEBUG_ERR("epoll_wait timeout");
            continue;
        }
        else
        {
            for (n = 0; n < nfds; ++n)
            {
                if(events[n].events & EPOLLIN)
                {
                    eventfd = events[n].data.fd;
                    if(eventfd == listenfd)
                    {
                        conn_sock = mysock_tcp_accept(listenfd);
                        if (conn_sock < 0)
                        {
                            MYSOCK_DEBUG_ERR("epoll accept error, [%d]", conn_sock);
                            //goto epoll_err;
                            continue;
                        }

                        _mysock_epoll_add(epollfd, conn_sock, EPOLLIN/*|EPOLLOUT*/);
                    }
                    else if(eventfd == STDIN_FILENO)
                    {
                        if((stdin_f != NULL) && (stdin_b != NULL))
                        {
                            if(stdin_f(eventfd, stdin_b) < 0)
                            {
                                goto epoll_err;
                            }
                        }
                    }
                    else
                    {
                        recv_len = recv_f(eventfd, recv_b);
                        if(recv_len < 0)
                        {
                            _mysock_epoll_del(epollfd, eventfd);
                            MYSOCK_CLOSEFD(eventfd);
                            MYSOCK_DEBUG_ERR("Recv client[%d] error", eventfd);
                            goto epoll_err;
                        }
                        else if(recv_len == 0)//closed
                        {
                            _mysock_epoll_del(epollfd, eventfd);
                            MYSOCK_CLOSEFD(eventfd);
                            MYSOCK_DEBUG_ERR("Client[%d] is closed", eventfd);
                        }
                        /*else
                        {
                        }*/
                    }
                }
                /*else if(events[n].events & EPOLLOUT)
                {
                }*/
            }
        }
    }

    return 0;

epoll_err:
    MYSOCK_CLOSEFD(epollfd);
    MYSOCK_CLOSEFD(listenfd);
    return -1;
}
