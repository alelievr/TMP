/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 02:32:51 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 02:43:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_server.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

static t_clients	g_clients[255];

void			add_new_client(int fd)
{
	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd == 0)
		{
			g_clients[i].fd = fd;
			break ;
		}
}

void			update_client_info(int fd, char *name, char *ip)
{
	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd == fd)
		{
			strncpy(g_clients[i].name, name, 63);
			if (!ip)
				strcpy(g_clients[i].ip, "0.0.0.0");
			else
				strcpy(g_clients[i].ip, ip);
			g_clients[i].name[63] = 0;
			break ;
		}
}

void			remove_client(int fd)
{
	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd == fd)
		{
			g_clients[i].fd = 0;
			break ;
		}
}

t_clients		*get_client_info(int fd)
{
	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd == fd)
			return (g_clients + i);
	return (NULL);
}

void			write_connected_clients(int fd)
{
	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd != fd && g_clients[i].fd)
		{
			printf("writed name: %s - ip: %s\n", g_clients[i].name, g_clients[i].ip);
			write(fd, g_clients + i, MAX_LOGIN_LENGTH + IP_LENGTH);
		}
}
