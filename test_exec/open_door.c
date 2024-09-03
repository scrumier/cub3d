#include "cube3d.h"

bool	door_around(t_data *data, double x, double y)
{
	if (data->map[double_to_int(x)][double_to_int(y)] == '2')
		return (true);
	if (data->map[double_to_int(x + 0.5)][double_to_int(y)] == '2')
		return (true);
	if (data->map[double_to_int(x + 0.5)][double_to_int(y + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x - 0.5)][double_to_int(y + 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x - 0.5)][double_to_int(y)] == '2')
		return (true);
	if (data->map[double_to_int(x - 0.5)][double_to_int(y - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		return (true);
	if (data->map[double_to_int(x + 0.5)][double_to_int(y - 0.5)] == '2')
		return (true);
	return (false);
}

void	open_door(t_data *data)
{
	double	x = data->player->x;
	double	y = data->player->y;

	if (data->map[double_to_int(x)][double_to_int(y)] == '2')
		data->map[double_to_int(x)][double_to_int(y)] = '0';
	if (data->map[double_to_int(x + 0.5)][double_to_int(y)] == '2')
		data->map[double_to_int(x + 0.5)][double_to_int(y)] = '0';
	if (data->map[double_to_int(x + 0.5)][double_to_int(y + 0.5)] == '2')
		data->map[double_to_int(x + 0.5)][double_to_int(y + 0.5)] = '0';
	if (data->map[double_to_int(x)][double_to_int(y + 0.5)] == '2')
		data->map[double_to_int(x)][double_to_int(y + 0.5)] = '0';
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x)][double_to_int(y - 0.5)] = '0';
	if (data->map[double_to_int(x - 0.5)][double_to_int(y + 0.5)] == '2')
		data->map[double_to_int(x - 0.5)][double_to_int(y + 0.5)] = '0';
	if (data->map[double_to_int(x - 0.5)][double_to_int(y)] == '2')
		data->map[double_to_int(x - 0.5)][double_to_int(y)] = '0';
	if (data->map[double_to_int(x - 0.5)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x - 0.5)][double_to_int(y - 0.5)] = '0';
	if (data->map[double_to_int(x)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x)][double_to_int(y - 0.5)] = '0';
	if (data->map[double_to_int(x + 0.5)][double_to_int(y - 0.5)] == '2')
		data->map[double_to_int(x + 0.5)][double_to_int(y - 0.5)] = '0';
}
