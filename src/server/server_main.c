/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by alelievr          #+#    #+#             */
/*   Updated: 2016/04/19 18:13:40 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_server.h"
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

static void			usage(char *s)
{
	printf("%s [port]\n", s);
}

static int			create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		printf("cant bind port: %i\n", port), exit(-1);
	printf("Server connected on port %i\n", port);
	listen(sock, STACK_SIZE);
	return (sock);
}

static int		read_from_client(int filedes)
{
	char				buff[MAX_LOGIN_LENGTH + IP_LENGTH];
	long				nbytes;
	struct sockaddr_in	connection;
	socklen_t			addrlen = sizeof(connection);
	int					port;

	nbytes = recvfrom(filedes, buff, sizeof(buff), 0, (struct sockaddr *)&connection, &addrlen);
	if (nbytes < 0)
		perror("recvfrom"), exit(-1);
	else if (nbytes == 0)
		return -1;
	else
	{
		port = /*ntohs(((struct sockaddr_in *)&connection)->sin_port)*/ntohs(atoi(buff + MAX_LOGIN_LENGTH));
		printf("received infos: [%s] : [%s]\n", buff, buff + MAX_LOGIN_LENGTH);
		update_client_info(filedes, buff, port, buff + MAX_LOGIN_LENGTH);
		send_new_connected_client(filedes);
	}
	return 0;
}

static void		wait_for_event(int sock, fd_set *active_fd)
{
	struct			sockaddr_in clientname;
	socklen_t		size;
	fd_set			read_fd;
	int				new_sock;

	read_fd = *active_fd;
	if (select(FD_SETSIZE, &read_fd, NULL, NULL, NULL) < 0)
		perror("(fatal) select"), exit(-1);

	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd))
		{
			if (i == sock)
			{
				size = sizeof(clientname);
				if ((new_sock = accept(sock, (struct sockaddr *)&clientname, &size)) < 0)
					perror ("accept"), exit(-1);
				printf("accepted connection: %i\n", new_sock);
				add_new_client(new_sock);
				FD_SET(new_sock, active_fd);
			}
			else
			{
				if (read_from_client(i) < 0)
				{
					printf("%s closed !\n", get_client_info(i)->name);
					close (i);
					send_disconnected_client(i);
					remove_client(i);
					FD_CLR(i, active_fd);
				}
			}
		}
}

static int		get_server_socket(int s)
{
	static int so = 0;

	if (s)
		so = s;
	return (so);
}

static void		close_sockets(int s)
{
	int		ss;
	int		*socks;

	(void)s;
	if ((ss = get_server_socket(0)))
		close(ss);
	socks = get_all_open_sockets();
	for (int i = 0; socks[i]; i++)
		close(socks[0]);
}

int				main(int ac, char **av)
{
	int					port;
	int					sock;
	fd_set				read_fd;

	if (ac == 2)
	{
		signal(SIGINT, close_sockets);
		port = atoi(av[1]);
		sock = create_server(port);
		get_server_socket(sock);
		FD_ZERO(&read_fd);
		FD_SET(sock, &read_fd);
//		FD_SET(0, &read_fd);
		while (42)
			wait_for_event(sock, &read_fd);
	}
	else
		usage(*av);
	return (0);
}
