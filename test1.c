#include "include/MLX42/MLX42.h"
#include "so_long.h"

void assignPlayerPos(t_win *win, int y, int x)
{
	win->pos_player.pos_x = x;
	win->pos_player.pos_y = y;
	win->map.map[y][x] = '0';
}

void RenderAndAssignExitPos(t_win *win, int y, int x)
{
	win->exit_tile.pos_x = x;
	win->exit_tile.pos_y = y;
	win->map.map[y][x] = '0';
	if (mlx_image_to_window(win->mlx_ptr, win->texture.exit, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void RenderAndAssignCollPos(t_win *win, int y, int x, char map_byte)
{
	win->map.map[y][x] = map_byte;
	win->collect.numberOfCollectables++;
	if (mlx_image_to_window(win->mlx_ptr, win->texture.collect, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void renderTheWall(t_win *win, int y, int x)
{	
	if (mlx_image_to_window(win->mlx_ptr, win->texture.wall, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void renderTheFloor(t_win *win, int y, int x)
{	
	if (mlx_image_to_window(win->mlx_ptr, win->texture.floor, x * 32, y * 32) < 0)
		exit(EXIT_FAILURE);
}

void letsTry(t_win *win, char map_byte, int ix, int iy)
{
	if (map_byte == 'P')
	{
		renderTheFloor(win, iy, ix);
		assignPlayerPos(win, iy, ix);
	}
	else if (map_byte == 'E')
		RenderAndAssignExitPos(win, iy, ix);
	else if (map_byte == 'C')
		RenderAndAssignCollPos(win, iy, ix, map_byte);
	else if (map_byte == '0')
	{
		win->map.map[iy][ix] = map_byte;
		renderTheFloor(win, iy, ix);
	}
	else 
	{
		win->map.map[iy][ix] = map_byte;
		renderTheWall(win, iy, ix);
	}
}

void checkTileConditions(t_win *win)
{
	//checkConditions(win);
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

void renderCoverTiles(t_win *win)
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

void renderTheMap(void *param) 
{
	int fd;
	char buffer[1];
	char map_byte;
	ssize_t bytesRead;
	int ix;
	int iy;

	t_win *win;
	win = param;
	ix = 0;
	iy = 0;

	fd = open("map.ber", O_RDONLY);
	while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
	{
		map_byte = buffer[0];
		if (map_byte == '\n')
		{
			ix = -1;
			iy++;
		} 
		else
			letsTry(win, map_byte, ix, iy);
		ix++;
	}
	renderCoverTiles(win);
	if (mlx_image_to_window(win->mlx_ptr, win->texture.character, win->pos_player.pos_x * 32, win->pos_player.pos_y* 32) < 0)
		exit(EXIT_FAILURE);
	close(fd);
}

void my_keyhook(mlx_key_data_t keydata, void *param)
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
    {
        win->pos_player.pos_y = new_y;
        win->pos_player.pos_x = new_x;
        win->texture.character->instances[0].y = new_y * 32;
        win->texture.character->instances[0].x = new_x * 32;
    }
	checkTileConditions(win);
}

void initializeTextures(t_win *win)
{
	win->mlx_ptr = mlx_init(win->map.cols * 32, win->map.rows * 32, "Shitcircus", true);
	if (!win->mlx_ptr)
		exit(EXIT_FAILURE);
	mlx_texture_t* wall_texture = mlx_load_png("./textures/wall.png");
	mlx_texture_t* grass = mlx_load_png("./textures/grass.png");
	mlx_texture_t* character = mlx_load_png("./textures/character.png");
	mlx_texture_t* collect = mlx_load_png("./textures/collect.png");
	mlx_texture_t* exit_texture = mlx_load_png("./textures/exit.png");
	mlx_texture_t* cover = mlx_load_png("./textures/grass.png");
	if (!wall_texture || !grass || !character || !collect || !exit_texture)
		exit(EXIT_FAILURE);
	win->texture.floor = mlx_texture_to_image(win->mlx_ptr, grass);
	win->texture.wall  = mlx_texture_to_image(win->mlx_ptr, wall_texture);
	win->texture.character  = mlx_texture_to_image(win->mlx_ptr, character);
	win->texture.collect  = mlx_texture_to_image(win->mlx_ptr, collect);
	win->texture.exit  = mlx_texture_to_image(win->mlx_ptr, exit_texture);
	win->cover_tile.cover  = mlx_texture_to_image(win->mlx_ptr, grass);
}

void mallocTheMap(t_win *win, int ix, int iy)
{
	int i;

	i = 0;
	win->map.rows = iy;
	win->map.map = (char **)malloc(win->map.rows * sizeof(char *));
    while (i < win->map.rows) 
	{
        win->map.map[i] = (char *)malloc(win->map.cols * sizeof(char));
		i++;
    }
}

void determineMapSize(t_win *win)
{
	int fd;
	char buffer[1];
	char map_byte;
	ssize_t bytesRead;
	int ix;
	int iy;

	ix = 0;
	iy = 0;
	fd = open("map.ber", O_RDONLY);
	if (fd == -1) 
	{
		puts("Error: could not open the map.");
		exit(EXIT_FAILURE);
	}
	while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
	{
		map_byte = buffer[0];
		win->map.cols = ix;
		if (map_byte == '\n')
		{
			ix = -1;
			iy++;
		}
		ix++;
	}
	mallocTheMap(win, ix, iy);
	if (bytesRead == -1) 
	{
		perror("Error reading from file"); // CHANGE !
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1) 
	{
		perror("Error closing file"); // CHANGE!!
		exit(EXIT_FAILURE);
	}
}

int32_t main(void)
{
	t_win		win;
	int			countMoves;
	
	countMoves = 0;
	win.collect.numberOfCollectables = 0;
	determineMapSize(&win);
 	//mlx_set_setting(MLX_MAXIMIZED, false);
	initializeTextures(&win);
	renderTheMap(&win);
/*   	if (!checkIfPassable(&win))
	{
		printf("Wrong map file");
		EXIT_FAILURE;
	}  */
 	mlx_key_hook(win.mlx_ptr, &my_keyhook, &win);
	mlx_loop(win.mlx_ptr);
	mlx_terminate(win.mlx_ptr);
	return (EXIT_SUCCESS); 
}

//cc test.c libmlx42.a  -ldl -lglfw -pthread -lm && ./a.out