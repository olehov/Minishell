/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:09:16 by ogrativ           #+#    #+#             */
/*   Updated: 2024/05/22 16:20:14 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"
#include <unistd.h>

char	*ft_join_and_free(char *dest, char *src)
{
	char	*str;

	str = ft_strjoin(dest, src);
	free(dest);
	return (str);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		size;

	size = 0;
	if (!buffer[size])
		return (NULL);
	while (buffer[size] != '\0' && buffer[size] != '\n')
	{
		size++;
	}
	size++;
	line = (char *)malloc(sizeof(char) * size + 1);
	if (line == NULL)
		return (NULL);
	line[size] = '\0';
	while (size > 0)
	{
		size--;
		line[size] = buffer[size];
	}
	return (line);
}

static char	*ft_skip_line(char *buffer)
{
	char	*line;
	int		size;
	int		j;

	size = 0;
	while (buffer[size] != '\0' && buffer[size] != '\n')
		size++;
	if (buffer[size] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	++size;
	line = ft_calloc(sizeof(char), (ft_strlen(buffer) - size + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (buffer[size] != '\0')
	{
		line[j++] = buffer[size++];
	}
	line[j] = '\0';
	free(buffer);
	return (line);
}

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (res == NULL)
	{
		res = ft_calloc(1, 1);
		if (res == NULL)
			return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1 || byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		res = ft_join_and_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*str;

	if ((fd < 0 || fd > FOPEN_MAX) || BUFFER_SIZE < 1)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] == NULL)
	{
		return (NULL);
	}
	str = get_line(buffer[fd]);
	buffer[fd] = ft_skip_line(buffer[fd]);
	return (str);
}
