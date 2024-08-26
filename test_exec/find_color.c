/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:47:05 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 14:02:46 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double find_cube_center(double x)
{
	int i = 0;

	while (i < 10)
	{
		if (x >= i && x < i + 1)
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
	t_coord center = {find_cube_center(ray->dstx), find_cube_center(ray->dsty)};
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

int	find_ray_face(t_data *data, t_ray *ray)
{
	int face = find_wall_facing(data, ray);

	if (face == 'n') // purple
		return (0x00FF00FF);
	else if (face == 's') // red
		return (0x00FF0033);
	else if (face == 'e') // blue
		return (0x007777FF);
	else if (face == 'w') // green
		return (0x0044FF44);
	return (0x00000000);
}
