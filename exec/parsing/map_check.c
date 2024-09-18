/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:41:49 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:58:20 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_everything_init(t_data *data)
{
	if (data->ceiling_color == -1)
		return (print_error(CEILING_NOT_INIT), false);
	if (data->floor_color == -1)
		return (print_error(FLOOR_NOT_INIT), false);
	if (!data->texture[WALL_NO] || !data->texture[WALL_SO] \
		|| !data->texture[WALL_WE] || !data->texture[WALL_EA] \
		|| !data->texture[BEAM] || !data->texture[DOOR])
		return (print_error(WALLS_NOT_INIT), false);
	if (!data->map)
		return (print_error(MAP_NOT_INIT), false);
	return (true);
}

int	space_check_diagonal(t_data *data, size_t x, size_t y)
{
	size_t	map_width;
	size_t	map_height;

	map_width = data->mapx;
	map_height = data->mapy;
	if (x > 0 && y > 0 && (data->map[y - 1][x - 1] != '1'
		&& data->map[y - 1][x - 1] != ' '))
		return (0);
	if (x + 1 < map_width && y > 0 && (data->map[y - 1][x + 1] != '1'
		&& data->map[y - 1][x + 1] != ' '))
		return (0);
	if (x > 0 && y + 1 < map_height && (data->map[y + 1][x - 1] != '1'
		&& data->map[y + 1][x - 1] != ' '))
		return (0);
	if (x + 1 < map_width && y + 1 < map_height
		&& (data->map[y + 1][x + 1] != '1' && data->map[y + 1][x + 1] != ' '))
		return (0);
	return (1);
}

int	space_check(t_data *data, size_t x, size_t y)
{
	size_t	map_width;
	size_t	map_height;

	map_width = data->mapx;
	map_height = data->mapy;
	if (x > 0 && (data->map[y][x - 1] != '1' && data->map[y][x - 1] != ' '))
		return (0);
	if (x + 1 < map_width && (data->map[y][x + 1] != '1'
		&& data->map[y][x + 1] != ' '))
		return (0);
	if (y > 0 && (data->map[y - 1][x] != '1' && data->map[y - 1][x] != ' '))
		return (0);
	if (y + 1 < map_height && (data->map[y + 1][x] != '1'
		&& data->map[y + 1][x] != ' '))
		return (0);
	if (!space_check_diagonal(data, x, y))
		return (0);
	return (1);
}

int	map_check(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < data->mapy)
	{
		if (map_check_init_x(&x, y, data))
			return (22);
		while (data->map[y][x])
		{
			if ((y == 0 || y == data->mapy - 1)
				&& data->map[y][x] != '1' && data->map[y][x] != ' ')
				return (print_error(INVALID_MAP), 22);
			if (data->map[y][x] == ' ')
			{
				if (!space_check(data, x, y))
					return (print_error(INVALID_MAP), 22);
			}
			x++;
		}
		if (data->map[y][x - 1] != '1' && data->map[y][x - 1] != ' ')
			return (print_error(INVALID_MAP), 22);
		y++;
	}
	return (0);
}
