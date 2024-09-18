/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:59 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 16:05:04 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	calculate_distance(double x0, double y0, double xo, double yo)
{
	return (sqrt(pow(x0 - xo, 2) + pow(y0 - yo, 2)));
}

int	is_out_of_bounds(int map_x, int map_y)
{
	return (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT);
}

int	is_wall_hit(char **map, int map_x, int map_y)
{
	return (map[map_y][map_x] == '1' || map[map_y][map_x] == '2');
}

void	update_ray_destination(t_ray *ray, double x0, double y0)
{
	ray->dstx = x0 / COEF;
	ray->dsty = y0 / COEF;
}

void	init_bresenham(t_bresenham *bresenham, t_ray *ray, int wall_accuracy)
{
	bresenham->x0 = ray->xo;
	bresenham->y0 = ray->yo;
	bresenham->xinc = cos(ray->ra) / wall_accuracy;
	bresenham->yinc = sin(ray->ra) / wall_accuracy;
}
