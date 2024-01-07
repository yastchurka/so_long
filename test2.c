/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralukasi <ralukasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:09:42 by ralukasi          #+#    #+#             */
/*   Updated: 2024/01/07 14:41:30 by ralukasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/MLX42/MLX42.h"
#include "so_long.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_win	*win;
	int		new_y;
	int		new_x;

	win = param;
	new_y = win->pos_player.pos_y;
	new_x = win->pos_player.pos_x;
	if ((keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS))
		mlx_close_window(win->mlx_ptr);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		new_y--;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		new_y++;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		new_x--;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		new_x++;
	if (win->map.map[new_y][new_x] != '1')
		change_instances(win, new_y, new_x);
	check_tile_conditions(win);
}

void	initialize_textures(t_win *win)
{
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*character;
	mlx_texture_t	*collect;
	mlx_texture_t	*exit_texture;

	win->mlx_ptr = mlx_init(win->map.cols * 32, 
			win->map.rows * 32, "Shitcircus", true);
	if (!win->mlx_ptr)
		exit(EXIT_FAILURE);
	if (!wall_texture && !character && !collect && !exit_texture)
		exit(EXIT_FAILURE);
	wall_texture = mlx_load_png("./textures/wall.png");
	character = mlx_load_png("./textures/character.png");
	collect = mlx_load_png("./textures/collect.png");
	exit_texture = mlx_load_png("./textures/exit.png");
	win->texture.wall = mlx_texture_to_image(win->mlx_ptr, wall_texture);
	win->texture.character = mlx_texture_to_image(win->mlx_ptr, character);
	win->texture.collect = mlx_texture_to_image(win->mlx_ptr, collect);
	win->texture.exit = mlx_texture_to_image(win->mlx_ptr, exit_texture);
}

int32_t	main(void)
{
	t_win			win;
	int				count_moves;
	mlx_texture_t	*cover;
	mlx_texture_t	*grass;

	count_moves = 0;
	cover = mlx_load_png("./textures/grass.png");
	grass = mlx_load_png("./textures/grass.png");
	win.collect.numberOfCollectables = 0;
	win.cover_tile.cover = mlx_texture_to_image(win.mlx_ptr, grass);
	win.texture.floor = mlx_texture_to_image(win.mlx_ptr, grass);
	determine_map_size(&win);
	initialize_textures(&win);
	if (!check_if_passable(&win))
	{
		printf("Wrong map file");
		(EXIT_FAILURE);
	}
	mlx_key_hook(win.mlx_ptr, &my_keyhook, &win);
	mlx_loop(win.mlx_ptr);
	mlx_terminate(win.mlx_ptr);
	return (EXIT_SUCCESS);
}

//mlx_set_setting(MLX_MAXIMIZED, false);
//cc test.c libmlx42.a  -ldl -lglfw -pthread -lm && ./a.out