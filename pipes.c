/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/03 00:28:57 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execute ls, result goes to fds[0]
// void	child(int *fds)
// {
// 	int old_stdout;
// 	char *av[] = {"/usr/bin/ls", NULL};
// 	char **envp = {NULL};

// 	old_stdout = dup(STDOUT_FILENO);
// 	dup2(fds[1], STDOUT_FILENO);
// 	close(fds[0]);
// 	close(fds[1]);
// 	execve(av[0], av, envp);

// 	perror("execve");
// 	dup2(old_stdout, STDOUT_FILENO);
// 	exit(EXIT_FAILURE);
// }

// //ls | rev

// //dup, dup2, pipe, execve
// int	main(void)
// {
// 	int fds[2];
// 	int ch_pid;
// 	char *av[] = {"/usr/bin/rev", NULL};
// 	char **envp = {NULL};

// 	pipe(fds);	//connects the two fds
// 	ch_pid = fork();
// 	if (ch_pid == 0) //it's the child
// 		child(fds);
// 	else if (ch_pid == -1)
// 		return (perror("lmao"), exit(0), 1);
// 	waitpid(ch_pid, NULL, 0);
// 	ch_pid = fork();
// 	if (ch_pid == 0) //it's the child
// 	{
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[1]);
// 		close(fds[0]);
// 		execve(av[0], av, envp);
// 	}
// 	close(fds[1]);
// 	close(fds[0]);
// 	waitpid(ch_pid, NULL, 0);
// 	return (0);
// }

/*Executes the command, and sends its output to fd[1]*/
void	child(int *fds, char *cmd)
{
	char 	**av;
	char 	*envp[1];
	char	*join;
	int		len;

	printf("IN CHILD\n");/////
	av = ft_split(cmd, ' ');
	envp[0] = NULL;
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free(av);
		exit(1);
	}
	printf("ONE\n");/////
	close(fds[1]);
	close(fds[0]);///
		printf("TWO\n");/////
	join = ft_strjoin("/bin/", cmd);
	printf("join=%s\n", join);///////////////
	if (execve(join, av, envp) < 0)
	{
		len = 0;
		while (&fds[len])
			len++;
		free_arr((void **)&fds, len);
		free(join);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

/*
	cmds: A null terminated array of commands that are to be piped
*/
void	pipes(char **cmds)
{
	int	len;
	int	i;
	int	*ch_pid;
	int	**fds;

	len = 0;
	while (cmds[len])
		len++;
	ch_pid = ft_calloc(len + 1, sizeof(int));
	fds = ft_calloc(len * 2, sizeof(int *));
	i = 0;
	while(i < len)
		fds[i++] = ft_calloc(2 + 1, sizeof(int));
	// i = 0;
	// while (i < len)
	// {
	// 	if (pipe(fds[i]) < 0)	//Creating the connection between to two fds
	// 	{
	// 		free_arr((void **)fds, len);
	// 		perror("pipe");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	i++;
	// }
	i = 0;
	while (i < len)
	{
		ch_pid[i] = fork();
		if (ch_pid[i] < 0)
		{
			free_arr((void **)fds, len);
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (ch_pid[i] == 0)
		{
			if (pipe(fds[i]) < 0)
			{
				free_arr((void **)fds, len);
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			child(fds[i], cmds[i]);
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		wait(NULL);
		// waitpid(ch_pid[i], NULL, 0);
		i++;		
	}
	i = 0;
	while (i < len)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	free(ch_pid);
	free_arr((void **)fds, len);
}
