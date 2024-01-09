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

typedef struct s_game_textures
{
	mlx_image_t	*character;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*collect;
	mlx_image_t	*exit;
}	t_textures;

typedef struct s_cover {
	mlx_image_t	*cover;
} t_cover;

typedef struct s_map {
	char **map;
    int rows;
    int cols;
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

typedef struct s_visited {
	char **visited;
} t_visit;


typedef struct s_window {
	mlx_t			*mlx_ptr;
	void			*win_ptr;
	t_player_pos	pos_player;
	t_collect		collect;
	t_map			map;
	t_exit_tile		exit_tile;
	t_textures		texture;
	t_cover			cover_tile;
	int				moves_number;
	t_visit			visited;
} t_win;

//checkIfPassable.c
void check_if_passable(void *param);
void check_if_serrounded_by_ones(t_win *win);
void check_other_signes(t_win *win);
bool dfs(t_win *win, int row, int col);

//assignPositions.c
void assign_player_pos(t_win *win, int y, int x);
void render_assign_exit_pos(t_win *win, int y, int x);
void render_assign_coll_pos(t_win *win, int y, int x, char map_byte);

//determineMapSize.c
void	determine_map_size(t_win *win);
void	malloc_map(t_win *win, int ix, int iy);
void	read_update_map(t_win *win, int *ix, int *iy, ssize_t bytesRead, char map_byte);
void	open_map_file(int *fd);
void	close_map_file(int fd);

 //renderTheGrid.c - norminette to solve
void	let_try(t_win *win, char map_byte, int ix, int iy);
void	render_map(t_win *win);
void	change_instances(t_win *win, int y, int x);
void	check_tile_conditions(t_win *win);

//renderElements.c
void	render_cover_tiles(t_win *win);
void	render_floor(t_win *win, int y, int x);
void	render_wall(t_win *win, int y, int x);

//moves.c
void    move_up(t_win *win);
void    move_left(t_win *win);
void    move_right(t_win *win);
void    move_down(t_win *win);

#endif 
