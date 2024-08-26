/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:26:45 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 14:49:31 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int blend_colors(unsigned int color, unsigned int color_left, unsigned int color_right, unsigned int color_up, unsigned int color_down)
{
	int r = 0, g = 0, b = 0;

	r += (color >> 16) & 0xFF;
	g += (color >> 8) & 0xFF;
	b += color & 0xFF;
	r += (color_left >> 16) & 0xFF;
	g += (color_left >> 8) & 0xFF;
	b += color_left & 0xFF;
	r += (color_right >> 16) & 0xFF;
	g += (color_right >> 8) & 0xFF;
	b += color_right & 0xFF;
	r += (color_up >> 16) & 0xFF;
	g += (color_up >> 8) & 0xFF;
	b += color_up & 0xFF;
	r += (color_down >> 16) & 0xFF;
	g += (color_down >> 8) & 0xFF;
	b += color_down & 0xFF;
	r /= 5;
	g /= 5;
	b /= 5;

	return (r << 16) | (g << 8) | b;
}

unsigned int get_pixel_color(t_data *data, int x, int y)
{
	char *dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	return *(unsigned int *)dst;
}

void set_pixel_color(t_data *data, int x, int y, unsigned int color)
{
	char *dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int color_difference(unsigned int color1, unsigned int color2)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	return abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2);
}

void apply_custom_antialiasing(t_data *data)
{
	for (int y = 1; y < HEIGHT - 1; y++) {
		for (int x = 1; x < WIDTH - 1; x++) {
			unsigned int color = get_pixel_color(data, x, y);
			unsigned int color_left = get_pixel_color(data, x - 1, y);
			unsigned int color_right = get_pixel_color(data, x + 1, y);
			unsigned int color_up = get_pixel_color(data, x, y - 1);
			unsigned int color_down = get_pixel_color(data, x, y + 1);
			if (color_difference(color, color_left) > THRESHOLD ||
				color_difference(color, color_right) > THRESHOLD ||
				color_difference(color, color_up) > THRESHOLD ||
				color_difference(color, color_down) > THRESHOLD) {
				unsigned int blended_color = blend_colors(color, color_left, color_right, color_up, color_down);
				set_pixel_color(data, x, y, blended_color);
			}
		}
	}
}