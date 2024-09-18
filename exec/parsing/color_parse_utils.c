/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:00 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:58:07 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_color_line(char *line)
{
	return (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0);
}

bool	is_valid_char_color(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	check_colors(t_data *data, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (init_colors(data, line + 2, CEILING));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (init_colors(data, line + 2, FLOOR));
	return (0);
}
