/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:41:33 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:51:06 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_init(size_t *i, char *file, int *fd)
{
	*i = 0;
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		return (print_error(INVALID_EXTENSION), 127);
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		return (perror("Error\n"), 1);
	return (0);
}

int	parse_return(t_data *data, int fd)
{
	if (!is_everything_init(data))
		return (127);
	if (map_check(data))
		return (1);
	map_fill_spaces(data);
	if (map_info_parse(data))
		return (1);
	if (data->player->x == -1 || data->player->y == -1)
		return (print_error(NO_PLAYER), 127);
	return (close(fd), 0);
}

int	parse_iter(char **line, char **line_trimmed, int fd)
{
	free(*line);
	free(*line_trimmed);
	if (get_line_trimmed(line, line_trimmed, fd))
		return (close(fd), 1);
	return (0);
}

int	parse_process(t_data *data, char **line, char **line_trimmed, int fd)
{
	while (*line_trimmed)
	{
		if (is_color_line(*line_trimmed))
		{
			if (parse_colors(data, line_trimmed, line, fd))
				return (1);
		}
		else if ((*line_trimmed)[0] == '1' || (*line_trimmed)[0] == '0')
		{
			free(*line_trimmed);
			if (parse_map(data, *line, fd))
				return (close(fd), free(*line), 1);
			if (get_line_trimmed(line, line_trimmed, fd))
				return (close(fd), 1);
			continue ;
		}
		else if ((*line_trimmed)[0])
		{
			if (init_wall(data, *line_trimmed))
				return (close(fd), free(*line), free(*line_trimmed), 1);
		}
		if (parse_iter(line, line_trimmed, fd))
			return (1);
	}
	return (0);
}

int	parse(t_data *data, char *file)
{
	int		fd;
	char	*line_trimmed;
	char	*line;
	size_t	i;

	if (parse_init(&i, file, &fd))
		return (1);
	if (get_line_trimmed(&line, &line_trimmed, fd))
		return (close(fd), 1);
	if (parse_process(data, &line, &line_trimmed, fd))
		return (1);
	return (parse_return(data, fd));
}
