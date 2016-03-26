/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by vdaviot           #+#    #+#             */
/*   Updated: 2016/03/25 19:44:24 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

int					ci_connect_server(t_co *infos)
{
	struct protoent		*proto;
	struct sockaddr_in	sini;
	int					sock;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sini.sin_family = AF_INET;
	sini.sin_port = htons(atoi("4242"));
	sini.sin_addr.s_addr = inet_addr(infos->ip);
	if ((connect(sock, (const struct sockaddr *)&sini,
		sizeof(sini))) == -1)
		ft_exit("Connection failed");
	if ((sendto(sock, infos->name, MAX_LOGIN_LENGTH, MSG_CONFIRM,
	 (const struct sockaddr *)&sini, sizeof(sini))) == -1)
		ft_exit("Cannot send infos to the server");
	return (sock);
}

int					ci_init_connexion()
{
	t_co	*infos;
	int		socket;

	if (!(infos = ci_get_infos()))
		ft_exit("Can't get any reliable informations.");
	printf("\n\nConnection infos: \nname: %s\nip: [%s]\n", infos->name, infos->ip);
	socket = ci_connect_server(infos);
	return (socket);
}
