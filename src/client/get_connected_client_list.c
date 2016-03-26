/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connected_client_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 23:18:25 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 20:01:26 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#define IP_FILE ".ip_server"

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

t_co				*ci_get_client_list(int socket)
{
	static t_co		ci_list[255];
	static int		i = -1;

	while ((read(socket, &ci_list[++i], sizeof(t_co))) > 0)
	{
		if (i == 0)
			printf("Clients connected:\n");
		printf("\t%s\n", ci_list[i].name);
		break ;
	}
	ci_list[i].name[0] = 0;
	i = -1;
	while (ci_list[++i].name[0])
		printf("Info on client no%d:\n\tname: \t%s\nip: [%s]\n\n--------------------------\n\n",
		 i, ci_list[i].name, ci_list[i].ip);
	return (ci_list);
}

t_co				*get_connected_client_list(int socket)
{
	return (ci_get_client_list(socket));
}
