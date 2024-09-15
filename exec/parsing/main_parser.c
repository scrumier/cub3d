/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:41:33 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/15 14:02:39 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_error(char *reason)
{
	write(2, "Error\n", 7);
	write(2, reason, ft_strlen(reason));
	write(2, "\n", 1);
	exit(0);
}

size_t	strarray_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_strarray(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_llist(t_llist *list)
{
	t_llist	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (texture->img == NULL)
		return (print_error(FAILED_LOAD_TEXTURE), -1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	texture->path = ft_strdup(path);
	return (0);
}

char *texture_to_string(e_texture texture)
{
	if (texture == WALL_EA)
		return ("WALL_EA");
	else if (texture == WALL_WE)
		return ("WALL_WE");
	else if (texture == WALL_SO)
		return ("WALL_SO");
	else if (texture == WALL_NO)
		return ("WALL_NO");
	else if (texture == BEAM)
		return ("BEAM");
	else if (texture == DOOR)
		return ("DOOR");
	else
		return ("UNKNOWN");
}

int	init_walls_texture(t_data *data, char *line, e_texture texture)
{
	char	**sprites;
	size_t	i;

	if (data->texture[texture])
		return (print_error(ALREADY_INIT), 127);
	i = 0;
	while (line[i] == ' ')
		i++;
	sprites = ft_split(line, ' ');
	if (!sprites)
		return (-1);
	data->texture[texture] = ft_calloc(strarray_len(sprites) + 1, sizeof(t_texture));
	if (!data->texture[texture])
		return (free_strarray(sprites), -1);
	while (sprites[i])
	{
		if (load_texture(data, &(data->texture[texture][i]), sprites[i]) == -1) // TODO: check return for invalid path
			return (free_strarray(sprites), -1);
		i++;
	}
	return (free_strarray(sprites), 0);
}
int	init_wall(t_data *data, char *line)
{
	if (data->map)
		return (print_error(VALUE_AFTER_MAP), 1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_NO));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_SO));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_WE));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_EA));
	else if (ft_strncmp(line, "BEAM ", 5) == 0)
		return(init_walls_texture(data, line + 5, BEAM));
	else if (ft_strncmp(line, "DOOR ", 5) == 0)
		return(init_walls_texture(data, line + 5, DOOR));
	else
		return (print_error(IDENTIFIER_NOT_FOUND), 127);
}

bool	is_valid_char_color(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (false);
		i++;
	}
	return (true);
}

int	init_colors(t_data *data, char *line, e_texture type)
{
	int		rgb[3];
	size_t	i;
	size_t	start;
	size_t	color;

	i = 0;
	color = 0;
	if (data->map)
		return (print_error(VALUE_AFTER_MAP), 1);
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (print_error(INVALID_COLOR_ARG), 22);
	start = i;
	if (!is_valid_char_color(line))
		return (print_error(INVALID_COLOR_ARG), 22);
	while (line[i])
	{
		if (line[i] == ',' && color == 2)
			return (print_error(INVALID_COLOR_ARG), 22);
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (print_error(INVALID_COLOR_ARG), 22);
		if (line[i] == ',' || !line[i + 1])
		{
			if (i == start && line[i + 1])
				return (print_error(INVALID_COLOR_ARG), 22);
			rgb[color] = ft_atoi(line + start);
			if (rgb[color] < 0 || rgb[color] > 255)
				return (print_error(INVALID_COLOR_ARG), 22);
			color++;
			start = i + 1;
		}
		i++;
	}
	if (color != 3)
		return (print_error(INVALID_COLOR_ARG), 22);
	if (type == CEILING)
		data->ceiling_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	else
		data->floor_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (0);
}

