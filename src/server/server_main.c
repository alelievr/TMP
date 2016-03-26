/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 04:06:29 by alelievr         ###   ########.fr       */
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
	t_clients			buffer;
	long				nbytes;

	struct sockaddr_in	connection;
	socklen_t			addrlen;

	nbytes = recvfrom(filedes, &buffer, sizeof(buffer), 0, (struct sockaddr *)&connection, &addrlen);
	if (nbytes < 0)
		perror ("recvfrom"), exit (EXIT_FAILURE);
	else if (nbytes == 0)
		return -1;
	else
	{
		printf("%s\n", inet_ntoa(connection.sin_addr));
		printf("received name: [%s]\n", buffer.name);
		update_client_info(filedes, buffer.name, NULL);
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
				printf("accepted connection: %i\n", new);
				add_new_client(new);
				FD_SET(new, active_fd);
			}
			else
			{
				if (read_from_client(i) < 0)
				{
					printf("%s closed !\n", get_client_info(i)->name);
					close (i);
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
		while (42)
			wait_for_event(sock, &read_fd);
	}
	else
		usage(*av);
	return (0);
}
