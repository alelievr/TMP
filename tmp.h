/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:35:48 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/25 16:51:41 by shayn            ###   ########.fr       */
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

# define OPTIONS			"a"

# define MAX_LOGIN_LENGTH	64
# define SERVER_TIMEOUT		60 //1 min

typedef	struct 	s_co
{
	char	name[MAX_LOGIN_LENGTH];
	char	ip[sizeof("255.255.255.255")];
	char	i
}				t_co;

t_co		*get_connected_client_list(void);
t_co		*ci_get_infos(void);
