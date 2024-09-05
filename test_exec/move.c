/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:35:31 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 11:36:45 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool is_out_of_the_map(t_data *data, double x, double y)
{
	if (x < 0 || y < 0 || x >= data->mapX || y >= data->mapY)
		return (true);
	return (false);
}

bool is_wall(t_data *data, double x, double y)
{
	return (data->map[double_to_int(x)][double_to_int(y)] == '1' || \
			data->map[double_to_int(x)][double_to_int(y)] == '2');
}

void	check_collision_and_slide(t_data *data, double *new_x, double *new_y)
{
	double	radius;
	bool	x_collision;
	bool	y_collision;

	radius = 0.2;
	x_collision = false;
	y_collision = false;
	if (is_out_of_the_map(data, *new_x, data->player->y) ||
		is_wall(data, *new_x + radius, data->player->y) ||
		is_wall(data, *new_x - radius, data->player->y))
		x_collision = true;
	if (is_out_of_the_map(data, data->player->x, *new_y) ||
		is_wall(data, data->player->x, *new_y + radius) ||
		is_wall(data, data->player->x, *new_y - radius))
		y_collision = true;
	if (x_collision && y_collision)
	{
		*new_x = data->player->x;
		*new_y = data->player->y;
	}
	else
	{
		if (x_collision)
			*new_x = data->player->x;
		if (y_collision)
			*new_y = data->player->y;
	}
	if (is_wall(data, *new_x + radius, *new_y + radius) ||
		is_wall(data, *new_x - radius, *new_y + radius) ||
		is_wall(data, *new_x + radius, *new_y - radius) ||
		is_wall(data, *new_x - radius, *new_y - radius))
	{
		*new_x = data->player->x;
		*new_y = data->player->y;
	}
}


void move_player(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->x;
	new_y = data->player->y;
	if (data->move->forward == true)
	{
		new_x += PLAYER_SPEED * cos(data->player->player_angle);
		new_y += PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->backward == true)
	{
		new_x -= PLAYER_SPEED * cos(data->player->player_angle);
		new_y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->go_left == true)
	{
		new_x -= PLAYER_SPEED * cos(data->player->player_angle + PI / 2);
		new_y -= PLAYER_SPEED * sin(data->player->player_angle + PI / 2);
	}
	if (data->move->go_right == true)
	{
		new_x += PLAYER_SPEED * cos(data->player->player_angle + PI / 2);
		new_y += PLAYER_SPEED * sin(data->player->player_angle + PI / 2);
	}
	check_collision_and_slide(data, &new_x, &new_y);
	data->player->x = new_x;
	data->player->y = new_y;
	if (data->move->turn_left == true)
	{
		data->player->player_angle -= (PI / 30) * PLAYER_ROTATE;
		data->player->pdx = cos(data->player->player_angle);
		data->player->pdy = sin(data->player->player_angle);
	}
	if (data->move->turn_right == true)
	{
		data->player->player_angle += PI / 30 * PLAYER_ROTATE;
		data->player->pdx = cos(data->player->player_angle);
		data->player->pdy = sin(data->player->player_angle);
	}
}