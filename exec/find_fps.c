/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:28:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 12:11:33 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	find_lowest_value(double *tab, int size)
{
	int		i;
	double	lowest;

	i = 0;
	lowest = tab[0];
	while (i < size)
	{
		if (tab[i] < lowest)
			lowest = tab[i];
		i++;
	}
	return (lowest);
}

double	get_fps_average(t_data *data)
{
	int		i;
	double	sum;

	i = 0;
	sum = 0;
	while (i < FPS)
	{
		sum += data->last_fps[i];
		i++;
	}
	return (sum / FPS);
}

double	find_highest_value(double *tab, int size)
{
	int		i;
	double	highest;

	i = 0;
	highest = tab[0];
	while (i < size)
	{
		if (tab[i] > highest)
			highest = tab[i];
		i++;
	}
	return (highest);
}
