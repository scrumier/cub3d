/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:50:42 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:56:08 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	get_player_angle(char c)
{
	if (c == 'S')
		return (PI / 2);
	else if (c == 'N')
		return ((3 * PI) / 2);
	else if (c == 'W')
		return (PI);
	else
		return (2 * PI);
}
