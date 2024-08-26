/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:35:31 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/26 10:35:45 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_player(t_data *data)
{

	if (data->player->x < 0 || data->player->x > 9 || data->player->y < 0 || data->player->y > 9)
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
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);
	}
	if (data->move->turn_right == true)
	{
		data->player->player_angle = (data->player->player_angle + PI / 30);
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);

	}
}
