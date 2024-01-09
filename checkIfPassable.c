/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkIfPassable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralukasi <ralukasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:59:57 by ralukasi          #+#    #+#             */
/*   Updated: 2024/01/07 15:13:26 by ralukasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_if_serrounded_by_ones(t_win *win)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < win->map.cols)
	{
		if (win->map.map[0][x] != '1' 
			|| win->map.map[win->map.rows - 1][x] != '1' )
		{
			printf("The map is fucked!");
			exit(EXIT_FAILURE);
		}
		x++;
	}
	while (y < win->map.rows)
	{
		if (win->map.map[y][0] != '1' 
			|| win->map.map[y][win->map.cols - 1] != '1')
		{
			printf("The map is fucked!");
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

void	check_other_signes(t_win *win)
{
	int	x;
	int	y;

	y = 0;
	if (win->map.cols < win->map.rows)
	{
		printf("Your map is fucked.");
		exit(EXIT_FAILURE);
	}
	while (y < win->map.rows)
	{
		x = 0;
		while (x < win->map.cols)
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

void	check_if_passable(void *param)
{
	t_win	*win;

	win = param;
	int col = win->pos_player.pos_x;
    int row = win->pos_player.pos_y;
	check_other_signes(win);
	check_if_serrounded_by_ones(win);
	if (!dfs(win, row, col))
		exit(EXIT_FAILURE);
}

bool	dfs(t_win *win, int row, int col)
{
	
    char original_value = win->map.map[row][col]; // Save the original value
    win->map.map[row][col] = 'V'; // Mark the cell as visited

    if (win->exit_tile.pos_x == col && win->exit_tile.pos_y == row)
	{
        win->map.map[row][col] = original_value; // Revert back to original value
        return true; // Path found
    }
    if (row < 1 || row >= win->map.rows - 1 || col < 1 || col >= win->map.cols - 1 ||
        original_value == '1' || original_value == 'V') {
        win->map.map[row][col] = original_value; // Revert back to original value
        return false; // Out of bounds, obstacle, or already visited
    }
    if (dfs(win, row - 1, col) || dfs(win, row + 1, col) 
		|| dfs(win, row, col - 1) || dfs(win, row, col + 1)) 
        return true; // Path found in one of the directions
    win->map.map[row][col] = original_value; // Revert back to original value
	return false;
}

	/* if (win->pos_player.pos_y < 1 || win->pos_player.pos_y >= win->map.rows 
		|| win->pos_player.pos_x < 1 || win->pos_player.pos_x >= win->map.cols
		|| win->exit_tile.pos_x < 1 || win->exit_tile.pos_y >= win->map.rows 
		|| win->exit_tile.pos_y < 1 || win->exit_tile.pos_x >= win->map.cols)
		exit(EXIT_FAILURE); */
