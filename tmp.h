/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:35:48 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 19:13:37 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>


# define OPTIONS			"a"

# define MAX_LOGIN_LENGTH	64
# define SERVER_TIMEOUT		60 //1 min

typedef	struct 	s_co
{
	char	name[MAX_LOGIN_LENGTH];
	char	ip[sizeof("255.255.255.255")];
}				t_co;

t_co		*get_connected_client_list(int socket);
t_co		*ci_get_infos(void);
t_co		*ci_get_client_list(int socket);
int			ci_connect_server(t_co *infos);
int			ci_init_connexion(void);
void		ci_wait_msg_server(int socket);
