/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:20:35 by mwagner           #+#    #+#             */
/*   Updated: 2023/05/11 10:02:02 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_tail(char *line, char *buff)
{
	int		len;
	char	*tail;
	char	*rest;

	rest = ft_strchr(buff, '\n');
	if (!rest)
		return (ft_concat(line, buff));
	rest++;
	len = rest - buff;
	tail = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpy(tail, buff, len + 1);
	len = ft_strlen(rest);
	ft_memmove(buff, rest, len + 1);
	line = ft_concat(line, tail);
	free(tail);
	return (line);
}

int	ft_read(int fd, char *buf, int size)
{
	int	rd;

	rd = read(fd, buf, size);
	buf[rd] = '\0';
	return (rd);
}

char	*ft_concat(char *line, char *nonl_stash)
{
	char	*newline;

	newline = ft_strjoin(line, nonl_stash);
	free(line);
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	stash[MAX_FD][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		rd;

	if (fd < 0)
		return (NULL);
	line = (char *)malloc(1);
	line[0] = '\0';
	while (!ft_strchr(stash[fd], '\n'))
	{
		line = ft_concat(line, stash[fd]);
		rd = ft_read(fd, stash[fd], BUFFER_SIZE);
		if (!rd && line[0])
			break ;
		if (rd < 1)
		{
			free(line);
			return (NULL);
		}
	}
	line = ft_get_tail(line, stash[fd]);
	return (line);
}
