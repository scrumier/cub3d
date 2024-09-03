/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/03 17:08:13 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void draw_square(t_data *data, int x, int y, int coef, int color)
{
	int i = 0;
	int j = 0;


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

double draw_line(t_ray *ray, t_data *data, int mode, int wall_accuracy)
{
	t_bresenham bresenham;

	bresenham.x = ray->xo;
	bresenham.y = ray->yo;
	bresenham.x1 = ray->rx;
	bresenham.y1 = ray->ry;
	bresenham.dx = ft_dabs(bresenham.x1 - bresenham.x);
	bresenham.dy = ft_dabs(bresenham.y1 - bresenham.y);

	if (bresenham.x1 > bresenham.x)
		bresenham.xinc = 1;
	else
		bresenham.xinc = -1;
	if (bresenham.y1 > bresenham.y)
		bresenham.yinc = 1;
	else
		bresenham.yinc = -1;

	bresenham.steps = (bresenham.dx > bresenham.dy) ? bresenham.dx : bresenham.dy;

	bresenham.xinc *= bresenham.dx / bresenham.steps;
	bresenham.yinc *= bresenham.dy / bresenham.steps;

	bresenham.x0 = bresenham.x;
	bresenham.y0 = bresenham.y;

	while (1)
	{
		int map_x = ft_abs((int)bresenham.x0) / COEF;
		int map_y = ft_abs((int)bresenham.y0) / COEF;

		if (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT)
			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));

		if (data->map[map_x][map_y] == '1' || data->map[map_x][map_y] == '2')
		{
			while (data->map[map_x][map_y] == '1' || data->map[map_x][map_y] == '2')
			{
				bresenham.x0 -= bresenham.xinc / wall_accuracy * 4;
				bresenham.y0 -= bresenham.yinc / wall_accuracy * 4;
				map_x = ft_abs((int)bresenham.x0) / COEF;
				map_y = ft_abs((int)bresenham.y0) / COEF;
			}

			while (data->map[map_x][map_y] == '0')
			{
				bresenham.x0 += bresenham.xinc / wall_accuracy * 10;
				bresenham.y0 += bresenham.yinc / wall_accuracy * 10;
				map_x = ft_abs((int)bresenham.x0) / COEF;
				map_y = ft_abs((int)bresenham.y0) / COEF;
			}

			ray->dstx = bresenham.x0 / COEF;
			ray->dsty = bresenham.y0 / COEF;

			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));
		}

		if (wall_around_05(data, bresenham.x0 / COEF, bresenham.y0 / COEF))
		{
			bresenham.x0 += bresenham.xinc / wall_accuracy;
			bresenham.y0 += bresenham.yinc / wall_accuracy;
		}
		else
		{
			bresenham.x0 += bresenham.xinc;
			bresenham.y0 += bresenham.yinc;
		}

		if (mode == 1)
		{
			my_mlx_pixel_put(data, (int)bresenham.x0, (int)bresenham.y0, 0x00FFFFFF);
		}
	}
}