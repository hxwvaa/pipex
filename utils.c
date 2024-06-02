#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

size_t	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*path(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		str = ft_substr(env[i], 0, j);
		if (ft_strcmp("PATH", str) == 0)
		{
			free(str);
			return (env[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	char	**cmds;
	int		i;

	i = 0;
	paths = ft_split(path(env), ':');
	cmds = ft_split(cmd, ' ');
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmds[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_arr(cmds);
			free_arr(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_arr(cmds);
	free_arr(paths);
	return (cmd);
}
