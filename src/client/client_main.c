/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:16:05 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 18:37:42 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

static int		create_udp_socket(void)
{
	int					ret;
	struct sockaddr_in	connection;

	if ((ret = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		perror("sock"), exit(-1);
	bzero(&connection, sizeof(connection));
	connection.sin_family = AF_INET;
	connection.sin_port = htons(CLIENTS_PORT);
	connection.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(ret, (struct sockaddr *)&connection, sizeof(connection))==-1)
		perror("(fatal) bind"), exit(-1);
	return (ret);
}

int				main(int ac, char **av)
{
	int			socket;
	int			sock_read_message;
	int			sock_send_message;
	fd_set		read_fd;
	fd_set		read_fd_new;

	getopt(ac, av, OPTIONS);
	printf("%s running with %s\n", *av, optarg);
	socket = ci_init_connexion();
	sock_read_message = create_udp_socket();
	sock_send_message = sock_read_message;
	FD_ZERO(&read_fd_new);
	FD_SET(0, &read_fd_new);
	FD_SET(sock_read_message, &read_fd_new);
	if (socket != -1)
		FD_SET(socket, &read_fd_new);
	while (42)
	{
		read_fd = read_fd_new;
		if (select(FD_SETSIZE, &read_fd, NULL, NULL, NULL) < 0)
			perror("(fatal) select"), exit(-1);
		for (int i = 0; i < FD_SETSIZE; ++i)
			if (FD_ISSET(i, &read_fd))
			{
				if (i == 0)
					stdin_event(sock_send_message);
				else if (i == sock_read_message)
					peer_message_event(sock_read_message);
				else if (i == socket)
				{
					if (server_connection_event(socket) == -1)
					{
						close(socket);
						FD_CLR(socket, &read_fd_new);
					}
				}
				else
					peer_connection_event(i);
			}
	}
}
