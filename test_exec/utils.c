/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:36:06 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/27 13:05:05 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_tab(double *tab)
{
	int i = 0;

	while (i < RAYS)
	{
		printf("Ray[%i] = %f\n", i, tab[i]);
		i++;
	}
}

int deg_to_rad(int deg)
{
	return (deg * PI / 180);
}

void	print_minimap(t_data *data, int mode)
{
	int i = 0;
	int j = 0;

	// i want the minimap to be displayed in the top left corner
	// walls are displayed in black
	// player is displayed in blue
	// empty space is displayed in gray black
	// i want the minimap to be 100x100 always (even if the map is bigger)
	// use COEF to scale the minimap
	// use PLAYER_SIZE to display the player

	while (i < data->mapX)
	{
		j = 0;
		while (j < data->mapY)
		{
			if (data->map[i][j] == '1' && mode == 2)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00000000);
			else if (data->map[i][j] == '0' && mode == !data->flash_light)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00A9A9A9);
			else if (data->map[i][j] == '0' && mode == 3)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00000000);
			j++;
		}
		i++;
	}
}

double	find_angle(int total_rays)
{
	double rad;

	rad = FOV * PI / 180;
	return (rad / total_rays);
}

double	ft_dabs(double d)
{
	if (d < 0)
		d = -d;
	return (d);
}

int	double_to_int(double x)
{
	if (x - (int)x > 0.5)
		return ((int)x + 1);
	return ((int)x);
}

int ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	print_map(char **map)
{
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
