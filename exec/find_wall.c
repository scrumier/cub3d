/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:08:59 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 16:11:02 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	find_cube_center_y(t_data *data, double y)
{
	int	i;

	i = 0;
	while (i < data->mapy)
	{
		if (y < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

double	find_cube_center_x(t_data *data, double x)
{
	int	i;

	i = 0;
	while (i < data->mapx)
	{
		if (x < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

int	find_closest_to_05(double x, double y)
{
	double	delta_x;
	double	delta_y;

	delta_x = ft_dabs(x - 0.5);
	delta_y = ft_dabs(y - 0.5);
	if (delta_x < delta_y)
		return (0);
	return (1);
}

bool	is_wall(t_data *data, double x, double y)
{
	if (is_out_of_the_map(data, x, y))
		return (true);
	return (data->map[double_to_int(y)][double_to_int(x)] == '1' || \
			data->map[double_to_int(y)][double_to_int(x)] == '2');
}
