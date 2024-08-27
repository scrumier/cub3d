/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:21:06 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/27 13:04:32 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	handle_keypressed(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (key == KEY_F)
	{
		data->flash_light = !data->flash_light;
		print_minimap(data, 3);
	}
	if (key == KEY_W)
		data->move->forward = true;
	if (key == KEY_S)
		data->move->backward = true;
	if (key == KEY_A)
		data->move->turn_left = true;
	if (key == KEY_D)
		data->move->turn_right = true;
	return (0);
}

int	handle_keyrelease(int key, t_data *data)
{
	if (key == KEY_W)
		data->move->forward = false;
	if (key == KEY_S)
		data->move->backward = false;
	if (key == KEY_A)
		data->move->turn_left = false;
	if (key == KEY_D)
		data->move->turn_right = false;
	return (0);
}
