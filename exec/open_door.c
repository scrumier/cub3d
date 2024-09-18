/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:37:05 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 14:59:56 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	door_around(t_data *data, double x, double y)
{
	if (data->map[double_to_int(y)][double_to_int(x)] == '2')
		return (true);
	if (data->map[double_to_int(y + 0.5)][double_to_int(x)] == '2')
		return (true);
	if (data->map[double_to_int(y + 0.5)][double_to_int(x + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(y - 0.5)][double_to_int(x + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(y - 0.5)][double_to_int(x)] == '2')
		return (true);
	if (data->map[double_to_int(y - 0.5)][double_to_int(x - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(y + 0.5)][double_to_int(x - 0.5)] == '2')
		return (true);
	return (false);
}

bool	closed_door_around(t_data *data, double x, double y)
{
	if (data->map[double_to_int(y)][double_to_int(x)] == '3')
		return (true);
	if (data->map[double_to_int(y + 0.5)][double_to_int(x)] == '3')
		return (true);
	if (data->map[double_to_int(y + 0.5)][double_to_int(x + 0.5)] == '3')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x + 0.5)] == '3')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '3')
		return (true);
	if (data->map[double_to_int(y - 0.5)][double_to_int(x + 0.5)] == '3')
		return (true);
	if (data->map[double_to_int(y - 0.5)][double_to_int(x)] == '3')
		return (true);
	if (data->map[double_to_int(y - 0.5)][double_to_int(x - 0.5)] == '3')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '3')
		return (true);
	if (data->map[double_to_int(y + 0.5)][double_to_int(x - 0.5)] == '3')
		return (true);
	return (false);
}

void	open_door(t_data *data)
{
	double	x;
	double	y;

	x = data->player->x;
	y = data->player->y;
	if (data->map[double_to_int(y)][double_to_int(x)] == '2')
		data->map[double_to_int(y)][double_to_int(x)] = '3';
	if (data->map[double_to_int(y + 0.5)][double_to_int(x)] == '2')
		data->map[double_to_int(y + 0.5)][double_to_int(x)] = '3';
	if (data->map[double_to_int(y + 0.5)][double_to_int(x + 0.5)] == '2')
		data->map[double_to_int(y + 0.5)][double_to_int(x + 0.5)] = '3';
	if (data->map[double_to_int(y)][double_to_int(x + 0.5)] == '2')
		data->map[double_to_int(y)][double_to_int(x + 0.5)] = '3';
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '2')
		data->map[double_to_int(y)][double_to_int(x - 0.5)] = '3';
	if (data->map[double_to_int(y - 0.5)][double_to_int(x + 0.5)] == '2')
		data->map[double_to_int(y - 0.5)][double_to_int(x + 0.5)] = '3';
	if (data->map[double_to_int(y - 0.5)][double_to_int(x)] == '2')
		data->map[double_to_int(y - 0.5)][double_to_int(x)] = '3';
	if (data->map[double_to_int(y - 0.5)][double_to_int(x - 0.5)] == '2')
		data->map[double_to_int(y - 0.5)][double_to_int(x - 0.5)] = '3';
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '2')
		data->map[double_to_int(y)][double_to_int(x - 0.5)] = '3';
	if (data->map[double_to_int(y + 0.5)][double_to_int(x - 0.5)] == '2')
		data->map[double_to_int(y + 0.5)][double_to_int(x - 0.5)] = '3';
}

void	close_door(t_data *data)
{
	double	x;
	double	y;

	x = data->player->x;
	y = data->player->y;
	if (data->map[double_to_int(y)][double_to_int(x)] == '3')
		data->map[double_to_int(y)][double_to_int(x)] = '2';
	if (data->map[double_to_int(y + 0.5)][double_to_int(x)] == '3')
		data->map[double_to_int(y + 0.5)][double_to_int(x)] = '2';
	if (data->map[double_to_int(y + 0.5)][double_to_int(x + 0.5)] == '3')
		data->map[double_to_int(y + 0.5)][double_to_int(x + 0.5)] = '2';
	if (data->map[double_to_int(y)][double_to_int(x + 0.5)] == '3')
		data->map[double_to_int(y)][double_to_int(x + 0.5)] = '2';
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '3')
		data->map[double_to_int(y)][double_to_int(x - 0.5)] = '2';
	if (data->map[double_to_int(y - 0.5)][double_to_int(x + 0.5)] == '3')
		data->map[double_to_int(y - 0.5)][double_to_int(x + 0.5)] = '2';
	if (data->map[double_to_int(y - 0.5)][double_to_int(x)] == '3')
		data->map[double_to_int(y - 0.5)][double_to_int(x)] = '2';
	if (data->map[double_to_int(y - 0.5)][double_to_int(x - 0.5)] == '3')
		data->map[double_to_int(y - 0.5)][double_to_int(x - 0.5)] = '2';
	if (data->map[double_to_int(y)][double_to_int(x - 0.5)] == '3')
		data->map[double_to_int(y)][double_to_int(x - 0.5)] = '2';
	if (data->map[double_to_int(y + 0.5)][double_to_int(x - 0.5)] == '3')
		data->map[double_to_int(y + 0.5)][double_to_int(x - 0.5)] = '2';
}
