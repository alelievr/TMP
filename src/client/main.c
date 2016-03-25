/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 15:19:06 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

t_co			ci_connect_server(t_co info, char *name)
{
	
}

int				main(int ac, char **av)
{
	t_co		*infos;

	ci_init(av[1], );
	if (!(infos = ci_connect_server(&infos, av[1])))
		ft_exit("Connection to server failed");
	ci_send_message()
	return (0);
}
