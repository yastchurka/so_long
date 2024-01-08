#include "so_long.h"

void    move_up(t_win *win)
{
	int		new_y;
    int		new_x;

	new_y = win->pos_player.pos_y;
	new_x = win->pos_player.pos_x;
	new_y--;
    if (win->map.map[new_y][new_x] != '1')
    {
        win->pos_player.pos_y = new_y;
        win->pos_player.pos_x = new_x;
        win->texture.character->instances[0].y = new_y * 32;
        win->texture.character->instances[0].x = new_x * 32;
		printf("Moves moved: %d\n", win->moves_number++ );
    }
}

void    move_down(t_win *win)
{
	int		new_y;
    int		new_x;

	new_y = win->pos_player.pos_y;
	new_x = win->pos_player.pos_x;
	new_y++;
	if (win->map.map[new_y][new_x] != '1')
    {
        win->pos_player.pos_y = new_y;
        win->pos_player.pos_x = new_x;
        win->texture.character->instances[0].y = new_y * 32;
        win->texture.character->instances[0].x = new_x * 32;
		printf("Moves moved: %d\n", win->moves_number++ );
    }
}

void    move_left(t_win *win)
{
	int		new_y;
    int		new_x;

	new_y = win->pos_player.pos_y;
	new_x = win->pos_player.pos_x;
	new_x--;
	if (win->map.map[new_y][new_x] != '1')
    {
        win->pos_player.pos_y = new_y;
        win->pos_player.pos_x = new_x;
        win->texture.character->instances[0].y = new_y * 32;
        win->texture.character->instances[0].x = new_x * 32;
		printf("Moves moved: %d\n", win->moves_number++ );
    }
}

void    move_right(t_win *win)
{
	int		new_y;
    int		new_x;

	new_y = win->pos_player.pos_y;
	new_x = win->pos_player.pos_x;
	new_x++;
	if (win->map.map[new_y][new_x] != '1')
    {
        win->pos_player.pos_y = new_y;
        win->pos_player.pos_x = new_x;
        win->texture.character->instances[0].y = new_y * 32;
        win->texture.character->instances[0].x = new_x * 32;
		printf("Moves moved: %d\n", win->moves_number++ );
    }
}