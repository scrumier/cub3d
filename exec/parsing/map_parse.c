/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:41:59 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 13:38:29 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	first_map_node(char *line, t_llist **map, t_llist **last)
{
	*map = ft_calloc(1, sizeof(t_llist));
	if (!*map)
		return (1);
	(*map)->content = ft_strndup(line, ft_strlen(line) - 1);
	if (!(*map)->content)
		return (free(*map), 1);
	*last = *map;
	return (0);
}

int	add_map_node(char *line, t_llist **map, t_llist **last)
{
	size_t	len;

	(*last)->next = ft_calloc(1, sizeof(t_llist));
	if (!(*last)->next)
		return (free_llist(*map), 1);
	*last = (*last)->next;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		(*last)->content = ft_strndup(line, len - 1);
	else
		(*last)->content = ft_strdup(line);
	if (!(*last)->content)
		return (free_llist(*map), 1);
	return (0);
}

int	parse_map_iterate(t_data *data, char **line, int fd)
{
	data->mapy++;
	free(*line);
	errno = 0;
	*line = get_next_line(fd);
	if (!*line && errno)
		return (1);
	return (0);
}

int	map_info_parse(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < (size_t)data->mapy)
	{
		j = 0;
		while (j < (size_t)data->mapx)
		{
			if (!is_map_char(data->map[i][j]))
				return (print_error(INVALID_MAP), 22);
			if (ft_isalpha(data->map[i][j]))
			{
				if (data->player->x != -1 || data->player->y != -1)
					return (print_error(MULTIPLE_PLAYERS), 127);
				data->player->x = j;
				data->player->y = i;
				data->player->player_angle = get_player_angle(data->map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_map(t_data *data, char *line, int fd)
{
	t_llist	*map;
	t_llist	*last;

	map = NULL;
	last = NULL;
	data->mapy = 0;
	if (data->map)
		return (print_error(VALUE_AFTER_MAP), 127);
	while (line && line[0] != '\n')
	{
		if (!map)
		{
			if (first_map_node(line, &map, &last))
				return (1);
		}
		else
		{
			if (add_map_node(line, &map, &last))
				return (1);
		}
		if (parse_map_iterate(data, &line, fd))
			return (free_llist(map), 1);
	}
	padding_map(data, map);
	return (free(line), free_llist(map), 0);
}
