/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 18:13:55 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/26 18:18:50 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#include <ctype.h>

void			ft_exit(char *str) __attribute__ ((noreturn));
void			ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

char			*strtrim_buff(char *s)
{
	char	*ptr;
	size_t	len;

	len = strlen(s);
	ptr = s;
	while (isspace(*ptr) && *ptr)
	{
		ptr++;
		len--;
	}
	if (!*ptr || len <= 0)
	{
		*s = 0;
		return (s);
	}
	memmove(s, ptr, len + 1);
	ptr = s + len - 1;
	while (isspace(*ptr) && ptr != s)
		ptr--;
	ptr[1] = 0;
	return (s);
}
