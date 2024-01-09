#include "so_long.h"

void	assign_player_pos(t_win *win, int y, int x)
{
	win->pos_player.pos_x = x;
	win->pos_player.pos_y = y;
	win->map.map[y][x] = '0';
}

void	render_assign_exit_pos(t_win *win, int y, int x)
{
	win->exit_tile.pos_x = x;
	win->exit_tile.pos_y = y;
	win->map.map[y][x] = '0';
	if (mlx_image_to_window(win->mlx_ptr, win->texture.exit, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void	render_assign_coll_pos(t_win *win, int y, int x, char map_byte)
{
	win->map.map[y][x] = map_byte;
	win->collect.numberOfCollectables++;
	if (mlx_image_to_window(win->mlx_ptr, win->texture.collect, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}