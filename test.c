#include "minishell.h"

int	main(int ac, char **av)
{
	int fd[2];
	int	*ch_pid;
	ch_pid = ft_calloc(sizeof(int), 2);
	char **gg;
	char **hh;

	gg = ft_split(av[1], ' ');
	hh = ft_split(av[2], ' ');
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ch_pid[0] = fork();
	if (ch_pid[0] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (ch_pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(gg[0], gg, NULL);
	}
	ch_pid[1] = fork();
	if (ch_pid[1] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (ch_pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(hh[0], hh, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);


	///Freeing
	int i = 0;
	while (gg[i])
		free(gg[i++]);
	free(gg);
	i = 0;
	while (hh[i])
		free(hh[i++]);
	free(hh);
}