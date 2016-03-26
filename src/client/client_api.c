/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 02:32:51 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 16:42:28 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

static t_co		g_co[255];

void			add_client(t_co *c)
{
	for (int i = 0; i < 255; i++)
		if (g_co[i].name[0] == 0)
		{
			g_co[i] = *c;
			break ;
		}
}

void			remove_client(t_co *c)
{
	for (int i = 0; i < 255; i++)
		if (!strcmp(g_co[i].name, c->name))
		{
			g_co[i].name[0] = 0;
			break ;
		}
}

int				get_client_list(char *buff)
{
	int		co;

	co = 0;
	for (int i = 0; i < 255; i++)
		if (g_co[i].name[0])
		{
			strcat(buff, g_co[i].name);
			strcat(buff, "\n");
			co++;
		}
	return (co);
}
