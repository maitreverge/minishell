/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/05 12:37:29 by glambrig         ###   ########.fr       */
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
void	child(int *fds, char *cmd, char **envp, bool is_last_cmd)
{
	char 	**av;
	char	*join;

	av = ft_split(cmd, ' ');
	if (is_last_cmd == false)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			free(av);
			exit(EXIT_FAILURE);
		}
		close(fds[1]);
	}
	//close(fds[0]);///
	join = ft_strjoin("/bin/", av[0]);
	av[0] = join;
	if (execve(av[0], av, envp) < 0)
	{
		ft_putstr_fd("failed, file=", 2);
		ft_putendl_fd(join, 2);
		perror("execve");
		free(fds);
		free(join);
		exit(EXIT_FAILURE);
	}
}

/*
	cmds: A null terminated array of commands that are to be piped
*/
void	pipes(char **cmds, char **envp)
{
	int	len; // The numbers of commands that we get
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
			if (i == len - 1)
				child(fds[i], cmds[i], envp, true);
			else
				child(fds[i], cmds[i], envp, false);
			close(fds[i][0]);	//Close fds for parent process,
			close(fds[i][1]);	//but not for child
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
	free(ch_pid);
	free_arr((void **)fds, len);
}
