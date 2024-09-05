/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 10:50:52 by scrumier         ###   ########.fr       */
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
	
	bresenham.x0 = ray->xo;
	bresenham.y0 = ray->yo;
	bresenham.xinc = cos(ray->ra) / wall_accuracy;
	bresenham.yinc = sin(ray->ra) / wall_accuracy;
	int i = 0;
	while (i++ < RENDER_DISTANCE * wall_accuracy)
	{
		int map_x = (int)(bresenham.x0 / COEF);
		int map_y = (int)(bresenham.y0 / COEF);

		if (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT)
			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));

		if (data->map[map_x][map_y] == '1' || data->map[map_x][map_y] == '2')
		{
			ray->dstx = bresenham.x0 / COEF;
			ray->dsty = bresenham.y0 / COEF;

			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));
		}
		bresenham.x0 += bresenham.xinc;
		bresenham.y0 += bresenham.yinc;

		if (mode == 1)
		{
			my_mlx_pixel_put(data, (int)bresenham.x0, (int)bresenham.y0, 0x00FFFFFF);
		}
	}
	return (RENDER_DISTANCE);
}