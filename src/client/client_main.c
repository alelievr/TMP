/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:16:05 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 19:56:28 by shayn            ###   ########.fr       */
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
	t_co		*list;
	int			socket;

	getopt(ac, av, OPTIONS);
	printf("%s running with %s\n", *av, optarg);
	socket = ci_init_connexion();
	while (42)
	{
		list = get_connected_client_list(socket);
		ci_wait_msg_server(socket);
		// if (!list[0].name[0])
		// 	break ;
	}
	// close(socket);
	// return (0);
}
