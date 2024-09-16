/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:17 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 11:38:38 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	mini_parse(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	int		k;

	j = 0;
	data->ceiling_color = 0x404040;
	data->floor_color = 0x5C4033;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	data->map = ft_calloc(600, sizeof(char *));
	while (line)
	{
		j = 0;
		k = 0;
		data->map[i] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		while (line[j])
		{
			if (line[j] == ' ')
				j++;
			else
			{
				data->map[i][k] = line[j];
				j++;
				k++;
			}
		}
		line = get_next_line(fd);
		i++;
	}
	data->mapX = i;
	data->mapY = j / 2 + 1;
	print_map(data->map);
}
