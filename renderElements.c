#include "so_long.h"

void	render_wall(t_win *win, int y, int x)
{	
	if (mlx_image_to_window(win->mlx_ptr, win->texture.wall, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void	render_floor(t_win *win, int y, int x)
{	
	if (mlx_image_to_window(win->mlx_ptr, win->texture.floor, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void	render_cover_tiles(t_win *win)
{
	int	i;

	i = 0;
	while(i < win->collect.numberOfCollectables)
	{
		if (mlx_image_to_window(win->mlx_ptr, win->cover_tile.cover, win->pos_player.pos_x * 32, win->pos_player.pos_y * 32) < 0)
			exit(EXIT_FAILURE);
		i++;
	}
}