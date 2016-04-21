/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 02:34:33 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/28 12:37:41 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_rfc.h"
# include <unistd.h>
# include <stdlib.h>
 #include <sys/select.h>
#include <signal.h>

# define STACK_SIZE			42

/*
 **	Client API:
*/
void			add_new_client(int fd, char *ip);
void			update_client_info(int fd, char *name, int port);
void			remove_client(int fd);
t_clients		*get_client_info(int fd);
void			send_new_connected_client(int fd);
int				*get_all_open_sockets(void);
void			send_disconnected_client(int fd);
