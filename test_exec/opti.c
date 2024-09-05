/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:50:35 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 10:17:18 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	wall_around_01(t_data *data, double x, double y)
{
	if (data->map[double_to_int(x)][double_to_int(y)] == '1')
		return (true);
	if (data->map[double_to_int(x + 0.1)][double_to_int(y)] == '1')
		return (true);
	if (data->map[double_to_int(x + 0.1)][double_to_int(y + 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y + 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(x - 0.1)][double_to_int(y + 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(x - 0.1)][double_to_int(y)] == '1')
		return (true);
	if (data->map[double_to_int(x - 0.1)][double_to_int(y - 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.1)] == '1')
		return (true);
	if (data->map[double_to_int(x + 0.1)][double_to_int(y - 0.1)] == '1')
		return (true);
	return (false);
}

bool __attribute__((hot))	wall_around_05(t_data *data, double x, double y)
{
	x /= COEF;
	y /= COEF;
	if (data->map[double_to_int(x)][double_to_int(y)] == '1')
		return (true);
	if (data->map[double_to_int(x + 0.05)][double_to_int(y)] == '1')
		return (true);
	if (data->map[double_to_int(x + 0.05)][double_to_int(y + 0.05)] == '1')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y + 0.05)] == '1')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.05)] == '1')
		return (true);
	if (data->map[double_to_int(x - 0.05)][double_to_int(y + 0.05)] == '1')
		return (true);
	if (data->map[double_to_int(x - 0.05)][double_to_int(y)] == '1')
		return (true);
	if (data->map[double_to_int(x - 0.05)][double_to_int(y - 0.05)] == '1')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.05)] == '1')
		return (true);
	if (data->map[double_to_int(x + 0.05)][double_to_int(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)x ][(int)y ] == '1')
		return (true);
	if (data->map[(int)(x + 0.05)][(int)y ] == '1')
		return (true);
	if (data->map[(int)(x + 0.05)][(int)(y + 0.05)] == '1')
		return (true);
	if (data->map[(int)x ][(int)(y + 0.05)] == '1')
		return (true);
	if (data->map[(int)x ][(int)(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)(x - 0.05)][(int)(y + 0.05)] == '1')
		return (true);
	if (data->map[(int)(x - 0.05)][(int)y ] == '1')
		return (true);
	if (data->map[(int)(x - 0.05)][(int)(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)x ][(int)(y - 0.05)] == '1')
		return (true);
	if (data->map[(int)(x + 0.05)][(int)(y - 0.05)] == '1')
		return (true);
	return (false);
}

int	optimize_fps(double last_fps)
{
	if (FPS_OPTI == 1)
	{
		if (last_fps < 60)
			return (WALL_ACCURACY);
		else if (last_fps < 80)
			return (WALL_ACCURACY * 2);
		else if (last_fps < 100)
			return (WALL_ACCURACY * 4);
		else if (last_fps < 120)
			return (WALL_ACCURACY * 8);
		else
			return (WALL_ACCURACY * 16);
	}
	return (WALL_ACCURACY);
}
