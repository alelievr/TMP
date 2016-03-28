/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rfc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:28:10 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/28 12:28:58 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define CONNECTED_BYTE			'\01'
#define DISCONNECTED_BYTE		'\00'

# define IP_LENGTH				sizeof("255.255.255.255")
# define MAX_LOGIN_LENGTH		64

# define CLIENTS_PORT			10042
# define CLIENT_MESSAGE_LENGTH	256

typedef struct	s_clients
{
	char			code;
	long			:48;
	char			name[MAX_LOGIN_LENGTH];
	char			ip[IP_LENGTH];
	int				:8;
	int				fd;
	int				port;
}				t_clients;
