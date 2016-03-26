/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 02:34:33 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 02:42:24 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <stdlib.h>

# define STACK_SIZE			42
# define IP_LENGTH			sizeof("255.255.255.255")
# define MAX_BUFF			0xF00
# define MAX_LOGIN_LENGTH	64

typedef struct	s_clients
{
	char			name[MAX_LOGIN_LENGTH];
	char			ip[IP_LENGTH];
	int				fd;
	int				:32;
}				t_clients;

/*
 **	Client API:
*/
void			add_new_client(int fd);
void			update_client_info(int fd, char *name, char *ip);
void			remove_client(int fd);
t_clients		*get_client_info(int fd);
void			write_connected_clients(int fd);
