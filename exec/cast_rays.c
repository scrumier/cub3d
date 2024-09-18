/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:03 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 16:32:17 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	render_ceiling_and_floor(t_data *data, int ray_nbr, \
								double line_height, double line_start)
{
	int	i;
	int	ceil_color;
	int	floor_color;

	i = 0;
	while (i < line_start)
	{
		ceil_color = darken_color(data->ceiling_color, i, HEIGHT / 1.5);
		if (!(ray_nbr < data->mapx * COEF && i < data->mapy * COEF))
			my_mlx_pixel_put(data, ray_nbr, i, ceil_color);
		i++;
	}
	i = line_start + line_height;
	while (i < HEIGHT)
	{
		floor_color = darken_color(data->floor_color, HEIGHT - i, HEIGHT / 1.5);
		if (!(ray_nbr < data->mapx * COEF && i < data->mapy * COEF))
			my_mlx_pixel_put(data, ray_nbr, i, floor_color);
		i++;
	}
}

static void	calculate_ray_position(t_data *data, t_ray *ray)
{
	ray->rx = data->player->x * COEF + (COEF / 2);
	ray->ry = data->player->y * COEF + (COEF / 2);
	ray->xo = ray->rx + 1;
	ray->yo = ray->ry + 1;
}

static void	adjust_ray_direction(t_ray *ray, double cos_val, double sin_val)
{
	ray->rx += RENDER_DISTANCE * cos_val;
	ray->ry += RENDER_DISTANCE * sin_val;
}

static void	render_ray(t_data *data, t_ray *ray, int ray_nbr, \
			t_line_3d line)
{
	render_wall_texture(data, ray, ray_nbr, line);
	render_ceiling_and_floor(data, ray_nbr, line.line_height, line.line_start);
}

void	cast_rays(t_data *data, t_ray *ray, int total_rays, double ray_angle)
{
	int			ray_nbr;
	t_line_3d	line;
	double		cos_val;
	double		sin_val;

	ray_nbr = 0;
	while (ray_nbr < total_rays)
	{
		cos_val = cos(ray->ra);
		sin_val = sin(ray->ra);
		calculate_ray_position(data, ray);
		adjust_ray_direction(ray, cos_val, sin_val);
		data->ray_len[ray_nbr] = draw_and_correct_ray(ray, data, WALL_ACCURACY);
		line.line_height = HEIGHT * COEF3D / data->ray_len[ray_nbr];
		line.line_start = (WIDTH / 2) - (line.line_height / 2);
		render_ray(data, ray, ray_nbr, line);
		ray->ra += ray_angle;
		ray_nbr++;
	}
}
