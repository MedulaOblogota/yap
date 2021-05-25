//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define TRUE   1
#define FALSE  0

static int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int IsEnoughArgc(int argc, int max_args);

struct sockaddr_in EstablishTCPConnection(int tcp_port,int *);

struct sockaddr_in EstablishUDPConnection(int tcp_port,int *);

struct sockaddr_in EstablishBroadcastConnection(int tcp_port,int *);

int main(int argc , char *argv[])
{
    int opt = TRUE;
    int tcp_master_socket , addrlen , new_socket , client_socket[30] ,
          max_clients = 30 , activity, i , valread , sd, udp_socket, broadcast_socket;
    int max_sd;
    struct sockaddr_in tcp_address, udp_address, broadcast_addr;
    socklen_t len;
    ssize_t n;

    char buffer[1025];  //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;

    //a message
    char *message = "pong\n";

    int tcp_port = 0;
    int udp_port = 0;
    int broadcast_port = 0;

    if (!IsEnoughArgc(argc, 4))
    {
        printf("please input tcp-port, udp-port & broadcast-port after executable!\n");
        exit(0);
    }

    tcp_port = atoi(argv[1]);
    udp_port = atoi(argv[2]);
    broadcast_port = atoi(argv[3]);
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    //create a TCP master socket
    tcp_address = EstablishTCPConnection(tcp_port, &tcp_master_socket);
    // if( (tcp_master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    // {
    //     perror("TCP socket failed");
    //     exit(EXIT_FAILURE);
    // }

    udp_address = EstablishUDPConnection(udp_port, &udp_socket);
    //create a UDP socket
    // if( (udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    // {
    //     perror("UDP socket failed");
    //     exit(EXIT_FAILURE);
    // }
    broadcast_addr = EstablishBroadcastConnection(broadcast_port, &broadcast_socket);
    //create a Broadcast socket
    // if( (broadcast_socket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    // {
    //     perror("BROADCAST socket failed");
    //     exit(EXIT_FAILURE);
    // }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    // if( setsockopt(tcp_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
    //       sizeof(opt)) < 0 )
    // {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }

    //allowing broadcast server
    // if (setsockopt(broadcast_socket, SOL_SOCKET, SO_BROADCAST, (char *)&opt,
	// 	sizeof(opt)) == -1)
    // {
    //     perror("setsockopt (SO_BROADCAST)");
    //     exit(1);
    // }

    //type of TCP socket created
    // tcp_address.sin_family = AF_INET;
    // tcp_address.sin_addr.s_addr = INADDR_ANY;
    // tcp_address.sin_port = htons( tcp_port );

    //type of UDP socket created
    // udp_address.sin_family = AF_INET;
    // udp_address.sin_addr.s_addr = INADDR_ANY;
    // udp_address.sin_port = htons( udp_port );

    //type of BROADCAST socket created
    // broadcast_addr.sin_family = AF_INET;
    // broadcast_addr.sin_addr.s_addr = INADDR_ANY;
    // broadcast_addr.sin_port = htons( broadcast_port );

    //bind the socket to localhost port 8888
    // if (bind(tcp_master_socket, (struct sockaddr *)&tcp_address, sizeof(tcp_address))<0)
    // {
    //     perror("bind failed");
    //     exit(EXIT_FAILURE);
    // }
    // else
    // {
    //     printf("TCP Listener on port %d \n", tcp_port);
    // }

    // if (bind(udp_socket, (struct sockaddr *)&udp_address, sizeof(udp_address))<0)
    // {
    //     perror("bind failed");
    //     exit(EXIT_FAILURE);
    // }
    // else
    // {
    //     printf("UDP Listener on port %d \n", udp_port);
    // }

    // if (bind(broadcast_socket, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr))<0)
    // {
    //     perror("bind failed");
    //     exit(EXIT_FAILURE);
    // }
    // else
    // {
    //     printf("BROADCAST Listener on port %d \n", broadcast_port);
    // }


    //try to specify maximum of 3 pending connections for the master socket
    // if (listen(tcp_master_socket, 3) < 0)
    // {
    //     perror("listen");
    //     exit(EXIT_FAILURE);
    // }

    //accept the incoming connection
    addrlen = sizeof(tcp_address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        FD_SET(udp_socket, &readfds);
        //add master socket to set
        FD_SET(tcp_master_socket, &readfds);
        FD_SET(broadcast_socket, &readfds);

        max_sd = max(tcp_master_socket, max(udp_socket, broadcast_socket));

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(tcp_master_socket, &readfds))
        {
            if ((new_socket = accept(tcp_master_socket,
                    (struct sockaddr *)&tcp_address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(tcp_address.sin_addr) , ntohs(tcp_address.sin_port));

            //send new connection greeting message

            // if( send(new_socket, message, strlen(message), 0) != strlen(message) )
            // {
            //     perror("send");
            // }
						//
            // puts("Welcome message sent successfully");

            //add new socket to array of sockets
            // for (i = 0; i < max_clients; ++i)
						i = 0;
						while ((client_socket[i] != 0) && (i < max_clients))
            {
                //if position is empty
								++i;
								// if( client_socket[i] == 0 )
                // {
                //     client_socket[i] = new_socket;
                //     printf("Adding to list of sockets as %d\n" , i);
								//
                //     break;
                // }
            }
						(i < max_clients) ? (client_socket[i] = new_socket) : (printf("no more TCP connections available\n"));
        }

        if (FD_ISSET(udp_socket, &readfds))
				{
            len = sizeof(udp_address);
            bzero(buffer, sizeof(buffer));
            printf("\nMessage from UDP client: ");
            n = recvfrom(udp_socket, buffer, sizeof(buffer), 0,
                         (struct sockaddr*)&udp_address, &len);
            puts(buffer);
            sendto(udp_socket, (const char*)message, sizeof(buffer), 0,
                   (struct sockaddr*)&udp_address, sizeof(udp_address));
        }

        if (FD_ISSET(broadcast_socket, &readfds))
        {
          // int len, n;
					bzero(buffer, sizeof(buffer));

					// printf("buffer is %s. ", buffer);

					n = recvfrom(broadcast_socket, (char *)buffer, sizeof(buffer),
											MSG_WAITALL, ( struct sockaddr *) &broadcast_addr,
											(socklen_t *)&len);
					buffer[n] = '\0';
					// printf("buffer is %s. ", buffer);

					printf("%s\n", buffer);
					sendto(broadcast_socket, (const char *)message, sizeof(message),
							MSG_CONFIRM, (const struct sockaddr *) &broadcast_addr,
									len);

					// printf("buffer now is %s\n", buffer);
					bzero(buffer, sizeof(buffer));
					// printf("buffer now is %s\n", buffer);
					sleep(1);
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {

                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&tcp_address , \
                        (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                        inet_ntoa(tcp_address.sin_addr) , ntohs(tcp_address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }

                else
                {
                    printf("SERVER: %s\n", buffer);

                    if (write(sd, message, sizeof(message)) < 0)
                    {
                        perror("write");
                        exit(EXIT_FAILURE);
                    }

                    sleep(1);
                }

            }
        }
    }

    return 0;
}


int IsEnoughArgc(int argc, int max_args)
{
   if (argc < max_args)
    {
        // printf("no PORT inserted, please input it with execution!\n");
        // perror("no input from user");

        return 0;
    }

    return 1;
}

struct sockaddr_in EstablishTCPConnection(int tcp_port, int *tcp_master_socket)
{
    // int tcp_master_socket;
    int opt = TRUE;
    struct sockaddr_in  tcp_address;

    if( (*tcp_master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("TCP socket failed");
        exit(EXIT_FAILURE);
    }

    if( setsockopt(*tcp_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    tcp_address.sin_family = AF_INET;
    tcp_address.sin_addr.s_addr = INADDR_ANY;
    tcp_address.sin_port = htons( tcp_port );

    if (bind(*tcp_master_socket, (struct sockaddr *)&tcp_address, sizeof(tcp_address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("TCP Listener on port %d \n", tcp_port);
    }

     if (listen(*tcp_master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return tcp_address;
}

struct sockaddr_in EstablishUDPConnection(int udp_port,int *udp_socket)
{
    struct sockaddr_in udp_address;

    if( (*udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("UDP socket failed");
        exit(EXIT_FAILURE);
    }

    udp_address.sin_family = AF_INET;
    udp_address.sin_addr.s_addr = INADDR_ANY;
    udp_address.sin_port = htons( udp_port );

    if (bind(*udp_socket, (struct sockaddr *)&udp_address, sizeof(udp_address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("UDP Listener on port %d \n", udp_port);
    }

    return udp_address;
}

struct sockaddr_in EstablishBroadcastConnection(int broadcast_port,int *broadcast_socket)
{
    struct sockaddr_in broadcast_address;
    int opt = TRUE;
    if( (*broadcast_socket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("BROADCAST socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(*broadcast_socket, SOL_SOCKET, SO_BROADCAST, (char *)&opt,
		sizeof(opt)) == -1)
    {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    broadcast_address.sin_family = AF_INET;
    broadcast_address.sin_addr.s_addr = INADDR_ANY;
    broadcast_address.sin_port = htons( broadcast_port );

    if (bind(*broadcast_socket, (struct sockaddr *)&broadcast_address, sizeof(broadcast_address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("BROADCAST Listener on port %d \n", broadcast_port);
    }

    return broadcast_address;
}
