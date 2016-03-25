/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 23:46:06 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#include <sys/mman.h>

static void		usage(char *s)
{
	printf("%s port\n", s);
}

int				main(int ac, char **av)
{
	int		port;

	if (ac == 2)
	{

	}
	else
		usage();
	return (0);
}
