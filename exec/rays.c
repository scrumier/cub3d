/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 16:39:28 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initialize_ray_parameters(t_ray *ray, t_data *data, int *total_rays, \
									double *ray_angle)
{
	ray->ra = data->player->player_angle - (FOV / 2) * PI / 180;
	ray->dof = 0;
	*total_rays = RAYS;
	*ray_angle = find_angle(*total_rays);
}

double	correct_ray_angle(double ray_angle, double player_angle)
{
	double	corrected_angle;

	corrected_angle = ray_angle - player_angle;
	if (corrected_angle < 0)
		corrected_angle += 2 * PI;
	if (corrected_angle > 2 * PI)
		corrected_angle -= 2 * PI;
	return (corrected_angle);
}

double	draw_and_correct_ray(t_ray *ray, t_data *data, \
								int wall_accuracy)
{
	double	ray_len;
	double	corrected_angle;

	ray_len = draw_line(ray, data, 1, wall_accuracy);
	corrected_angle = correct_ray_angle(ray->ra, data->player->player_angle);
	return (ray_len * cos(corrected_angle));
}

void	parse_rays(t_data *data)
{
	t_ray	ray;
	double	ray_angle;
	int		total_rays;

	initialize_ray_parameters(&ray, data, &total_rays, &ray_angle);
	draw_player_on_minimap(data);
	cast_rays(data, &ray, total_rays, ray_angle);
}
