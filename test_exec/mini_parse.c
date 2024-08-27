/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:17:17 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/27 12:17:38 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	mini_parse(t_data *data, char *file)
{
	int fd = open(file, O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	int j;
	int k;
	data->map = ft_calloc(MAP_SIZE, sizeof(char *));

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
	data->mapY = j;
	print_map(data->map);
}
