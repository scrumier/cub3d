/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:21 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:57:30 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	colors_init_check(size_t *i, char **line, size_t *start, size_t *color)
{
	*i = 0;
	*color = 0;
	while ((*line)[*i] == ' ')
		(*i)++;
	if (!(*line)[*i])
		return (print_error(INVALID_COLOR_ARG), 22);
	*start = *i;
	if (!is_valid_char_color(*line))
		return (print_error(INVALID_COLOR_ARG), 22);
	return (0);
}

int	init_color_return(size_t color, t_texture_enum type, t_data *data, int *rgb)
{
	if (color != 3)
		return (print_error(INVALID_COLOR_ARG), 22);
	if (type == CEILING)
		data->ceiling_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	else
		data->floor_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (0);
}

int	color_line_check(char *line, size_t *i, size_t color)
{
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == ',' && color == 2)
		return (print_error(INVALID_COLOR_ARG), 22);
	if (!ft_isdigit(line[*i]) && line[*i] != ',' && line[*i] != ' ')
		return (print_error(INVALID_COLOR_ARG), 22);
	return (0);
}

int	init_colors(t_data *data, char *line, t_texture_enum type)
{
	int		rgb[3];
	size_t	i;
	size_t	start;
	size_t	color;

	if (data->map)
		return (print_error(VALUE_AFTER_MAP), 1);
	if (colors_init_check(&i, &line, &start, &color))
		return (22);
	while (line[i])
	{
		if (color_line_check(line, &i, color))
			return (22);
		if (line[i] == ',' || !line[i + 1])
		{
			if (i == start && line[i + 1])
				return (print_error(INVALID_COLOR_ARG), 22);
			rgb[color] = ft_atoi(line + start);
			if (rgb[color] < 0 || rgb[color++] > 255)
				return (print_error(INVALID_COLOR_ARG), 22);
			start = i + 1;
		}
		i++;
	}
	return (init_color_return(color, type, data, rgb));
}

int	parse_colors(t_data *data, char **line_trimmed, char **line, int fd)
{
	if (ft_strncmp(*line_trimmed, "C ", 2) == 0)
	{
		if (init_colors(data, *line_trimmed + 2, CEILING))
			return (close(fd), free(*line_trimmed), free(*line), 1);
	}
	else if (ft_strncmp(*line_trimmed, "F ", 2) == 0)
	{
		if (init_colors(data, *line_trimmed + 2, FLOOR))
			return (close(fd), free(*line_trimmed), free(*line), 1);
	}
	return (0);
}
