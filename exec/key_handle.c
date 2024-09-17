/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:21:06 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 15:26:16 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_move(t_data *data, int key)
{
	if (key == KEY_W)
		data->move->forward = true;
	if (key == KEY_S)
		data->move->backward = true;
	if (key == KEY_LEFT)
		data->move->turn_left = true;
	if (key == KEY_RIGHT)
		data->move->turn_right = true;
	if (key == KEY_A)
		data->move->go_left = true;
	if (key == KEY_D)
		data->move->go_right = true;
}

int	handle_keypressed(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		free_all(data);
		exit(0);
	}
	set_move(data, key);
	if (key == KEY_E)
	{
		if (door_around(data, data->player->x, data->player->y))
			open_door(data);
		else if (closed_door_around(data, data->player->x, data->player->y))
		{
			close_door(data);
			if (is_wall(data, data->player->x, data->player->y) \
			|| check_x_collision(data, data->player->x, data->player->y, 0.2) \
			|| check_y_collision(data, data->player->x, data->player->y, 0.2))
				open_door(data);
		}
	}
	return (0);
}

int	handle_keyrelease(int key, t_data *data)
{
	if (key == KEY_W)
		data->move->forward = false;
	if (key == KEY_S)
		data->move->backward = false;
	if (key == KEY_LEFT)
		data->move->turn_left = false;
	if (key == KEY_RIGHT)
		data->move->turn_right = false;
	if (key == KEY_A)
		data->move->go_left = false;
	if (key == KEY_D)
		data->move->go_right = false;
	return (0);
}
