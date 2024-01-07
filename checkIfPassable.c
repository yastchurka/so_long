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

void	check_conditions(void *param)
{
	t_win	*win;

	win = param;
	check_other_signes(win);
	check_if_serrounded_by_ones(win);
}

bool	dfs(t_win *win, bool visited[win->map.rows][win->map.cols], int row, int col)
{
	if (win->exit_tile.pos_x == col && win->exit_tile.pos_y == row)
		return (true);
	if (row < 1 || row >= win->map.rows - 1 || col < 1 
		|| col >= win->map.cols - 1 || win->map.map[row][col] == '1' 
		|| visited[row][col])
		return (false);
	visited[row][col] = true;
	if (dfs(win, visited, row - 1, col) 
		|| dfs(win, visited, row + 1, col)
		|| dfs(win, visited, row, col - 1)
		|| dfs(win, visited, row, col + 1)) 
		return (true);
	return (false);
}

bool	check_if_passable(t_win *win)
{
	bool	visited[win->map.rows][win->map.cols];
	int		x;
	int		y;

	y = 0;
	check_conditions(win);
	if (win->pos_player.pos_y < 1 || win->pos_player.pos_y >= win->map.rows 
		|| win->pos_player.pos_x < 1 || win->pos_player.pos_x >= win->map.cols
		|| win->exit_tile.pos_x < 1 || win->exit_tile.pos_y >= win->map.rows 
		|| win->exit_tile.pos_y < 1 || win->exit_tile.pos_x >= win->map.cols)
		return (false);
	while (y < win->map.rows)
	{
		x = 0;
		while (x < win->map.cols) 
		{
			visited[y][x] = false;
			x++;
		}
		y++;
	}
	return (dfs(win, visited, win->pos_player.pos_y, win->pos_player.pos_x));
}
