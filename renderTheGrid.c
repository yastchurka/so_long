/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderTheGrid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralukasi <ralukasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:10:14 by ralukasi          #+#    #+#             */
/*   Updated: 2024/01/07 14:30:19 by ralukasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	lets_try(t_win *win, char map_byte, int ix, int iy)
{
	if (map_byte == 'P')
	{
		render_floor(win, iy, ix);
		assign_player_pos(win, iy, ix);
	}
	else if (map_byte == 'E')
		render_assign_exit_pos(win, iy, ix);
	else if (map_byte == 'C')
		render_assign_coll_pos(win, iy, ix, map_byte);
	else if (map_byte == '0')
	{
		win->map.map[iy][ix] = map_byte;
		render_floor(win, iy, ix);
	}
	else 
	{
		win->map.map[iy][ix] = map_byte;
		render_wall(win, iy, ix);
	}
}

void	render_map(t_win *win)
{
	int		fd;
	char	buffer[1];
	char	map_byte;
	ssize_t	bytes_read;
	int		ix;
	int		iy;

	ix = 0;
	iy = 0;
	fd = open("map.ber", O_RDONLY);
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		map_byte = buffer[0];
		if (map_byte == '\n')
		{
			ix = -1;
			iy++;
		}
		else
			lets_try(win, map_byte, ix, iy);
		ix++;
	}
	render_cover_tiles(win);
	if (mlx_image_to_window(win->mlx_ptr, win->texture.character, 
			win->pos_player.pos_x * 32, win->pos_player.pos_y * 32) < 0)
		exit(EXIT_FAILURE);
}
	//close the file maybe?

void	change_instances(t_win *win, int y, int x)
{
	win->texture.character->instances[0].y = y * 32;
	win->texture.character->instances[0].x = x * 32;
}

void	check_tile_conditions(t_win *win)
{
	
	if (win->map.map[win->pos_player.pos_y][win->pos_player.pos_x] == 'C') 
	{
		win->cover_tile.cover->instances[win->collect.numberOfCollectables - 1].x = win->pos_player.pos_x * 32;
		win->cover_tile.cover->instances[win->collect.numberOfCollectables - 1].y = win->pos_player.pos_y * 32;
		win->map.map[win->pos_player.pos_y][win->pos_player.pos_x] = '0';
		win->collect.numberOfCollectables--;
	}
	if (win->exit_tile.pos_x == win->pos_player.pos_x 
		&& win->exit_tile.pos_y == win->pos_player.pos_y) 
	{
		if (win->collect.numberOfCollectables == 0)
		{
			printf("You won!\n");
			exit(0);
		}
	}
}
