/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:36:06 by scrumier          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/09/16 16:31:24 by scrumier         ###   ########.fr       */
=======
/*   Updated: 2024/09/16 13:03:51 by scrumier         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_tab(double *tab)
{
	int	i;

	i = 0;
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
	int	j;
	int	i;
	t_coord coord;

	i = 0;
	j = 0;
	while (i < data->mapX)
	{
		j = 0;
		while (j < data->mapY)
		{
			coord.x = i * COEF;
			coord.y = j * COEF;
			if ((data->map[j][i] == '1' || data->map[j][i] == '2') && mode == 2)
				draw_square(data, coord, COEF, 0x00000000);
			else if ((data->map[j][i] == '0' || ft_isalpha(data->map[j][i])) && mode == !data->flash_light)
				draw_square(data, coord, COEF, 0x00A9A9A9);
			else if (data->map[j][i] == '0' && mode == 3)
				draw_square(data, coord, COEF, 0x00000000);
			j++;
		}
		i++;
	}
}

double	find_angle(int total_rays)
{
	double	rad;

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
	if (x - (int)x >= 0.4)
		return ((int)x + 1);
	return ((int)x);
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	print_map(char **map)
{
	int	i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		i++;
	}
}
