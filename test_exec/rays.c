/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/03 17:25:56 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// get texture color
int get_texture_color(t_texture *texture, double texture_offset, int tex_x)
{
	int tex_y = (int)texture_offset;

	if (tex_x < 0) tex_x = 0;
	if (tex_x >= texture->width) tex_x = texture->width - 1;

	if (tex_y < 0) tex_y = 0;
	if (tex_y >= texture->height) tex_y = texture->height - 1;

	int color = *(int *)(texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8)));

	return color;
}

void parse_rays(t_data *data)
{
	t_ray ray;
	int ray_nbr;
	double ray_angle;
	int total_rays;

	ray.ra = data->player->player_angle - (FOV / 2) * PI / 180;
	ray.dof = 0;
	ray_nbr = 0;
	total_rays = RAYS;
	int wall_accuracy = WALL_ACCURACY;
	double last_fps = get_fps_average(data);
	if (FPS_OPTI != 0)
		wall_accuracy = optimize_fps(last_fps);
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
		data->ray_len[ray_nbr] = draw_line(&ray, data, 1, wall_accuracy);
		data->ray_len[ray_nbr] *= cos(corrected_angle);
		double line_height = HEIGHT * COEF3D / data->ray_len[ray_nbr];
		double line_start = (WIDTH / 2) - (line_height / 2);
		int i = 0;
		int texture_index = find_ray_texture(data, &ray);
		if (data->map[(int)ray.dstx][(int)ray.dsty] == '2')
			texture_index = 5;
		int wall_face = find_wall_facing(data, &ray);
		t_texture *texture = &data->texture[texture_index];

		while (i < line_start)
		{
			if (!(ray_nbr < 150 && i < 150))
				my_mlx_pixel_put(data, ray_nbr, i, data->ceiling_color);
			i++;
		}
		i = 0;
		while (i < line_height)
		{
			if (!(ray_nbr < 150 && i + line_start < 150))
			{
				double texture_offset = (i / line_height) * texture->height;

				int tex_x;

				if (wall_face == 'e' || wall_face == 'w')
					tex_x = (int)((ray.dstx - floor(ray.dstx)) * texture->width);
				else
					tex_x = (int)((ray.dsty - floor(ray.dsty)) * texture->width);

				int texture_color = get_texture_color(texture, texture_offset, tex_x);
				my_mlx_pixel_put(data, ray_nbr, i + line_start, texture_color);
			}
			i++;
		}
		i = line_start + line_height;
		while (i < HEIGHT)
		{
			if (!(ray_nbr < 150 && i < 150))
				my_mlx_pixel_put(data, ray_nbr, i, data->floor_color);
			i++;
		}
		ray.ra += ray_angle;
		ray_nbr++;
	}
}