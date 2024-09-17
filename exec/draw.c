/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 16:35:43 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_player_on_minimap(t_data *data)
{
	t_coord	coord;

	coord.x = data->player->x * COEF;
	coord.y = data->player->y * COEF;
	print_minimap(data, 1);
	draw_square(data, coord, COEF, 0x00FF00);
}

void	draw_square(t_data *data, t_coord coord, int coef, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < coef)
	{
		j = 0;
		while (j < coef)
		{
			my_mlx_pixel_put(data, coord.x + i, coord.y + j, color);
			j++;
		}
		i++;
	}
}

double	draw_line(t_ray *ray, t_data *data, int mode, int wall_accuracy)
{
	t_bresenham	bresenham;
	int			map_x;
	int			map_y;
	int			i;

	i = 0;
	init_bresenham(&bresenham, ray, wall_accuracy);
	while (i++ < RENDER_DISTANCE * wall_accuracy)
	{
		map_x = (int)(bresenham.x0 / COEF);
		map_y = (int)(bresenham.y0 / COEF);
		if (is_out_of_bounds(map_x, map_y))
			return (calculate_distance(bresenham.x0, bresenham.y0, \
					ray->xo, ray->yo));
		if (is_wall_hit(data->map, map_x, map_y))
			return (update_ray_destination(ray, bresenham.x0, bresenham.y0), \
					calculate_distance(bresenham.x0, bresenham.y0, \
					ray->xo, ray->yo));
		bresenham.x0 += bresenham.xinc;
		bresenham.y0 += bresenham.yinc;
		if (mode == 1)
			my_mlx_pixel_put(data, (int)bresenham.x0, \
					(int)bresenham.y0, 0x00FFFFFF);
	}
	return (RENDER_DISTANCE);
}

void	print_minimap(t_data *data, int mode)
{
	int		j;
	int		i;
	t_coord	coord;

	i = 0;
	j = 0;
	while (i < data->mapx)
	{
		j = 0;
		while (j < data->mapy)
		{
			coord.x = i * COEF;
			coord.y = j * COEF;
			if ((data->map[j][i] == '1' || data->map[j][i] == '2') && mode == 2)
				draw_square(data, coord, COEF, 0x00000000);
			else if (data->map[j][i] == '3' && mode == 2)
				draw_square(data, coord, COEF, 0x00FF0000);
			else if ((data->map[j][i] == '0' || ft_isalpha(data->map[j][i])) \
						&& mode == !data->flash_light)
				draw_square(data, coord, COEF, 0x00A9A9A9);
			j++;
		}
		i++;
	}
}
