#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_game
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_game;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	char		*map_path;
	char		**map;
	t_rgb		*floor;
	t_rgb		*ceiling;
	t_texture	*texture_NO;
	t_texture	*texture_SO;
	t_texture	*texture_WE;
	t_texture	*texture_EA;
	t_game		*game;
}	t_all;

t_all	*init_all();
int	parser(int argc, char **argv, t_all *all);

#endif
