/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created  2016/03/25 22:35:48 by alelievr          #+#    #+#             */
/*   Updated  2016/03/25 19:47:57 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ft_rfc.h"
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
# define IP_FILE			".ip_server"

typedef t_clients	t_co;

t_co		*get_connected_client_list(int socket);
t_co		*ci_get_client_list(int socket);
int			ci_init_connexion(void);
void		ft_exit(char *str);
int			get_client_list(char *buff);
void		get_server_ip(char *domain, char *ip);

/*
 **	Connection events:
*/
int			stdin_event(void);
int			server_connection_event(int socket);
int			peer_connection_event(int socket);
void		add_client(t_co *c);
void		remove_client(t_co *c);
