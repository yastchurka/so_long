#include "so_long.h"

void	open_map_file(int *fd)
{
	*fd = open("map.ber", O_RDONLY);
	if (*fd == -1)
	{
		perror("Error: could not open the map.");
		exit(EXIT_FAILURE);
	}
}

void	close_map_file(int fd)
{
	if (close(fd) == -1)
	{
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
}

void	malloc_map(t_win *win, int ix, int iy)
{
	int	i;

	i = 0;
	win->map.rows = iy;
	win->map.map = (char **)malloc(win->map.rows * sizeof(char *));
    while (i < win->map.rows) 
	{
        win->map.map[i] = (char *)malloc(win->map.cols * sizeof(char));
		i++;
    }
}

void	read_update_map(t_win *win, int *ix, int *iy, ssize_t bytesRead, char map_byte)
{
    win->map.cols = *ix;
    if (map_byte == '\n') {
        *ix = -1;
        (*iy)++;
    }
    (*ix)++;
}

void	determine_map_size(t_win *win)
{
	int		fd;
	char	buffer[1];
	char	map_byte;
	ssize_t	bytesRead;
	int		ix;
	int		iy;

	ix = 0;
	iy = 0;
	open_map_file(&fd);
	while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
	{
		map_byte = buffer[0];
		read_update_map(win, &ix, &iy, bytesRead, map_byte);
	}
	malloc_map(win, ix, iy);
	if (bytesRead == -1) 
	{
		perror("Error reading from file"); // CHANGE !
		close(fd);
		exit(EXIT_FAILURE);
	}
	close_map_file(fd);
}