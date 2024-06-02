#include "pipex.h"

void	execute(char *cmd, char **env)
{
	char	**f_cmds;
	char	*path;

	f_cmds = ft_split(cmd, ' ');
	path = find_path(f_cmds[0], env);
	if (execve(path, f_cmds, env) == -1)
	{
		ft_putstr_fd("LOL! THIS COMMAND DOES NOT EXIST: ", 2);
		ft_putendl_fd(f_cmds[0], 2);
		free_arr(f_cmds);
		free(path);
		exit(1);
	}
}

void	child(char **av, char **env, int *fd)
{
	int	f;

	f = open(av[1], O_RDONLY);
	if (f == -1)
		exit(1);
	close(fd[0]);
	dup2(f, 0);
	dup2(fd[1], 1);
	execute(av[2], env);
}

void	parent(char **av, char **env, int *fd)
{
	int	f;

	f = open(av[4], O_WRONLY | O_CREAT, 0777);
	if (f == -1)
		exit(1);
	close(fd[1]);
	dup2(f, 1);
	dup2(fd[0], 0);
	execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	id;

	if (ac != 5)
	{
		ft_putstr_fd("WRONG FORMAT!\n", 2);
		ft_putendl_fd("CORRECT FORMAT: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	if (pipe(fd) == -1)
		exit(1);
	id = fork();
	if (id == -1)
		exit(1);
	if (id == 0)
		child(av, env, fd);
	parent(av, env, fd);
}
