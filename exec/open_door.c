/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:37:05 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 12:22:10 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	door_around(t_data *data, double x, double y)
{
	if (data->map[double_to_int(x)][double_to_int(y)] == '2')
		return (true);
	if (data->map[double_to_int(x + 0.5)][double_to_int(y)] == '2')
		return (true);
	if (data->map[double_to_int(x + 0.5)][double_to_int(y + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x - 0.5)][double_to_int(y + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x - 0.5)][double_to_int(y)] == '2')
		return (true);
	if (data->map[double_to_int(x - 0.5)][double_to_int(y - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x + 0.5)][double_to_int(y - 0.5)] == '2')
		return (true);
	return (false);
}

void	open_door(t_data *data)
{
	double	x;
	double	y;

	x = data->player->x;
	y = data->player->y;
	if (data->map[double_to_int(x)][double_to_int(y)] == '2')
		data->map[double_to_int(x)][double_to_int(y)] = '0';
	if (data->map[double_to_int(x + 0.5)][double_to_int(y)] == '2')
		data->map[double_to_int(x + 0.5)][double_to_int(y)] = '0';
	if (data->map[double_to_int(x + 0.5)][double_to_int(y + 0.5)] == '2')
		data->map[double_to_int(x + 0.5)][double_to_int(y + 0.5)] = '0';
	if (data->map[double_to_int(x)][double_to_int(y + 0.5)] == '2')
		data->map[double_to_int(x)][double_to_int(y + 0.5)] = '0';
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x)][double_to_int(y - 0.5)] = '0';
	if (data->map[double_to_int(x - 0.5)][double_to_int(y + 0.5)] == '2')
		data->map[double_to_int(x - 0.5)][double_to_int(y + 0.5)] = '0';
	if (data->map[double_to_int(x - 0.5)][double_to_int(y)] == '2')
		data->map[double_to_int(x - 0.5)][double_to_int(y)] = '0';
	if (data->map[double_to_int(x - 0.5)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x - 0.5)][double_to_int(y - 0.5)] = '0';
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x)][double_to_int(y - 0.5)] = '0';
	if (data->map[double_to_int(x + 0.5)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x + 0.5)][double_to_int(y - 0.5)] = '0';
}
