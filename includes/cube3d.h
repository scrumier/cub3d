/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:17:42 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/20 15:34:55 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>
# include "libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define KeyPress 2
# define KeyRelease 3
# define HEIGHT 800
# define WIDTH 800
# define COEF 60
# define PLAYER_SIZE 20

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_player
{
	float		x;
	float		y;
}				t_player;

typedef struct	s_move
{
	bool		up;
	bool		down;
	bool		left;
	bool		right;
}				t_move;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	*player;
	t_move		*move;
	bool		created_player;
	int			map[10][10];
}				t_data;

#endif