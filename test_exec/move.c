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

bool is_out_of_the_map(t_data *data, double x, double y)
{
	if (x < 0 || y < 0 || x >= data->mapX || y >= data->mapY)
		return (true);
	return (false);
}

bool is_wall(t_data *data, double x, double y)
{
	return (data->map[double_to_int(x)][double_to_int(y)] == '1' || data->map[double_to_int(x)][double_to_int(y)] == '2');
}

void check_collision_and_slide(t_data *data, double *new_x, double *new_y)
{
	double radius = 0.2;  // Player collision radius
	bool x_collision = false;
	bool y_collision = false;

	// Check for collision on the x-axis
	if (is_out_of_the_map(data, *new_x, data->player->y) ||
		is_wall(data, *new_x + radius, data->player->y) ||
		is_wall(data, *new_x - radius, data->player->y))
	{
		x_collision = true;
	}

	// Check for collision on the y-axis
	if (is_out_of_the_map(data, data->player->x, *new_y) ||
		is_wall(data, data->player->x, *new_y + radius) ||
		is_wall(data, data->player->x, *new_y - radius))
	{
		y_collision = true;
	}

	// If both x and y would cause a collision, prevent movement in both directions
	if (x_collision && y_collision) {
		*new_x = data->player->x;
		*new_y = data->player->y;
	}
		// Otherwise, allow sliding along the axis that does not collide
	else {
		if (x_collision) {
			*new_x = data->player->x;
		}
		if (y_collision) {
			*new_y = data->player->y;
		}
	}
}

void move_player(t_data *data)
{
	double new_x = data->player->x;
	double new_y = data->player->y;

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

	// Check for collisions and allow sliding
	check_collision_and_slide(data, &new_x, &new_y);

	// Update player position
	data->player->x = new_x;
	data->player->y = new_y;

	if (data->move->turn_left == true)
	{
		data->player->player_angle -= PI / 30;
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);
	}
	if (data->move->turn_right == true)
	{
		data->player->player_angle += PI / 30;
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);
	}
}