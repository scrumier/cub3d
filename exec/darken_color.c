/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darken_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:33:57 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/18 11:46:12 by mwojtasi         ###   ########.fr       */
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
