/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by vdaviot           #+#    #+#             */
/*   Updated: 2016/03/26 16:03:32 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

static t_co			*ci_get_infos(void)
{
	t_co			*infos = NULL;
	int				fd;
	ssize_t			ret;
	char			*ptr;

	if (!(infos = (t_co*)malloc(sizeof(t_co))))
		perror("malloc"), exit(-1);
	if((fd = open(IP_FILE, O_RDONLY)) == -1)
		ft_exit("IP file config not found");
	if ((ret = read(fd, infos->ip, 15)) > 0)
	{
		infos->ip[ret] = '\0';
		if (!(ptr = strchr(infos->ip, ':')))
			return (NULL);
		else
			*ptr = '\0';
		close(fd);
	}
	printf("\nEnter a name: ");
	fflush(stdout);
	if ((ret = read(0, infos->name, MAX_LOGIN_LENGTH)) > 0)
		infos->name[ret] = '\0';
	return (infos);
}

static int				ci_connect_server(t_co *infos)
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
	if ((sendto(sock, infos->name, MAX_LOGIN_LENGTH, 0, (const struct sockaddr *)&sini, sizeof(sini))) == -1)
		perror("(fatal) sendto"), exit(-1);
	return (sock);
}

int					ci_init_connexion()
{
	t_co	*infos;
	int		socket;

	if (!(infos = ci_get_infos()))
		ft_exit("bad IP file format");
	printf("\n\nConnection infos: \nname: %s\nip: [%s]\n", infos->name, infos->ip);
	socket = ci_connect_server(infos);
	return (socket);
}
