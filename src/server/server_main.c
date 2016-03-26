/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 02:41:54 by alelievr         ###   ########.fr       */
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
	char				buffer[MAX_BUFF];
	long				nbytes;

	struct sockaddr_in	connection;
	socklen_t			addrlen;

	nbytes = recvfrom(filedes, buffer, MAX_BUFF, 0, (struct sockaddr *)&connection, &addrlen);
	if (nbytes < 0)
		perror ("recvfrom"), exit (EXIT_FAILURE);
	else if (nbytes == 0)
		return -1;
	else
		update_client_info(filedes, buffer, NULL);
	return 0;
}

static void		wait_for_event(int sock, fd_set *read_fd)
{
	struct			sockaddr_in clientname;
	socklen_t		size;

	if (select(FD_SETSIZE, read_fd, NULL, NULL, NULL) < 0)
		perror("(fatal) select"), exit(-1);

	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, read_fd))
		{
			if (i == sock)
			{
				int new;
				size = sizeof (clientname);
				new = accept (sock, (struct sockaddr *)&clientname, &size);
				if (new < 0)
				{
					perror ("accept");
					exit(EXIT_FAILURE);
				}
				struct sockaddr_in client = clientname;
				printf("%s\n", inet_ntoa(client.sin_addr));

				printf("accepted connection: %i\n", new);
				add_new_client(new);
				FD_SET (new, read_fd);
			}
			else
			{
				if (read_from_client(i) < 0)
				{
					printf("%s closed !\n", get_client_info(i)->name);
					close (i);
					remove_client(i);
					FD_CLR (i, read_fd);
				}
				else
					write_connected_clients(i);
			}
		}
}

int				main(int ac, char **av)
{
	int					port;
	int					sock;
	fd_set				read_fd;

	if (ac == 2)
	{
		port = atoi(av[1]);
		sock = create_server(port);
		FD_ZERO(&read_fd);
		FD_SET(sock, &read_fd);
		while (42)
			wait_for_event(sock, &read_fd);
	}
	else
		usage(*av);
	return (0);
}
