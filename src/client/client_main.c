/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:16:05 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 16:09:28 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void			ft_exit(char *str) __attribute__ ((noreturn));
void			ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

int				main(int ac, char **av)
{
	int			socket;
	fd_set		read_fd;
	fd_set		read_fd_new;

	getopt(ac, av, OPTIONS);
	printf("%s running with %s\n", *av, optarg);
	socket = ci_init_connexion();
	FD_ZERO(&read_fd_new);
	FD_SET(0, &read_fd_new);
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
					stdin_event();
				else if (i == socket)
					server_connection_event(socket);
				else
					peer_connection_event(i);
			}
//		list = get_connected_client_list(socket);
//		ci_wait_msg_server(socket);
		// if (!list[0].name[0])
		// 	break ;
	}
	// close(socket);
	// return (0);
}
