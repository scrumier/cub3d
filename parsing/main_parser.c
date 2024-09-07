#include "cube3d.h"

typedef struct	s_parsedata
{
	int				ceiling_color;
	int				floor_color;
	t_player		*player;
	char			**map;
	int				mapX;
	int				mapY;
	t_texture		*texture[6];
}				t_parsedata;

typedef enum
{
	WALL_EA = 0,
	WALL_WE,
	WALL_SO,
	WALL_NO,
	BEAM,
	DOOR,
	CEILING,
	FLOOR
}	e_texture;

void	mini_parse(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	int		k;

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
	data->mapY = j;
	print_map(data->map);
}

void	init_textures(t_data *data)
{
	load_texture(data, &data->texture[0], "textures/wall_1.xpm"); // east
	load_texture(data, &data->texture[1], "textures/wall_2.xpm"); // west
	load_texture(data, &data->texture[2], "textures/wall_3.xpm"); // south
	load_texture(data, &data->texture[3], "textures/wall_4.xpm"); // north
	load_texture(data, &data->texture[4], "textures/beam.xpm");
	load_texture(data, &data->texture[5], "textures/door.xpm");
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

int	init_walls_texture(t_parsedata *data, char *line, e_texture texture)
{
	char	**sprites;
	size_t	i;

	i = 0;
	sprites = ft_split(line, ' ');
	if (!sprites)
		return (-1);
	data->texture[texture] = ft_calloc(strarray_len(sprites), sizeof(t_texture));
	if (!data->texture[texture])
		return (free_strarray(sprites), -1);
	while (sprites[i])
	{
		load_texture(data, &data->texture[texture], sprites[i]);
		i++;
	}
	return (free_strarray(sprites), 0);
}
int	init_wall(t_parsedata *data, char *line)
{
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
		return (127); // TODO: print identifier not found
}

int	init_colors(t_parsedata *data, char *line)
{
	int		rgb[3];
	size_t	i;
	size_t	start;
	size_t	color;

	i = 0;
	color = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (22); // TODO: print invalid arg
	start = i;
	while (line[i])
	{
		if (line[i] == ',' && color == 2)
			return (22); // TODO: print invalid arg
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (22); // TODO: print invalid arg
		if (line[i] == ',')
		{
			if (i == start)
				return (22); // TODO: print invalid arg
			rgb[color] = ft_atoi(line + start);
			if (rgb[color] < 0 || rgb[color] > 255)
				return (22); // TODO: print invalid arg
			color++;
			start = i + 1;
		}
		i++;
	}


}

int	parse(t_parsedata *data, char *file)
{
	int		fd;
	char	*line;
	char	*tmp;
	size_t	i;
	int		ret;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("cube3d: "), -1);
	tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
	line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	while (line)
	{
		if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
			init_colors(data, line + 2);
		{
			
		}
		//elseif (ft_isdigit(line[0]))
		//else
		//	init_wall(data, line);
	}
}
