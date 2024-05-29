#include "pipex.h"

int	main(int ac, char **av)
{
	int		fd[2];
	pid_t	id;

	if (pipe(fd) == -1)
		exit(-1);
	id = fork();
	if (id == -1)
		exit(-1);
	open();
}
