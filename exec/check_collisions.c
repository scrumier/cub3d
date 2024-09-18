/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:18 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/18 10:18:18 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
