/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by vdaviot           #+#    #+#             */
/*   Updated: 2016/03/25 20:02:24 by shayn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void				ci_wait_msg_server(int socket)
{
	char			buf[256];
	ssize_t			ret;

	if ((ret = read(socket, buf, 256)) > 0)
	{
		buf[ret] = '\0';
		printf("Server sent %lu bytes: %s\n", ret, buf);
	}
	else
		printf("No bytes received\n");
}
