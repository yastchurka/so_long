//cc so_long.c libmlx42.a -Iinclude -ldl -lglfw -pthread -lm && ./a.out
#include "so_long.h"

void display_map(void *param) {
	t_win *win;
	int y;
	int x;

	y = 0;
	win = param;
	while (y < ROWS) 
	{
		x = 0;
		while (x < COLS) 
		{
			if (x == win->pos_player.pos_x && y == win->pos_player.pos_y)
			win->map.map[y][x] = 'P';
			else if (!(x == win->pos_player.pos_x && y == win->pos_player.pos_y) &&
				win->map.map[y][x] == 'P')
					win->map.map[y][x] = '0';
			printf("%c", win->map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void checkIfSerroundedByOnes(void *param)
{
	t_win *win;
	int x;
	int y;
	
	win = param;
	x = 0;
	y = 0;
	while (x < COLS)
	{
		if (win->map.map[0][x] != '1' || win->map.map[ROWS - 1][x] != '1' )
		{
			printf("The map is fucked!"); // add the exit err
			exit(EXIT_FAILURE);
		}
		x++;
	}
	while (y < ROWS)
	{
		if (win->map.map[y][0] != '1' || win->map.map[y][COLS - 1] != '1')
		{
			printf("The map is fucked!");
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

void checkOtherSignes(void *param)
{
	t_win *win;
	win = param;

	int x;
	int y;

	y = 0;
	if (COLS < ROWS)
	{
		printf("Your map is fucked.");
		exit(EXIT_FAILURE);
	}
	while (y < ROWS)
	{
		x = 0;
		while (x < COLS)
		{
			if (win->map.map[y][x] != '1' && win->map.map[y][x] != '0' 
			&& win->map.map[y][x] != 'P' && win->map.map[y][x] != 'C'
			 && win->map.map[y][x] != 'E')
				{
					printf("Your map is fucked.");
					exit(EXIT_FAILURE);
				}
				x++;
		}
		y++;
	}
}

void checkConditions(void *param)
{
	t_win *win;
	win = param;

	checkOtherSignes(win);
	checkIfSerroundedByOnes(win);
}

void checkTileConditions(void *param) {
	t_win *win;
	win = param;
	
	checkConditions(win);
	if (win->map.map[win->pos_player.pos_y][win->pos_player.pos_x] == 'C') 
	{
		win->collect.numberOfCollectables--;
		win->map.map[win->pos_player.pos_y][win->pos_player.pos_x] = '0';
	}
	if (win->exit_tile.pos_x == win->pos_player.pos_x &&
			win->exit_tile.pos_y == win->pos_player.pos_y) 
	{
		if (win->collect.numberOfCollectables == 0)
		{
			printf("You won!\n");
			exit(0);
		}
	}
}

bool dfs(t_win *win, bool visited[ROWS][COLS], int row, int col) 
{
	if (win->exit_tile.pos_x == col && win->exit_tile.pos_y == row)
			return true; // Path found
	if (row < 1 || row >= ROWS - 1 || col < 1 || col >= COLS - 1 ||
		win->map.map[row][col] == '1' || visited[row][col])
			return false; // Out of bounds or obstacle or already visited
	visited[row][col] = true;
	if (dfs(win, visited, row - 1, col) ||
		dfs(win, visited, row + 1, col) ||
		dfs(win, visited, row, col - 1) ||
		dfs(win, visited, row, col + 1)) 
			return true; // Path found in one of the directions
	return false;
}

bool checkIfPassable(void *param) {
	t_win *win;
	bool visited[ROWS][COLS];
	int x;
	int y;

	y = 0;
	win = param;
	if (win->pos_player.pos_y < 1 || win->pos_player.pos_y >= ROWS ||
		win->pos_player.pos_x < 1 || win->pos_player.pos_x >= COLS ||
		win->exit_tile.pos_x < 1 || win->exit_tile.pos_y >= ROWS ||
		win->exit_tile.pos_y < 1 || win->exit_tile.pos_x >= COLS)
			return false;
	while (y < ROWS)
	{
		x = 0;
		while (x < COLS) 
		{
			visited[y][x] = false;
			x++;
		}
		y++;
	}
	return dfs(win, visited, win->pos_player.pos_y, win->pos_player.pos_x);
}

void assignPlayerPos(void *param, int ix, int iy)
{
	t_win *win;
	win = param;

	win->pos_player.pos_x = ix;
	win->pos_player.pos_y = iy;
	win->map.map[iy][ix] = '0';
}

void assignExitPos(void *param, int ix, int iy)
{
	t_win *win;
	win = param;

	win->exit_tile.pos_x = ix;
	win->exit_tile.pos_y = iy;
	win->map.map[iy][ix] = '0';
}

void assignCollPos(void *param, int ix, int iy, char map_byte)
{
	t_win *win;
	win = param;

	win->map.map[iy][ix] = map_byte;
	win->collect.numberOfCollectables++;
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
	win->collect.numberOfCollectables = 0;

	fd = open("map.ber", O_RDONLY);
	if (fd == -1) 
	{
		puts("Error: could not open the map.");
		exit(EXIT_FAILURE);
	}
	while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
	{
		map_byte = buffer[0];
		if (map_byte == 'P') 
			assignPlayerPos(win, ix, iy);
		if (map_byte == 'E') 
			assignExitPos(win, ix, iy);
		if (map_byte == 'C') 
			assignCollPos(win, ix, iy, map_byte);
		if (map_byte == '\n') 
		{
			ix = -1;
			iy++;
		} 
		else
			win->map.map[iy][ix] = map_byte;
		ix++;
	}
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
/* 	t_win win;
	char input;
	int countMoves; */
	
	mlx_t* mlx;
	mlx_loop(mlx);
	//mlx_terminate(mlx);
	return (EXIT_SUCCESS);

/*
	renderTheMap(&win);
	display_map(&win);
	countMoves = 0;
 	if (!checkIfPassable(&win))
	{
		printf("Wrong map file");
		EXIT_FAILURE;
	}
	while (1) 
	{
		scanf(" %c", &input);
		if (input == 'e') 
		{
			printf("Exiting the loop.\n");
			break;
		} 
		else if (input == 'w' 
			&& win.map.map[win.pos_player.pos_y - 1][win.pos_player.pos_x] != '1')
					win.pos_player.pos_y--;
		else if (input == 's' 
			&& win.map.map[win.pos_player.pos_y + 1][win.pos_player.pos_x] != '1')
					win.pos_player.pos_y++;
		else if (input == 'a' 
			&& win.map.map[win.pos_player.pos_y][win.pos_player.pos_x - 1] != '1')
					win.pos_player.pos_x--;
		else if (input == 'd' 
			&& win.map.map[win.pos_player.pos_y][win.pos_player.pos_x + 1] != '1')
					win.pos_player.pos_x++;
		countMoves++;
		printf("COLL: %d\n", win.collect.numberOfCollectables);
		printf("MOVES: %d\n", countMoves);
		checkTileConditions(&win);
		display_map(&win);
	} */
}