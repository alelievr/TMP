/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 02:34:33 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 16:43:55 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_rfc.h"
# include <unistd.h>
# include <stdlib.h>

# define STACK_SIZE			42

/*
 **	Client API:
*/
void			add_new_client(int fd);
void			update_client_info(int fd, char *name, char *ip);
void			remove_client(int fd);
t_clients		*get_client_info(int fd);
void			send_new_connected_client(int fd);
int				*get_all_open_sockets(void);
void			send_disconnected_client(int fd);
