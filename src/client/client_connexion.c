/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayn <shayn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 22:39:17 by vdaviot           #+#    #+#             */
/*   Updated: 2016/03/26 22:19:15 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>

static int			get_server_ip(char *hostname, char *ip)
{
	struct addrinfo		*result;
	struct addrinfo		*res;
	struct sockaddr_in	*sock_ip;
	int					error;

	if ((error = getaddrinfo(hostname, NULL, NULL, &result)) != 0)
		return (0);
	res = result;
	sock_ip = (struct sockaddr_in *)(unsigned long)res->ai_addr;
	strcpy(ip, inet_ntoa(sock_ip->sin_addr));
	freeaddrinfo(result);
	return (1);
}

static int			get_local_ip(char *ip)
{
	struct ifaddrs		*ias = NULL;
	struct ifaddrs		*ifa = NULL;
	void				*tmp = NULL;
	char				buff[INET_ADDRSTRLEN];

	getifaddrs(&ias);
	for (ifa = ias; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (!ifa->ifa_addr)
			continue;
		if (ifa->ifa_addr->sa_family == AF_INET) {
			tmp = &((struct sockaddr_in *)(unsigned long)ifa->ifa_addr)->sin_addr;
			inet_ntop(AF_INET, tmp, buff, INET_ADDRSTRLEN);
			printf("%s IP Address %s\n", ifa->ifa_name, buff);
			if (!strcmp(buff, "127.0.0.1"))
				continue ;
			strcpy(ip, buff);
			break ;
		}
	}
	if (ias)
		freeifaddrs(ias);
	return 0;
}

static t_co			*ci_get_infos(void)
{
	t_co			*infos = NULL;
	int				fd;
	ssize_t			ret;
	char			*ptr;
	char			buf_dns[255];

	if (!(infos = (t_co*)malloc(sizeof(t_co))))
		perror("malloc"), exit(-1);
	if((fd = open(IP_FILE, O_RDONLY)) == -1)
		ft_exit("IP file not found");
	if ((ret = read(fd, buf_dns, 255)) > 0)
	{
		buf_dns[ret] = '\0';
		// infos->ip[ret] = '\0';
		if (!(ptr = strchr(buf_dns, ':')))
			return (NULL);
		else
			*ptr = '\0';
		close(fd);
	}
	printf("\nEnter a name: ");
	fflush(stdout);
	if ((ret = read(0, infos->name, MAX_LOGIN_LENGTH)) > 0)
		infos->name[ret] = '\0';
	strtrim_buff(infos->name);
	if (!get_server_ip(buf_dns, infos->ip))
		return (NULL);
	return (infos);
}

static int				ci_connect_server(t_co *infos)
{
	struct protoent		*proto;
	struct sockaddr_in	sini;
	int					sock;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sini.sin_family = AF_INET;
	sini.sin_port = htons(atoi("4242"));
	sini.sin_addr.s_addr = inet_addr(infos->ip);
	if ((connect(sock, (const struct sockaddr *)&sini, sizeof(sini))) == -1)
	{
		printf("Server connection failed\n");
		return (-1);
	}
	get_local_ip(infos->ip);
	if ((sendto(sock, infos->name, MAX_LOGIN_LENGTH + IP_LENGTH, 0, (const struct sockaddr *)&sini, sizeof(sini))) == -1)
		perror("(fatal) sendto"), exit(-1);
	return (sock);
}

int					ci_init_connexion()
{
	t_co	*infos;

	if (!(infos = ci_get_infos()))
		ft_exit("bad IP file format/hostname unreachable");
	printf("\n\nConnection infos: \nname: %s\nip: [%s]\n", infos->name, infos->ip);
	return (ci_connect_server(infos));
}

<<<<<<< HEAD
void				get_server_ip(char *domain, char *ip)
{
	struct addrinfo	hints, *res, *p;
	int				status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if ((status = getaddrinfo(domain, NULL, &hints, &res)) != 0)
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	for(p = res; p != NULL; p = p->ai_next)
	{
		void 			*addr;
		char 			*ipver = NULL;

		if (p->ai_family == AF_INET)
		{
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)(unsigned long)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
        printf("  %s: %s\n", ipver, ip);
		inet_ntop(p->ai_family, addr, ip, sizeof(IP_LENGTH));
        printf("  %s: %s\n", ipver, ip);
    }
    freeaddrinfo(res);
}
=======
>>>>>>> b198b4de8957710a7562166b81502478e8801602
