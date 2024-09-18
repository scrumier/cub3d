/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:40:39 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 11:48:44 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == '2'
		| c == ' ' || c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void	map_fill_spaces(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < (size_t)data->mapy)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == ' ')
				data->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int	map_check_init_x(size_t *x, size_t y, t_data *data)
{
	*x = 0;
	if (data->map[y][0] != '1' && data->map[y][0] != ' ')
		return (print_error(INVALID_MAP), 22);
	return (0);
}

char	*add_spaces(char *str, size_t amount)
{
	char	*tmp;
	size_t	i;

	i = ft_strlen(str);
	tmp = ft_calloc(i + amount + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, i + 1);
	while (amount--)
		tmp[i++] = ' ';
	return (tmp);
}

int	padding_map(t_data *data, t_llist *map)
{
	size_t	i;
	t_llist	*tmp;
	char	**padded_map;

	data->mapx = get_max_size(map);
	padded_map = ft_calloc((size_t)data->mapy + 1, sizeof(char *));
	if (!padded_map)
		return (1);
	i = 0;
	tmp = map;
	while (tmp)
	{
		padded_map[i] = add_spaces(tmp->content, \
			data->mapx - ft_strlen(tmp->content));
		if (!padded_map[i])
			return (free_strarray(padded_map), 1);
		tmp = tmp->next;
		i++;
	}
	data->map = padded_map;
	return (0);
}
