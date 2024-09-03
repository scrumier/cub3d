#include "cube3d.h"

bool	door_around(t_data *data, double x, double y)
{
	// return true if there is a door around theses coordinates
	if (data->map[double_to_int(x) / COEF][double_to_int(y) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x + 1) / COEF][double_to_int(y) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x + 1) / COEF][double_to_int(y + 1) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x) / COEF][double_to_int(y + 1) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x) / COEF][double_to_int(y - 1) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x - 1) / COEF][double_to_int(y + 1) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x - 1) / COEF][double_to_int(y) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x - 1) / COEF][double_to_int(y - 1) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x) / COEF][double_to_int(y - 1) / COEF] == '2')
		return (true);
	if (data->map[double_to_int(x + 1) / COEF][double_to_int(y - 1) / COEF] == '2')
		return (true);
	return (false);
}

void	open_door(t_data *data)
{
	if (door_around(data, data->player->x, data->player->y)) {
		write(1, "Door opened\n", 12);
	}
}
