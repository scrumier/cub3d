/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/16 10:33:21 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_texture_color(t_texture *texture, double texture_offset, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)texture_offset;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
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

void	initialize_ray_parameters(t_ray *ray, t_data *data, int *total_rays, \
									double *ray_angle)
{
	ray->ra = data->player->player_angle - (FOV / 2) * PI / 180;
	ray->dof = 0;
	*total_rays = RAYS;
	*ray_angle = find_angle(*total_rays);
}

void	draw_player_on_minimap(t_data *data)
{
	t_coord	coord;

	coord.x = data->player->x * COEF;
	coord.y = data->player->y * COEF;
	print_minimap(data, 1);
	draw_square(data, coord, COEF, 0x00FF00);
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

void	render_ceiling_and_floor(t_data *data, int ray_nbr, \
								double line_height, double line_start)
{
	int	i;
	int	ceil_color;
	int	floor_color;

	i = 0;
	while (i < line_start)
	{
		ceil_color = darken_color(data->ceiling_color, i, HEIGHT);
		if (!(ray_nbr < data->mapX * COEF && i < data->mapY * COEF))
			my_mlx_pixel_put(data, ray_nbr, i, ceil_color);
		i++;
	}
	i = line_start + line_height;
	while (i < HEIGHT)
	{
		//printf("data->mapX = %i\ndata->mapY = %i\n", data->mapX, data->mapY);

		floor_color = darken_color(data->floor_color, HEIGHT - i, HEIGHT);
		if (!(ray_nbr < data->mapX * COEF && i < data->mapY * COEF))
			my_mlx_pixel_put(data, ray_nbr, i, floor_color);
		i++;
	}
}

double	calculate_texture_offset(int i, double line_height, int texture_height)
{
	return ((i / line_height) * texture_height);
}

int	calculate_tex_x(t_ray *ray, int wall_face, int texture_width)
{
	if (wall_face == 'e')
		return (texture_width - (int)((ray->dstx - floor(ray->dstx)) * texture_width) - 1);
	else if (wall_face == 'w')
		return ((int)((ray->dstx - floor(ray->dstx)) * texture_width));
	else if (wall_face == 's')
		return (texture_width - (int)((ray->dsty - floor(ray->dsty)) * texture_width) - 1);
	else if (wall_face == 'n')
		return ((int)((ray->dsty - floor(ray->dsty)) * texture_width));
	return (0);
}


void	draw_texture_pixel(t_data *data, t_ray *ray, t_draw_wall draw_wall, t_texture *texture)
{
	double texture_offset;
	int tex_x, texture_color;

	texture_offset = calculate_texture_offset(draw_wall.i, draw_wall.line_height, texture->height);
	tex_x = calculate_tex_x(ray, draw_wall.wall_face, texture->width);
	texture_color = get_texture_color(texture, texture_offset, tex_x);
	texture_color = darken_color(texture_color, data->ray_len[draw_wall.ray_nbr], RENDER_DISTANCE);
	my_mlx_pixel_put(data, draw_wall.ray_nbr, draw_wall.i + draw_wall.line_start, texture_color);
}

void	render_wall_texture(t_data *data, t_ray *ray, int ray_nbr, double line_height, double line_start)
{
	int			i;
	int			wall_face;
	int			texture_index;
	t_texture	*texture;
	t_draw_wall	draw_wall;

	texture_index = find_ray_texture(data, ray);
	if (ray->dstx >= 0 && ray->dstx < data->mapX && ray->dsty >= 0 && ray->dsty < data->mapY)
	{
		if (data->map[(int)ray->dstx][(int)ray->dsty] == '2')
		texture_index = 5;
	}
	wall_face = find_wall_facing(data, ray);
	if (texture_index != 4)
		texture = &data->texture[texture_index][data->animated_texture_index];
	else
		texture = &data->texture[texture_index][0];
	
	i = 0;
	while (i < line_height)
	{
		draw_wall.i = i;
		draw_wall.wall_face = wall_face;
		draw_wall.ray_nbr = ray_nbr;
		draw_wall.line_height = line_height;
		draw_wall.line_start = line_start;
		if (!(ray_nbr < data->mapX * COEF && i + line_start < data->mapY * COEF))
			draw_texture_pixel(data, ray, draw_wall, texture);
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
		data->ray_len[ray_nbr] = draw_and_correct_ray(ray, data, WALL_ACCURACY);
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
