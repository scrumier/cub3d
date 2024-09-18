/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:36:37 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/18 11:29:17 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	calculate_texture_offset(int i, double line_height, int texture_height)
{
	return ((i / line_height) * texture_height);
}

int	calculate_tex_x(t_ray *ray, int wall_face, int texture_width)
{
	if (wall_face == 'e')
		return (texture_width - (int)((ray->dstx - \
				floor(ray->dstx)) * texture_width) - 1);
	else if (wall_face == 'w')
		return ((int)((ray->dstx - floor(ray->dstx)) * \
				texture_width));
	else if (wall_face == 's')
		return (texture_width - (int)((ray->dsty - \
				floor(ray->dsty)) * texture_width) - 1);
	else if (wall_face == 'n')
		return ((int)((ray->dsty - floor(ray->dsty)) * \
				texture_width));
	return (0);
}

void	draw_texture_pixel(t_data *data, t_ray *ray, t_draw_wall draw_wall, \
		t_texture *texture)
{
	double	texture_offset;
	int		tex_x;
	int		texture_color;

	tex_x = 0;
	texture_color = 0;
	texture_offset = 0;
	texture_offset = calculate_texture_offset(draw_wall.i, \
					draw_wall.line_height, texture->height);
	tex_x = calculate_tex_x(ray, draw_wall.wall_face, texture->width);
	texture_color = get_texture_color(texture, texture_offset, tex_x);
	texture_color = darken_color(texture_color, \
					data->ray_len[draw_wall.ray_nbr], RENDER_DISTANCE);
	my_mlx_pixel_put(data, draw_wall.ray_nbr, draw_wall.i + \
					draw_wall.line_start, texture_color);
}

void	render_wall_texture(t_data *data, t_ray *ray, int ray_nbr, \
							t_line_3d line)
{
	int			i;
	int			wall_face;
	int			texture_index;
	t_texture	*texture;
	t_draw_wall	draw_wall;

	texture_index = find_ray_texture(data, ray);
	if (ray->dstx >= 0 && ray->dstx < data->mapx && ray->dsty >= 0 \
			&& ray->dsty < data->mapy)
		if (data->map[(int)ray->dsty][(int)ray->dstx] == '2')
			texture_index = (int)DOOR;
	wall_face = find_wall_facing(data, ray);
	texture = &data->texture[texture_index][data->animated_texture_index \
				% texture_array_len(data->texture[texture_index])];
	i = -1;
	while (++i < line.line_height)
	{
		draw_wall.i = i;
		draw_wall.wall_face = wall_face;
		draw_wall.ray_nbr = ray_nbr;
		draw_wall.line_height = line.line_height;
		draw_wall.line_start = line.line_start;
		if (!(ray_nbr < data->mapx * COEF && i + line.line_start < \
				data->mapy * COEF))
			draw_texture_pixel(data, ray, draw_wall, texture);
	}
}
