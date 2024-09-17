/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:41:33 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/16 16:18:59 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_error(char *reason)
{
	write(2, "Error\n", 7);
	write(2, reason, ft_strlen(reason));
	write(2, "\n", 1);
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

	if (!array)
		return ;
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
		if (list->content)
			free(list->content);
		free(list);
		list = tmp;
	}
}

int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	printf("Loading %p\n", texture->img);
	if (texture->img == NULL)
		return (print_error(FAILED_LOAD_TEXTURE), -1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	// protect
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
	if (strncmp(line + strlen(line) - 4, ".xpm", 4) != 0)
		return (print_error(INVALID_TEXTURE_FORMAT), 127);
	i = 0;
	sprites = ft_split(line, ' ');
	if (!sprites)
		return (1);
	data->texture[texture] = ft_calloc(strarray_len(sprites) + 1, sizeof(t_texture));
	if (!data->texture[texture])
		return (free_strarray(sprites), 1);
	while (sprites[i])
	{
		if (load_texture(data, &(data->texture[texture][i]), sprites[i]) == -1)
			return (free_strarray(sprites), 1);
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
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ')
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
		while (line[i] == ' ')
			i++;
		if (line[i] == ',' && color == 2)
			return (print_error(INVALID_COLOR_ARG), 22);
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ')
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
	while (i < TEXTURE_NB)
	{
		j = 0;
		while (data->texture[i] && data->texture[i][j].path)
		{
<<<<<<< Updated upstream
			printf("Freeing %p\n", data->texture[i][j].img);
=======
>>>>>>> Stashed changes
			mlx_destroy_image(data->mlx, data->texture[i][j].img);
			free(data->texture[i][j].path);
			data->texture[i][j].path = NULL;
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

int	padding_map(t_data *data, t_llist *map)
{
	size_t	i;
	t_llist	*tmp;
	char	**padded_map;

	data->mapX = get_max_size(map);
	padded_map = ft_calloc(data->mapY + 1, sizeof(char *));
	if (!padded_map)
		return (1);
	i = 0;
	tmp = map;
	while (tmp)
	{
		padded_map[i] = add_spaces(tmp->content, data->mapX - ft_strlen(tmp->content));
		if (!padded_map[i])
			return (free_strarray(padded_map), 1);
		tmp = tmp->next;
		i++;
	}
	data->map = padded_map;
	return (0);
}

int	parse_map(t_data *data, char *line, int fd)
{
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
			if (!map)
				return (1);
			map->content = ft_strndup(line, ft_strlen(line) - 1);
			if (!map->content)
				return (free(map), 1);
			last = map;
		}
		else
		{
			last->next = ft_calloc(1, sizeof(t_llist));
			if (!last->next)
				return (free_llist(map), 1);
			last = last->next;
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				last->content = ft_strndup(line, len - 1);
			else
				last->content = ft_strdup(line);
			if (!last->content)
				return (free_llist(map), 1);
		}
		data->mapY++;
		free(line);
		errno = 0;
		line = get_next_line(fd);
		if (!line && errno)
			return (1);
	}
	free(line);
	padding_map(data, map);
	free_llist(map);
	return (0);
}


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
	if (!data->texture[WALL_NO] || !data->texture[WALL_SO] || !data->texture[WALL_WE] || !data->texture[WALL_EA] || !data->texture[BEAM] || !data->texture[DOOR])
		return (print_error(WALLS_NOT_INIT), false);
	if (!data->map)
		return (print_error(MAP_NOT_INIT), false);
	return (true);
}

double	get_player_angle(char c)
{
	if (c == 'S')
		return (PI/2);
	else if (c == 'N')
		return ((3 * PI)/2);
	else if (c == 'W')
		return (PI);
	else
		return (2 * PI);
}

bool	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == '2'
		| c == ' ' || c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	map_info_parse(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->mapY)
	{
		j = 0;
		while (j < data->mapX)
		{
			if (!is_map_char(data->map[i][j]))
				return (print_error(INVALID_MAP), 22);
			if (ft_isalpha(data->map[i][j]))
			{
				if (data->player->x != -1 || data->player->y != -1)
					return (print_error(MULTIPLE_PLAYERS), 127);
				data->player->x = j;
				data->player->y = i;
				data->player->player_angle = get_player_angle(data->map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	get_line_trimmed(char **line, char **line_trimmed, int fd)
{
	errno = 0;
	*line = get_next_line(fd);
	if (!*line && errno)
		return (1);
	*line_trimmed = ft_strtrim(*line, " \t\n\v\f\r");
	if (!*line_trimmed && *line)
<<<<<<< Updated upstream
		return (1);
=======
		return (free(*line), 1);
>>>>>>> Stashed changes
	return (0);
}

int	check_colors(t_data *data, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (init_colors(data, line + 2, CEILING));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (init_colors(data, line + 2, FLOOR));
	return (0);
}

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
int	parse(t_data *data, char *file)
{
	int		fd;
	char	*line_trimmed;
	char	*line;
	size_t	i;

	i = 0;
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		return (print_error(INVALID_EXTENSION), 127);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), -1);
	if (get_line_trimmed(&line, &line_trimmed, fd))
		return (close(fd), 1);
	while (line_trimmed)
	{
		if (ft_strncmp(line_trimmed, "C ", 2) == 0)
<<<<<<< Updated upstream
			init_colors(data, line_trimmed + 2, CEILING); // check return
		else if (ft_strncmp(line_trimmed, "F ", 2) == 0)
			init_colors(data, line_trimmed + 2, FLOOR);
		else if (line_trimmed[0] == '1' || line_trimmed[0] == '0')
		{
			if (parse_map(data, line, fd))
				return (close(fd), free(line_trimmed), free(line), 1);
			if (get_line_trimmed(&line, &line_trimmed, fd))
				return (close(fd), 1);
			free(line);
			free(line_trimmed);
=======
		{
			if (init_colors(data, line_trimmed + 2, CEILING))
				return (close(fd), free(line_trimmed), free(line), 1);
		}
		else if (ft_strncmp(line_trimmed, "F ", 2) == 0)
		{
			if (init_colors(data, line_trimmed + 2, FLOOR))
				return (close(fd), free(line_trimmed), free(line), 1);
		}
		else if (line_trimmed[0] == '1' || line_trimmed[0] == '0')
		{
			free(line_trimmed);
			if (parse_map(data, line, fd))
				return (close(fd), free(line), 1);
			if (get_line_trimmed(&line, &line_trimmed, fd))
				return (close(fd), 1);
>>>>>>> Stashed changes
			continue;
		}
		else if (line_trimmed[0])
		{
			if (init_wall(data, line_trimmed))
				return (close(fd), free(line), free(line_trimmed), 1);
		}
		free(line);
		free(line_trimmed);
		if (get_line_trimmed(&line, &line_trimmed, fd))
			return (close(fd), 1);
	}
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
		return (1);
	// fill spaces with 0
	map_fill_spaces(data);
	if (map_info_parse(data))
		return (1);
	if (data->player->x == -1 || data->player->y == -1)
		return (print_error(NO_PLAYER), 127);
	//print map
	printc_map(data->map, data->mapY, data->mapX);
	//print player position and angle
	printf("Player position: %f, %f\n", data->player->x, data->player->y);
	printf("Player angle: %f\n", data->player->player_angle);
	return (close(fd), 0);
}

/*
check if nothing after map
check if 1 letter in map

*/
