/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:42:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 11:11:59 by scrumier         ###   ########.fr       */
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

double	draw_line(t_ray *ray, t_data *data, int mode)
{
	t_bresenham bresenham;
	int i;

	i = 0;
	bresenham.x = ray->xo;
	bresenham.y = ray->yo;
	bresenham.x1 = ray->rx;
	bresenham.y1 = ray->ry;
	bresenham.dx = bresenham.x1 - bresenham.x;
	bresenham.dy = bresenham.y1 - bresenham.y;
	if (bresenham.dx < 0)
	{
		bresenham.xinc = -1;
		bresenham.dx = -bresenham.dx;
	}
	else
		bresenham.xinc = 1;
	if (bresenham.dy < 0)
	{
		bresenham.yinc = -1;
		bresenham.dy = -bresenham.dy;
	}
	else
		bresenham.yinc = 1;
	bresenham.dx = ft_dabs(bresenham.dx);
	bresenham.dy = ft_dabs(bresenham.dy);
	if (bresenham.dx > bresenham.dy)
		bresenham.steps = bresenham.dx;
	else
		bresenham.steps = bresenham.dy;
	bresenham.xinc *= (double)bresenham.dx / bresenham.steps;
	bresenham.yinc *= (double)bresenham.dy / bresenham.steps;
	bresenham.x0 = bresenham.x;
	bresenham.y0 = bresenham.y;
	while (i < bresenham.steps)
	{
		if (data->map[ft_abs((int)bresenham.x0) / COEF][ft_abs((int)bresenham.y0) / COEF] == '1')
		{
			ray->dstx = bresenham.x0 / COEF;
			ray->dsty = bresenham.y0 / COEF;
			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));
		}
		if (mode == 1)
		{
			my_mlx_pixel_put(data, (int)bresenham.x0, (int)bresenham.y0, 0x00FFFFFF);
		}
		if (wall_around(data, bresenham.x0, bresenham.y0) == true)
		{
			bresenham.x0 += bresenham.xinc / WALL_ACCURACY;
			bresenham.y0 += bresenham.yinc / WALL_ACCURACY;
		}
		else
		{
			bresenham.x0 += bresenham.xinc;
			bresenham.y0 += bresenham.yinc;
		}
		i++;
	}
	ray->dstx = bresenham.x0 / COEF;
	ray->dsty = bresenham.y0 / COEF;
	return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->ry, 2)));
}
