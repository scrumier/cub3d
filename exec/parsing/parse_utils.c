/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:29:44 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:48:13 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_error(char *reason)
{
	write(2, "Error\n", 7);
	write(2, reason, ft_strlen(reason));
	write(2, "\n", 1);
}

size_t	strarray_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	get_line_trimmed(char **line, char **line_trimmed, int fd)
{
	errno = 0;
	*line = get_next_line(fd);
	if (!*line && errno)
		return (1);
	*line_trimmed = ft_strtrim(*line, " \t\n\v\f\r");
	if (!*line_trimmed && *line)
		return (free(*line), 1);
	return (0);
}
