/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created  2016/03/25 23:16:05 by alelievr          #+#    #+#             */
/*   Updated  2016/03/25 15:19:06 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#include <stdio.h>

int				main(int ac, char **av)
{
	char		opts[0xF00];
	t_co		*infos;

	getopt(ac, av, opts);
	printf("%s running with %s\n", *av, opts);

	infos = get_connected_client_list(opts);
	return (0);
}
