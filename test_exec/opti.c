/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:50:35 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 11:14:32 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	wall_around(t_data *data, double x, double y)
{
	// if there is a wall around the player coordinates x and y
	if (data->map[double_to_int(x) / COEF][double_to_int(y) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x) / COEF][double_to_int(y) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x) / COEF][double_to_int(y + 1) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x + 1) / COEF][double_to_int(y + 1) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x - 1) / COEF][double_to_int(y) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x) / COEF][double_to_int(y - 1) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x - 1) / COEF][double_to_int(y - 1) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x - 1) / COEF][double_to_int(y + 1) / COEF] == '1')
		return (true);
	if (data->map[double_to_int(x + 1) / COEF][double_to_int(y - 1) / COEF] == '1')
		return (true);
	return (false);
}

int	optimize_fps(double last_fps)
{
	if (FPS_OPTI == 1)
	{
		if (last_fps < 20)
			return (RAYS / 8);
		else if (last_fps < 40)
			return (RAYS / 4);
		else if (last_fps < 60)
			return (RAYS);
		else
			return (RAYS * 2);
	}
	else if (FPS_OPTI == 2)
	{
		if (last_fps < 20)
			return (RAYS / 4);
		else if (last_fps < 40)
			return (RAYS / 2);
		else
			return (RAYS);
	}
	return (RAYS);
}
