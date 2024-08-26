/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:28:49 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 10:51:43 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double find_lowest_value(double *tab, int size)
{
	int i = 0;
	double lowest = tab[0];

	while (i < size)
	{
		if (tab[i] < lowest)
			lowest = tab[i];
		i++;
	}
	return (lowest);
}

double get_fps_average(t_data *data)
{
	int i = 0;
	double sum = 0;

	while (i < FPS)
	{
		sum += data->last_fps[i];
		i++;
	}
	return (sum / FPS);
}

double find_highest_value(double *tab, int size)
{
	int i = 0;
	double highest = tab[0];

	while (i < size)
	{
		if (tab[i] > highest)
			highest = tab[i];
		i++;
	}
	return (highest);
}