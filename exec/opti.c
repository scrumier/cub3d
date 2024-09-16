/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:50:35 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/16 10:56:05 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	wall_around_01(t_data *data, double x, double y)
{
	if (data->map[double_to_int(y)][double_to_int(x)] == '1')
		return (true);
	if (data->map[double_to_int(y + 0.1)][double_to_int(x)] == '1')
		return (true);
	if (data->map[double_to_int(y + 0.1)][double_to_int(x + 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x + 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x - 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(y - 0.1)][double_to_int(x + 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(y - 0.1)][double_to_int(x)] == '1')
		return (true);
	if (data->map[double_to_int(y - 0.1)][double_to_int(x - 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(y)][double_to_int(x - 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(y + 0.1)][double_to_int(x - 0.1)] == '1')
		return (true);
	return (false);
}

bool __attribute__((hot))	wall_around_05(t_data *data, double x, double y)
{
	x /= COEF;
	y /= COEF;
	if (data->map[(int)y][(int)x] == '1')
		return (true);
	if (data->map[(int)(y + 0.05)][(int)x] == '1')
		return (true);
	if (data->map[(int)(y + 0.05)][(int)(y + 0.05)] == '1')
		return (true);
	if (data->map[(int)y][(int)(y + 0.05)] == '1')
		return (true);
	if (data->map[(int)y][(int)(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)(y - 0.05)][(int)(y + 0.05)] == '1')
		return (true);
	if (data->map[(int)(y - 0.05)][(int)x] == '1')
		return (true);
	if (data->map[(int)(y - 0.05)][(int)(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)y][(int)(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)(y + 0.05)][(int)(y - 0.05)] == '1')
		return (true);
	return (false);
}
