/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasnguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 00:26:59 by pasnguye          #+#    #+#             */
/*   Updated: 2018/01/16 00:17:07 by pasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

static int		check_buf_and_free(char *buf, char **line)
{
	char	*tmp;
	int		i;
	char	n;

	tmp = NULL;
	i = 0;
	n = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!(tmp = ft_strnew((ft_strlen(*line) + i))))
		return (0);
	ft_strcpy(tmp, *line);
	if (*line)
		free(*line);
	ft_strncat(tmp, buf, i);
	*line = tmp;
	printf("ligne 36 : [%s]\n", buf);
	n = (buf[i] == '\n') ? 1 : 0;
	ft_strcpy(buf, &(buf[i + n]));
	printf("ligne 39 i : [%d]\n", i);
	printf("ligne 40 : [%s]\n", buf);
	return (n);
}

int				get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || (read(fd, &ret, 0) == -1) || !line)
		return (-1);
	*line = NULL;
	printf("ligne 52 : [%s]\n", buf);
	if (buf[0] && check_buf_and_free(buf, line))
		return (1);
	printf("ligne 55 : [%s]\n", buf);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
	printf("ligne 59 : [%s]\n", buf);
		if (check_buf_and_free(buf, line) == 1)
			return (1);
	}
	if (*line)
		return (1);
	return (0);
}

int		main(int argc, char** argv)
{
	int fd;
	char *line;

	if (argc)
		;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
		printf(" print %s\n", line);
	return (0);
}
