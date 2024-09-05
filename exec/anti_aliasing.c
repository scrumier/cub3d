/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:26:45 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 12:51:13 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int	blend_colors(unsigned int color, t_color_antialiasing colors)
{
	t_rgb	rgb;

	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	rgb.r += (color >> 16) & 0xFF;
	rgb.g += (color >> 8) & 0xFF;
	rgb.b += color & 0xFF;
	rgb.r += (colors.color_left >> 16) & 0xFF;
	rgb.g += (colors.color_left >> 8) & 0xFF;
	rgb.b += colors.color_left & 0xFF;
	rgb.r += (colors.color_right >> 16) & 0xFF;
	rgb.g += (colors.color_right >> 8) & 0xFF;
	rgb.b += colors.color_right & 0xFF;
	rgb.r += (colors.color_up >> 16) & 0xFF;
	rgb.g += (colors.color_up >> 8) & 0xFF;
	rgb.b += colors.color_up & 0xFF;
	rgb.r += (colors.color_down >> 16) & 0xFF;
	rgb.g += (colors.color_down >> 8) & 0xFF;
	rgb.b += colors.color_down & 0xFF;
	rgb.r /= 5;
	rgb.g /= 5;
	rgb.b /= 5;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

unsigned int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	return (*(unsigned int *)dst);
}

void	set_pixel_color(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	color_difference(unsigned int color1, unsigned int color2)
{
	t_rgb	rgb1;
	t_rgb	rgb2;

	rgb1.r = (color1 >> 16) & 0xFF;
	rgb1.g = (color1 >> 8) & 0xFF;
	rgb1.b = color1 & 0xFF;
	rgb2.r = (color2 >> 16) & 0xFF;
	rgb2.g = (color2 >> 8) & 0xFF;
	rgb2.b = color2 & 0xFF;
	return (abs(rgb1.r - rgb2.r) + abs(rgb1.g - rgb2.g) + abs(rgb1.b - rgb2.b));
}

bool	get_color_difference(t_color_antialiasing colors, unsigned int color)
{
	if (color_difference(color, colors.color_left) > THRESHOLD || \
		color_difference(color, colors.color_right) > THRESHOLD || \
		color_difference(color, colors.color_up) > THRESHOLD || \
		color_difference(color, colors.color_down) > THRESHOLD)
		return (true);
	return (false);
}

void	apply_custom_antialiasing(t_data *data)
{
	t_color_antialiasing	colors;
	unsigned int			color;
	unsigned int			blended_color;
	int						x;
	int						y;

	y = 1;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (++x < WIDTH - 1)
		{
			color = get_pixel_color(data, x, y);
			colors.color_left = get_pixel_color(data, x - 1, y);
			colors.color_right = get_pixel_color(data, x + 1, y);
			colors.color_up = get_pixel_color(data, x, y - 1);
			colors.color_down = get_pixel_color(data, x, y + 1);
			if (get_color_difference(colors, color) == true)
			{
				blended_color = blend_colors(color, colors);
				set_pixel_color(data, x, y, blended_color);
			}
		}
		y++;
	}
}
