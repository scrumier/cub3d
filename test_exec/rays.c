/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 11:18:00 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	parse_rays(t_data *data)
{
	t_ray ray;
	int ray_nbr;
	double ray_angle;
	int total_rays;

	ray.ra = data->player->player_angle - (FOV / 2) * PI / 180;
	ray.dof = 0;
	ray_nbr = 0;
	total_rays = RAYS;
	double last_fps = get_fps_average(data);
	if (FPS_OPTI != 0)
		total_rays = optimize_fps(last_fps);
	ray_angle = find_angle(total_rays);
	print_minimap(data, 1);
	draw_square(data, data->player->x * COEF + (COEF / 2) - (PLAYER_SIZE / 2), data->player->y * COEF + (COEF / 2) - (PLAYER_SIZE / 2), PLAYER_SIZE, 0x0000FF00);
	while (ray_nbr < total_rays)
	{
		ray.rx = data->player->x * COEF + (COEF / 2);
		ray.ry = data->player->y * COEF + (COEF / 2);
		ray.xo = ray.rx + 1;
		ray.yo = ray.ry + 1;
		ray.rx += RENDER_DISTANCE * cos(ray.ra);
		ray.ry += RENDER_DISTANCE * sin(ray.ra);
		double corrected_angle = ray.ra - data->player->player_angle;
		if (corrected_angle < 0)
			corrected_angle += 2 * PI;
		if (corrected_angle > 2 * PI)
			corrected_angle -= 2 * PI;
		data->ray_len[ray_nbr] = draw_line(&ray, data, 1);
		data->ray_len[ray_nbr] *= cos(corrected_angle);
		double line_height = HEIGHT * COEF3D / data->ray_len[ray_nbr];
		double line_start = (WIDTH / 2) - (line_height / 2);
		int i = 0;
		ray.color = find_ray_color(data, &ray);
		while (i < line_height)
		{
			if (ray_nbr * (double)(WIDTH / total_rays) < WIDTH && i + line_start < HEIGHT)
			{
				int n = -1;
				while (++n < (double)(WIDTH / total_rays)) {
					if (!(n + ray_nbr * (double)(WIDTH / total_rays) < 150 && i + line_start < 150))
						my_mlx_pixel_put(data, ray_nbr * (double) (WIDTH / total_rays) + n, i + line_start, ray.color);
				}
			}
			i++;
		}
		ray.ra += ray_angle;
		ray_nbr++;
	}
}
