/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 02:32:51 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 04:03:00 by alelievr         ###   ########.fr       */
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

int				*get_all_open_sockets(void)
{
	static int		s[256];
	int				j;

	j = 0;
	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd)
			s[j++] = g_clients[i].fd;
	s[j] = 0;
	return (s);
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

void			send_new_connected_client(int fd)
{
	t_clients	*cl = NULL;

	for (int i = 0; i < 255; i++)
		if (g_clients[i].fd != fd && g_clients[i].fd)
		{
			write(fd, g_clients + i, MAX_LOGIN_LENGTH + IP_LENGTH);
			printf("writed name: %s - ip: %s to %i\n", g_clients[i].name, g_clients[i].ip, fd);
		}
		else if (g_clients[i].fd == fd)
			cl = g_clients + i;
	if (cl)
		for (int i = 0; i < 255; i++)
			if (g_clients[i].fd && g_clients[i].fd != fd)
			{
				write(g_clients[i].fd, cl, MAX_LOGIN_LENGTH + IP_LENGTH);
				printf("writed name: %s - ip: %s to %i\n", g_clients[i].name, g_clients[i].ip, g_clients[i].fd);
			}
}
