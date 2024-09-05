/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 12:26:37 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// get texture color
int	get_texture_color(t_texture *texture, double texture_offset, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)texture_offset;
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= texture->width) tex_x = texture->width - 1;
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= texture->height) tex_y = texture->height - 1;
	color = *(int *)(texture->addr + (tex_y * texture->line_len + tex_x * \
			(texture->bpp / 8)));
	return (color);
}

int	darken_color(int color, double distance, double max_distance)
{
	double	factor;
	t_rgb	rgb;

	factor = 1.0 - (distance / max_distance);
	if (factor < 0.0)
		factor = 0.0;
	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	rgb.r *= factor;
	rgb.g *= factor;
	rgb.b *= factor;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}


void	initialize_ray_parameters(t_ray *ray, t_data *data, int *total_rays, double *ray_angle)
{
	ray->ra = data->player->player_angle - (FOV / 2) * PI / 180;
	ray->dof = 0;
	*total_rays = RAYS;
	*ray_angle = find_angle(*total_rays);
}

void	draw_player_on_minimap(t_data *data)
{
	print_minimap(data, 1);
	draw_square(data, data->player->x * COEF + (COEF / 2) - (PLAYER_SIZE / 2),
		data->player->y * COEF + (COEF / 2) - (PLAYER_SIZE / 2), PLAYER_SIZE, 0x0000FF00);
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

double	draw_and_correct_ray(t_ray *ray, t_data *data, int ray_nbr, int wall_accuracy)
{
	double	ray_len;
	double	corrected_angle;

	ray_len = draw_line(ray, data, 1, wall_accuracy);
	ray_nbr = RAYS;
	corrected_angle = correct_ray_angle(ray->ra, data->player->player_angle);
	return (ray_len * cos(corrected_angle));
}

void	render_ceiling_and_floor(t_data *data, int ray_nbr, double line_height, double line_start)
{
	int	i;

	i = 0;
	while (i < line_start)
	{
		if (!(ray_nbr < 150 && i < 150))
			my_mlx_pixel_put(data, ray_nbr, i, data->ceiling_color);
		i++;
	}
	i = line_start + line_height;
	while (i < HEIGHT)
	{
		if (!(ray_nbr < 150 && i < 150))
			my_mlx_pixel_put(data, ray_nbr, i, data->floor_color);
		i++;
	}
}

double	calculate_texture_offset(int i, double line_height, int texture_height)
{
	return ((i / line_height) * texture_height);
}

int	calculate_tex_x(t_ray *ray, int wall_face, int texture_width)
{
	if (wall_face == 'e' || wall_face == 'w')
		return ((int)((ray->dstx - floor(ray->dstx)) * texture_width));
	else
		return ((int)((ray->dsty - floor(ray->dsty)) * texture_width));
}

void	draw_texture_pixel(t_data *data, t_ray *ray, int ray_nbr, int i, double line_height, double line_start, t_texture *texture, int wall_face)
{
	double texture_offset;
	int tex_x, texture_color;

	texture_offset = calculate_texture_offset(i, line_height, texture->height);
	tex_x = calculate_tex_x(ray, wall_face, texture->width);
	texture_color = get_texture_color(texture, texture_offset, tex_x);
	texture_color = darken_color(texture_color, data->ray_len[ray_nbr], RENDER_DISTANCE);
	my_mlx_pixel_put(data, ray_nbr, i + line_start, texture_color);
}

void	render_wall_texture(t_data *data, t_ray *ray, int ray_nbr, double line_height, double line_start)
{
	int			i;
	int			wall_face;
	int			texture_index;
	t_texture	*texture;

	texture_index = find_ray_texture(data, ray);
	if (ray->dstx >= 0 && ray->dstx < data->mapX && ray->dsty >= 0 && ray->dsty < data->mapY)
	{
		if (data->map[(int)ray->dstx][(int)ray->dsty] == '2')
		texture_index = 5;
	}
	wall_face = find_wall_facing(data, ray);
	texture = &data->texture[texture_index];
	
	i = 0;
	while (i < line_height)
	{
		if (!(ray_nbr < 150 && i + line_start < 150))
			draw_texture_pixel(data, ray, ray_nbr, i, line_height, line_start, texture, wall_face);
		i++;
	}
}


void	cast_rays(t_data *data, t_ray *ray, int total_rays, double ray_angle)
{
	int		ray_nbr;
	double	line_height;
	double	line_start;

	ray_nbr = 0;
	while (ray_nbr < total_rays)
	{
		ray->rx = data->player->x * COEF + (COEF / 2);
		ray->ry = data->player->y * COEF + (COEF / 2);
		ray->xo = ray->rx + 1;
		ray->yo = ray->ry + 1;
		ray->rx += RENDER_DISTANCE * cos(ray->ra);
		ray->ry += RENDER_DISTANCE * sin(ray->ra);
		data->ray_len[ray_nbr] = draw_and_correct_ray(ray, data, ray_nbr, WALL_ACCURACY);
		line_height = HEIGHT * COEF3D / data->ray_len[ray_nbr];
		line_start = (WIDTH / 2) - (line_height / 2);
		render_wall_texture(data, ray, ray_nbr, line_height, line_start);
		render_ceiling_and_floor(data, ray_nbr, line_height, line_start);
		ray->ra += ray_angle;
		ray_nbr++;
	}
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
