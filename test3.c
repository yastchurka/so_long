#include "so_long.h"

void my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_win	*win;

	win = param;
    if ((keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS))
        mlx_close_window(win->mlx_ptr);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(win);
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        move_down(win);//new_y++;
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        move_left(win);//new_x--;
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        move_right(win);//new_x++;
	check_tile_conditions(win);
}

void initialize_textures(t_win *win)
{
	win->mlx_ptr = mlx_init(win->map.cols * 32, win->map.rows * 32, "Shitcircus", true);
	if (!win->mlx_ptr)
		exit(EXIT_FAILURE);
	mlx_texture_t* wall_texture = mlx_load_png("./textures/wall.png");
	mlx_texture_t* grass = mlx_load_png("./textures/grass.png");
	mlx_texture_t* collect = mlx_load_png("./textures/collect.png");
	mlx_texture_t* exit_texture = mlx_load_png("./textures/exit.png");
	mlx_texture_t* cover = mlx_load_png("./textures/grass.png");
	if (!wall_texture || !grass || !collect || !exit_texture)
		exit(EXIT_FAILURE);
	win->texture.floor = mlx_texture_to_image(win->mlx_ptr, grass);
	win->texture.wall  = mlx_texture_to_image(win->mlx_ptr, wall_texture);
	win->texture.collect  = mlx_texture_to_image(win->mlx_ptr, collect);
	win->texture.exit  = mlx_texture_to_image(win->mlx_ptr, exit_texture);
	win->cover_tile.cover  = mlx_texture_to_image(win->mlx_ptr, grass);
}

int32_t main(void)
{
	mlx_texture_t*	character;
	t_win			win;
	
	win.collect.numberOfCollectables = 0;
	win.moves_number = 1;
	character = mlx_load_png("./textures/character.png");
	determine_map_size(&win);
	initialize_textures(&win);
	win.texture.character = mlx_texture_to_image(win.mlx_ptr, character);
	render_map(&win);
  	check_if_passable(&win);
	mlx_key_hook(win.mlx_ptr, &my_keyhook, &win);
	mlx_loop(win.mlx_ptr);
	mlx_terminate(win.mlx_ptr);
	return (EXIT_SUCCESS); 
}

//mlx_set_setting(MLX_MAXIMIZED, false);
//cc test3.c libmlx42.a  -ldl -lglfw -pthread -lm && ./a.out