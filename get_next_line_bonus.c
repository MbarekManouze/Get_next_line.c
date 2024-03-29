/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:21:21 by mmanouze          #+#    #+#             */
/*   Updated: 2021/12/11 11:22:37 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*after_line(char *buffer)
{
	int		i;
	int		j;
	char	*found_nl;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			found_nl = ft_substr(buffer, i + 1, ft_strlen(buffer) - i + 1);
			free(buffer);
			return (found_nl);
		}
		i++;
	}
	free(buffer);
	return (NULL);
}

char	*only_line(char *buffer)
{
	int		i;
	char	*one_allowed;

	i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	one_allowed = ft_substr(buffer, 0, i + 1);
	return (one_allowed);
}

char	*read_file(int fd, char *buffer)
{
	int		i;
	char	*take_line;

	i = 1;
	take_line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (!ft_strchr(buffer) && i)
	{
		i = read(fd, take_line, BUFFER_SIZE);
		if (i == -1)
		{
			free(take_line);
			return (NULL);
		}
		take_line[i] = 0;
		buffer = ft_strjoin(buffer, take_line);
	}
	free(take_line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = only_line(buffer[fd]);
	buffer[fd] = after_line(buffer[fd]);
	return (line);
}
