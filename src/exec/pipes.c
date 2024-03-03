/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/03 18:39:50 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Allocates space for fds and child pid array,
		and creates the pipe links in fds
*/
int	**create_pipes(t_pars **lst, pid_t **ch_pid, int *main_i)
{
	int		len;
	int		i;
	int		**fds;

	len = lstlen(*lst) - num_of_pipes(*lst);
	*ch_pid = ft_calloc(sizeof(pid_t), len);
	fds = ft_calloc(sizeof(int *), len + 1);
	fds[len] = NULL;
	i = 0;
	*main_i = 0;
	while (i < len)
	{
		fds[i] = ft_calloc(sizeof(int), 2);
		if (pipe(fds[i]) == -1)
		{
			perror("pipe");
			free_t_pars(lst);
			free_arr((void **)fds, size_of_ptr_ptr((void **)fds));
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fds);
}

int	pipes_child_func(t_pars **lst, t_all *all, int input, t_pipe pippy)
{
	if (input != -1)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if ((*lst)->next != NULL)
	{
		dup2(pippy.fds[pippy.i][1], STDOUT_FILENO);
		close(pippy.fds[pippy.i][1]);
	}
	close(pippy.fds[pippy.i][0]);
	free_arr((void **)pippy.fds, size_of_ptr_ptr((void **)pippy.fds));
	if ((*lst)->cmd->is_builtin == true)
		exec_builtin(*lst, all, 0);
	else
	{
		if (!(*lst)->cmd->command_path)
		{
			printf("Command not found\n");
			return (g_last_exit_status = 127, 0);
		}
		execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args,
			all->copy_envp);
	}
	// return (free_full_t_pars(lst), exit(0), 0);
	return (exit(0), 0);
}

/*
	Handles the pipe '|' operator.
	Input_fd is -1 when pipes() called for the first time,
		meaning we don't redirect STDIN this iteration.
*/
int	pipes(t_pars **lst, t_all *all, int input_fd)
{
	t_pipe	pippy;

	t_pars	*cur;
	cur = *lst;

	pippy.fds = create_pipes(lst, &pippy.ch_pid, &pippy.i);
	while (cur != NULL && cur->is_command == true)
	{
		if (pipes_helper_1(lst, all, input_fd) == 1)
			break ;
		pippy.ch_pid[pippy.i] = fork();
		pipes_helper_2(lst, all, pippy, input_fd);
		input_fd = pippy.fds[pippy.i++][0];
		if (cur->next && cur->next->is_operator == true
			&& cur->next->operator->pipe == true)
			cur = cur->next->next; // leaks comes from the old version where you played with the whole struct
		else
		{
			pipes_helper_3(lst, all);
			break ;
		}
	}
	while (pippy.i-- > 0)
		wait(NULL);
	return (free_arr((void **)pippy.fds, size_of_ptr_ptr((void **)pippy.fds)),
		free(pippy.ch_pid), input_fd);
}