void free_texture(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (data->texture[i][j].path)
		{
			free(data->texture[i][j].path);
			mlx_destroy_image(data->mlx, data->texture[i][j].img);
			j++;
		}
		free(data->texture[i]);
		i++;
	}
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	get_max_size(t_llist *list)
{
	size_t	max;
	size_t	len;

	max = 0;
	while (list)
	{
		len = ft_strlen(list->content);
		if (len > max)
			max = len;
		list = list->next;
	}
	return (max);
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

void	padding_map(t_data *data, t_llist *map) // TODO: optimize by putting the space only where needed
{
	size_t	i;
	t_llist	*tmp;
	char	**padded_map;

	data->mapX = get_max_size(map);
	padded_map = ft_calloc(data->mapY + 1, sizeof(char *));
	i = 0;
	tmp = map;
	while (tmp)
	{
		padded_map[i] = add_spaces(tmp->content, data->mapX - ft_strlen(tmp->content)); //TODO: check return
		tmp = tmp->next;
		i++;
	}
	data->map = padded_map;
}

int	parse_map(t_data *data, char *line, int fd)
{
	// TODO : protect mallocs
	t_llist	*map;
	t_llist	*last;
	size_t	len;

	map = NULL;
	last = NULL;
	data->mapY = 0;
	if (data->map)
		return (print_error(VALUE_AFTER_MAP), 127);
	while (line && line[0] != '\n')
	{
		if (!map)
		{
			map = ft_calloc(1, sizeof(t_llist));
			map->content = ft_strndup(line, ft_strlen(line) - 1);
			last = map;
		}
		else
		{
			last->next = ft_calloc(1, sizeof(t_llist));
			last = last->next;
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				last->content = ft_strndup(line, len - 1);
			else
				last->content = ft_strdup(line);
		}
		data->mapY++;
		free(line);
		line = get_next_line(fd);
	}
	padding_map(data, map);
	return (0);
}

/*
to check:
- maps must start with 1 or space
- maps must end with 1 or space
- maps first and last line should all be 1 or space

to do:
- space check in 8 directions
- replace spaces with 0
*/

int space_check(t_data *data, size_t x, size_t y)
{
	size_t map_width;
	size_t map_height;

	map_width = data->mapX;
	map_height = data->mapY;
	// <- x - 1
	if (x > 0 && (data->map[y][x - 1] != '1' && data->map[y][x - 1] != ' '))
		return (0);
	// -> x + 1
	if (x + 1 < map_width && (data->map[y][x + 1] != '1' && data->map[y][x + 1] != ' '))
		return (0);
	// ⬆ y - 1
	if (y > 0 && (data->map[y - 1][x] != '1' && data->map[y - 1][x] != ' '))
		return (0);
	// ⬇ y + 1
	if (y + 1 < map_height && (data->map[y + 1][x] != '1' && data->map[y + 1][x] != ' '))
		return (0);
	// 🡥 (x + 1), (y + 1)
	if (x > 0 && y > 0 && (data->map[y - 1][x - 1] != '1' && data->map[y - 1][x - 1] != ' '))
		return (0);
	// 🡦 (x + 1), (y - 1)
	if (x + 1 < map_width && y > 0 && (data->map[y - 1][x + 1] != '1' && data->map[y - 1][x + 1] != ' '))
		return (0);
	// 🡧 (x - 1), (y + 1)
	if (x > 0 && y + 1 < map_height && (data->map[y + 1][x - 1] != '1' && data->map[y + 1][x - 1] != ' '))
		return (0);
	// 🡤 (x - 1), (y - 1)
	if (x + 1 < map_width && y + 1 < map_height && (data->map[y + 1][x + 1] != '1' && data->map[y + 1][x + 1] != ' '))
		return (0);
	return (1);
}

int	map_check(t_data *data)
{
	size_t	y;
	size_t	x;
	

	y = 0;
	while (y < data->mapY)
	{
		x = 0;
		if (data->map[y][0] != '1' && data->map[y][0] != ' ')
			return (print_error(INVALID_MAP), 22);
		while (data->map[y][x])
		{
			if ((y == 0 || y == data->mapY - 1) && data->map[y][x] != '1' && data->map[y][x] != ' ')
				return (print_error(INVALID_MAP), 22);
			if (data->map[y][x] == ' ')
			{
				if (!space_check(data, x, y))
					return (print_error(INVALID_MAP), 22);
			}
			x++;
		}
		if (data->map[y][x - 1] != '1' && data->map[y][x - 1] != ' ')
			return (print_error(INVALID_MAP), 22);
		y++;
	}
	return (0);
}

void print_color(const char *label, unsigned int color)
{
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    printf("\033[38;2;%d;%d;%dm%s: #%06x\033[0m\n", red, green, blue, label, color);
}

void printc_map(char **map, size_t height, size_t width)
{
    // Loop over each row in the map
    for (size_t y = 0; y < height; y++)
    {
        // Loop over each column in the row
        for (size_t x = 0; x < width; x++)
        {
            char c = map[y][x];

            // Check what to print and set the color accordingly
            if (c == '1') // Walls, print in red
            {
                printf("\033[31m%c\033[0m", c); // Red color
            }
            else if (c == '2') // Doors, print in blue
            {
                printf("\033[34m%c\033[0m", c); // Blue color
            }
            else if (ft_isalpha(c)) // Players, print in green
            {
                printf("\033[32m%c\033[0m", c); // Green color
            }
            else // Any other character, print without color
            {
                printf("%c", c);
            }
        }
        printf("\n"); // Move to the next line after each row
    }
}

void	map_fill_spaces(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < data->mapY)
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

bool	is_everything_init(t_data *data)
{
	if (data->ceiling_color == -1)
		return (print_error(CEILING_NOT_INIT), false);
	if (data->floor_color == -1)
		return (print_error(FLOOR_NOT_INIT), false);
	//  || !data->texture[BEAM] || !data->texture[DOOR]
	if (!data->texture[WALL_NO] || !data->texture[WALL_SO] || !data->texture[WALL_WE] || !data->texture[WALL_EA])
		return (print_error(WALLS_NOT_INIT), false);
	if (!data->map)
		return (print_error(MAP_NOT_INIT), false);
	return (true);
}

int	parse(t_data *data, char *file)
{
	int		fd;
	char	*line;
	char	*tmp;
	size_t	i;

	i = 0;
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		return (print_error(INVALID_EXTENSION), 127);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), -1);
	tmp = get_next_line(fd); // TODO: check function's return
	line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	while (line)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			init_colors(data, line + 2, CEILING);
		else if (ft_strncmp(line, "F ", 2) == 0)
			init_colors(data, line + 2, FLOOR);
		else if (line[0] == '1' || line[0] == '0')
		{
			parse_map(data, tmp, fd);
			free(line);
			tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
			line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
			continue;
		}
		else if (line[0])
			init_wall(data, line);
		free(tmp);
		free(line);
		tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
		line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	}
	// check if all data is present and if there isn't any redefinition after map
	if (!is_everything_init(data))
		return (127);
	print_color("Ceiling", data->ceiling_color);
    print_color("Floor", data->floor_color);
	//print every texture path
	i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		printf("Texture %s\n", texture_to_string((e_texture)i));
		while (data->texture[i][j].path)
		{
			printf("%s\n", data->texture[i][j].path);
			j++;
		}
		i++;
	}
	// print map check
	if (map_check(data) == 0)
		printf("\033[0;32m%d\033[0m\n", map_check(data));
	else
		printf("\033[0;31m%d\033[0m\n", map_check(data));
	// fill spaces with 0
	map_fill_spaces(data);
	//print map
	printc_map(data->map, data->mapY, data->mapX);
	return (close(fd), 0);
}

/*
check if nothing after map
check if 1 letter in map
*/
