#include "pipex_bonus.h"

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

void	create_pipe(char *cmd, char **env)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		exit(4);
	id = fork();
	if (id == -1)
		exit(4);
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execute(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int	out;
	int	in;
	int	i;

	i = 2;
	if (ac < 5)
	{
		ft_putstr_fd("WRONG FORMAT!\n", 2);
		ft_putstr_fd("CORRECT FORMAT: ", 2);
		ft_putendl_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
		exit(1);
	}
	in = open(av[1], O_RDONLY);
	out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(in, 0);
	while (i < ac - 2)
		create_pipe(av[i++], env);
	dup2(out, 1);
	execute(av[ac - 2], env);
}
