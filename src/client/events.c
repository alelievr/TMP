/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connected_client_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:18:25 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 16:44:54 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

int					server_connection_event(int socket)
{
	long			r;
	t_co			ci;

	if ((r = read(socket, &ci, sizeof(t_co))) < 0)
		perror("(fatal) read"), exit(-1);
	else if (r == 0)
	{
		printf("disconnected from server !\n");
		return (-1);
	}
	else
	{
		ci.fd = 0;
		if (ci.code == CONNECTED_BYTE)
		{
			add_client(&ci);
			printf("new connected client: %s\n", ci.name);
		}
		else
		{
			remove_client(&ci);
			printf("disconnected client: %s\n", ci.name);
		}
	}
	return (1);
}

int					peer_connection_event(int sock)
{
	(void)sock;
	printf("received incoming peer connection/deconnection !\n");
	return (1);
}

int					stdin_event(void)
{
	char		buff[0xF000];
	long		r;

	r = read(0, buff, sizeof(buff));
	printf("catched stdin event: [%s]\n", buff);
	return ((int)r);
}
