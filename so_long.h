//cc so_long.c libmlx42.a  -ldl -lglfw -pthread -lm && ./a.out

#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "include/MLX42/MLX42.h"

#define COLS 12
#define ROWS 7

typedef struct s_game_textures
{
	mlx_image_t	*character;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*collect;
	mlx_image_t	*exit;
}	t_textures;

typedef struct s_map {
	char map[ROWS][COLS];
} t_map;

typedef struct s_exit_tile {
	int pos_x;
	int pos_y;
} t_exit_tile;

typedef struct s_pos_player {
	int pos_x;
	int pos_y;
} t_player_pos;

typedef struct s_collectable {
	int numberOfCollectables;
} t_collect;

typedef struct s_window {
	mlx_t			*mlx_ptr;
	void			*win_ptr;
	t_player_pos		pos_player;
	t_collect		collect;
	t_map			map;
	t_exit_tile		exit_tile;
	t_textures		texture;
	
} t_win;

#endif
