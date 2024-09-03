/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:47:05 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/03 17:19:39 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double find_cube_center_Y(t_data *data, double y)
{
	int i = 0;

	while (i < data->mapY)
	{
		if (y < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

double find_cube_center_X(t_data *data, double x)
{
	int i = 0;

	while (i < data->mapX)
	{
		if (x < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

int find_closest_to_05(double x, double y)
{
	double delta_x = ft_dabs(x - 0.5);
	double delta_y = ft_dabs(y - 0.5);

	if (delta_x < delta_y)
		return (0);
	return (1);
}

int	find_wall_facing(t_data *data, t_ray *ray)
{
	(void)data;
	t_coord center = {find_cube_center_X(data, ray->dstx), find_cube_center_Y(data, ray->dsty)};
	double angle = atan2(center.y - ray->dsty, center.x - ray->dstx);
	angle += PI / 4;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	if (angle > 0 + PI / BEAM_WIDTH && angle < PI / 2 - PI / BEAM_WIDTH)
		return ('n');
	if (angle > PI / 2 + PI / BEAM_WIDTH && angle < PI - PI / BEAM_WIDTH)
		return ('e');
	if (angle > PI + PI / BEAM_WIDTH && angle < 3 * PI / 2 - PI / BEAM_WIDTH)
		return ('s');
	if (angle > 3 * PI / 2 + PI / BEAM_WIDTH && angle < 2 * PI - PI / BEAM_WIDTH)
		return ('w');
	return (0);
}

int	find_ray_texture(t_data *data, t_ray *ray)
{
	int face = find_wall_facing(data, ray);

	if (face == 'n') // north
		return (0);
	else if (face == 's') // south
		return (1);
	else if (face == 'e') // east
		return (2);
	else if (face == 'w') // west
		return (3);
	else if (face == 'd') // door
	{
		return (5);
	}
	return (4); // beam
}
