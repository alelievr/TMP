/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created  2016/03/25 22:35:48 by alelievr          #+#    #+#             */
/*   Updated  2016/03/25 15:24:00 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <unistd.h>
# include <stdlib.h>

typedef	struct 	s_co
{
	char	*name;
	int		socket;
	int		:32;
}				t_co;

t_co		*get_connected_client_list(char *opts);
