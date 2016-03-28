/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connected_client_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:18:25 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/28 12:55:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#include <time.h>

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

int					stdin_event(int sock)
{
	char				buff[0xF000];
	long				r;
	t_co				*co;
	t_message			m;
	struct sockaddr_in	connection;

	if ((r = read(0, buff, sizeof(buff))) < 0)
		perror("(fatal) read"), exit(-1);
	if (!r)
		return (-1);
	buff[r] = 0;
	printf("catched stdin event: [%s]\n", buff);
	co = get_client_info(0);
	if (co)
	{
		printf("sending to the first connected person: %s : %s:%i\n", co->name, co->ip, htons(co->port));
		bzero(&connection, sizeof(connection));
		connection.sin_family = AF_INET;
		connection.sin_port = htons(co->port);
		if (inet_aton(co->ip, &connection.sin_addr) == 0)
			perror("inet_aton");

		m.time = time(NULL);
		unsigned char buf[sizeof(struct in6_addr)];
		m.id.ip = inet_pton(AF_INET, "localhost", buf);
		m.id.pid = getpid();
		strcpy(m.message, buff);

		if (sendto(sock, &m, sizeof(m), 0, (struct sockaddr *)&connection, sizeof(connection)) < 0)
			perror("sendto");
	}
	return ((int)r);
}

int					peer_message_event(int sock)
{
	struct sockaddr_in		co;
	socklen_t				colen;
	t_message				m;
	long					r;

	printf("here !\n");
	colen = sizeof(co);
	if ((r = recvfrom(sock, &m, sizeof(m), 0, (struct sockaddr *)&co, &colen)) == -1)
		perror("recvfrom");
	else if (r == 0)
		return (-1);
	printf("received message: <%u:%u> [%s] %s\n", m.id.ip, m.id.pid, ctime((const time_t *)&(m.time)), m.message);
	return (1);
}
