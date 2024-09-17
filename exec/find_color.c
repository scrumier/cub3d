/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:47:05 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 15:45:07 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	find_cube_center_y(t_data *data, double y)
{
	int	i;

	i = 0;
	while (i < data->mapy)
	{
		if (y < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

double	find_cube_center_x(t_data *data, double x)
{
	int	i;

	i = 0;
	while (i < data->mapx)
	{
		if (x < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

int	find_closest_to_05(double x, double y)
{
	double	delta_x;
	double	delta_y;

	delta_x = ft_dabs(x - 0.5);
	delta_y = ft_dabs(y - 0.5);
	if (delta_x < delta_y)
		return (0);
	return (1);
}

double	adjust_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	get_wall_facing(double angle)
{
	if (angle > 0 + PI / BEAM_WIDTH && angle < PI / 2 - PI / BEAM_WIDTH)
		return ('n');
	if (angle > PI / 2 + PI / BEAM_WIDTH && angle < PI - PI / BEAM_WIDTH)
		return ('e');
	if (angle > PI + PI / BEAM_WIDTH && angle < 3 * PI / 2 - PI / BEAM_WIDTH)
		return ('s');
	if (angle > 3 * PI / 2 + PI / BEAM_WIDTH && angle < 2 * PI - PI / \
			BEAM_WIDTH)
		return ('w');
	return (0);
}

int	find_wall_facing(t_data *data, t_ray *ray)
{
	t_coord	center;
	double	angle;

	center.x = find_cube_center_x(data, ray->dstx);
	center.y = find_cube_center_y(data, ray->dsty);
	angle = atan2(center.y - ray->dsty, center.x - ray->dstx);
	angle += PI / 4;
	angle = adjust_angle(angle);
	return (get_wall_facing(angle));
}

int	find_ray_texture(t_data *data, t_ray *ray)
{
	int	face;

	face = find_wall_facing(data, ray);
	if (face == 'n')
		return (0);
	else if (face == 's')
		return (1);
	else if (face == 'e')
		return (2);
	else if (face == 'w')
		return (3);
	return (4);
}
