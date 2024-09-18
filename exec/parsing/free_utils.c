/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:38:09 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:58:11 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	free_texture(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < TEXTURE_NB)
	{
		j = 0;
		while (data->texture[i] && data->texture[i][j].path)
		{
			mlx_destroy_image(data->mlx, data->texture[i][j].img);
			free(data->texture[i][j].path);
			data->texture[i][j].path = NULL;
			j++;
		}
		free(data->texture[i]);
		i++;
	}
}
