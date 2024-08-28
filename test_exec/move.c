/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:35:31 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/28 15:28:39 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_collision(t_data *data)
{
	if (data->map[double_to_int(data->player->x) / COEF][double_to_int(data->player->y) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x + 0.1) / COEF][double_to_int(data->player->y) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x + 0.1) / COEF][double_to_int(data->player->y + 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x) / COEF][double_to_int(data->player->y + 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x) / COEF][double_to_int(data->player->y - 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x - 0.1) / COEF][double_to_int(data->player->y + 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x - 0.1) / COEF][double_to_int(data->player->y) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x - 0.1) / COEF][double_to_int(data->player->y - 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x) / COEF][double_to_int(data->player->y - 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->map[double_to_int(data->player->x + 0.1) / COEF][double_to_int(data->player->y - 0.1) / COEF] == '1')
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
}

void	move_player(t_data *data)
{
	if (double_to_int(data->player->x) < 0 || double_to_int(data->player->x) > data->mapX || double_to_int(data->player->y) < 0 || double_to_int(data->player->y) > data->mapY)
	{
		data->created_player = false;
		return ;
	}
	if (data->move->forward == true)
	{
		data->player->x += PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y += PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->backward == true)
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->turn_left == true)
	{
		data->player->player_angle = (data->player->player_angle - PI / 30);
		data->player->pdx = (double)PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = (double)PLAYER_ROTATE * sin(data->player->player_angle);
	}
	if (data->move->turn_right == true)
	{
		data->player->player_angle = (data->player->player_angle + PI / 30);
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);
	}
	if (data->move->go_left == true)
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle + PI / 2);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle + PI / 2);
	}
	if (data->move->go_right == true)
	{
		data->player->x += PLAYER_SPEED * cos(data->player->player_angle + PI / 2);
		data->player->y += PLAYER_SPEED * sin(data->player->player_angle + PI / 2);
	}
}
