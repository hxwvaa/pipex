#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	free_arr(char **arr);
size_t	ft_strcmp(char *s1, char *s2);
char	*path(char **env);
char	*find_path(char *cmd, char **env);

#endif
