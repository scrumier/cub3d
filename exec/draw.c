/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 12:29:25 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void draw_square(t_data *data, int x, int y, int coef, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < coef)
	{
		j = 0;
		while (j < coef)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

double calculate_distance(double x0, double y0, double xo, double yo)
{
	return sqrt(pow(x0 - xo, 2) + pow(y0 - yo, 2));
}

int is_out_of_bounds(int map_x, int map_y)
{
	return (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT);
}

int is_wall_hit(char **map, int map_x, int map_y)
{
	return (map[map_x][map_y] == '1' || map[map_x][map_y] == '2');
}

void update_ray_destination(t_ray *ray, double x0, double y0)
{
	ray->dstx = x0 / COEF;
	ray->dsty = y0 / COEF;
}

void init_bresenham(t_bresenham *bresenham, t_ray *ray, int wall_accuracy)
{
	bresenham->x0 = ray->xo;
	bresenham->y0 = ray->yo;
	bresenham->xinc = cos(ray->ra) / wall_accuracy;
	bresenham->yinc = sin(ray->ra) / wall_accuracy;
}

double draw_line(t_ray *ray, t_data *data, int mode, int wall_accuracy)
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
			return calculate_distance(bresenham.x0, bresenham.y0, ray->xo, ray->yo);
		if (is_wall_hit(data->map, map_x, map_y))
		{
			update_ray_destination(ray, bresenham.x0, bresenham.y0);
			return calculate_distance(bresenham.x0, bresenham.y0, ray->xo, ray->yo);
		}
		bresenham.x0 += bresenham.xinc;
		bresenham.y0 += bresenham.yinc;
		if (mode == 1)
			my_mlx_pixel_put(data, (int)bresenham.x0, (int)bresenham.y0, 0x00FFFFFF);
	}
	return RENDER_DISTANCE;
}
