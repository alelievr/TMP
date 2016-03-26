/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connected_client_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:18:25 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 19:32:59 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#define IP_FILE ".ip_server"

static void			ft_exit(char *str) __attribute__ ((noreturn));

static void			ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

t_co				*ci_get_infos(void)
{
	t_co			*infos = NULL;
	int				fd;
	ssize_t			ret;
	char			*ptr;

	infos = (t_co*)malloc(sizeof(t_co));
	if((fd = open(IP_FILE, O_RDONLY)) == -1)
		ft_exit("No file found");
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

t_co				*ci_get_client_list(int socket)
{
	static t_co		ci_list[255];
	int				i = -1;

	while ((read(socket, &ci_list[++i], sizeof(t_co))) > 0)
	{
		if (i == 0)
			printf("ci_list[i].name = %s\n", ci_list[i].name);
		printf("\t\t%s\n", ci_list[i].name);
	}
	ci_list[i].name[0] = 0;
	i = -1;
	while (ci_list[++i].name[0])
		printf("Info on client no%d:\n\tname: \t%s\nip: [%s]\n\n-	-	-	-	-	-\n",
		 i, ci_list[i].name, ci_list[i].ip);
	return (ci_list);
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

t_co				*get_connected_client_list(int socket)
{
	return (ci_get_client_list(socket));
}

void				ci_wait_msg_server(int socket)
{
	char			buf[256];
	ssize_t			ret;

	if ((ret = read(socket, buf, 256)) > 0)
	{
		buf[ret] = '\0';
		printf("Server sent %lu bytes: %s\n", ret, buf);
	}
	printf("No bytes received\n");
}
