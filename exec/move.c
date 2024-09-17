/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:35:31 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 15:45:07 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_out_of_the_map(t_data *data, double x, double y)
{
	if (x < 0 || y < 0 || x >= data->mapx || y >= data->mapy)
		return (true);
	return (false);
}

bool	is_wall(t_data *data, double x, double y)
{
	if (is_out_of_the_map(data, x, y))
		return (true);
	return (data->map[double_to_int(y)][double_to_int(x)] == '1' || \
			data->map[double_to_int(y)][double_to_int(x)] == '2');
}

bool	check_x_collision(t_data *data, double new_x, \
						double player_y, double radius)
{
	return (is_out_of_the_map(data, new_x, player_y) || \
			is_wall(data, new_x + radius, player_y) || \
			is_wall(data, new_x - radius, player_y));
}

bool	check_y_collision(t_data *data, double player_x, double new_y, \
							double radius)
{
	return (is_out_of_the_map(data, player_x, new_y) || \
			is_wall(data, player_x, new_y + radius) || \
			is_wall(data, player_x, new_y - radius));
}

bool	check_corner_collision(t_data *data, double new_x, double new_y, \
								double radius)
{
	return (is_wall(data, new_x + radius, new_y + radius) || \
			is_wall(data, new_x - radius, new_y + radius) || \
			is_wall(data, new_x + radius, new_y - radius) || \
			is_wall(data, new_x - radius, new_y - radius));
}

void	check_collision_and_slide(t_data *data, double *new_x, double *new_y)
{
	double	radius;
	bool	x_collision;
	bool	y_collision;

	radius = 0.2;
	x_collision = check_x_collision(data, *new_x, data->player->y, radius);
	y_collision = check_y_collision(data, data->player->x, *new_y, radius);
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
	if (check_corner_collision(data, *new_x, *new_y, radius))
	{
		*new_x = data->player->x;
		*new_y = data->player->y;
	}
}

void	update_position(t_data *data, double *new_x, double *new_y)
{
	if (data->move->forward)
	{
		*new_x += PLAYER_SPEED * cos(data->player->player_angle);
		*new_y += PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->backward)
	{
		*new_x -= PLAYER_SPEED * cos(data->player->player_angle);
		*new_y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->go_left)
	{
		*new_x -= PLAYER_SPEED * cos(data->player->player_angle + PI / 2);
		*new_y -= PLAYER_SPEED * sin(data->player->player_angle + PI / 2);
	}
	if (data->move->go_right)
	{
		*new_x += PLAYER_SPEED * cos(data->player->player_angle + PI / 2);
		*new_y += PLAYER_SPEED * sin(data->player->player_angle + PI / 2);
	}
}

void	update_angle(t_data *data)
{
	if (data->move->turn_left)
	{
		data->player->player_angle -= (PI / 30) * PLAYER_ROTATE;
		data->player->pdx = cos(data->player->player_angle);
		data->player->pdy = sin(data->player->player_angle);
	}
	if (data->move->turn_right)
	{
		data->player->player_angle += (PI / 30) * PLAYER_ROTATE;
		data->player->pdx = cos(data->player->player_angle);
		data->player->pdy = sin(data->player->player_angle);
	}
}

void	move_player(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x;
	new_y = data->player->y;
	update_position(data, &new_x, &new_y);
	check_collision_and_slide(data, &new_x, &new_y);
	data->player->x = new_x;
	data->player->y = new_y;
	update_angle(data);
}
