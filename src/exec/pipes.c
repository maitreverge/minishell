/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/29 13:23:00 by glambrig         ###   ########.fr       */
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
    int 	**fds;

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

void	pipes_child_func(t_pars **lst, t_all *all, int input_fd, int **fds, int i)
{
	if (input_fd != -1)
    {
		dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if ((*lst)->next != NULL)//If it's not the last node, we redirect STDOUT
	{
		dup2(fds[i][1], STDOUT_FILENO);
		close(fds[i][1]);
	}
    close(fds[i][0]);	//We close Read end of pipe because we never use it. We only use input_fd/STDIN.
	free_arr((void **)fds, size_of_ptr_ptr((void **)fds));
	if ((*lst)->cmd->isBuiltin == true)
		exec_builtin(*lst, all, 0);
	else
	{
		if (!(*lst)->cmd->command_path)
		{
			printf("Command not found\n");
			lstfirst(*lst)->last_exit_status = 127;
		}
		else
			execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args, all->copy_envp);
	}
	free_full_t_pars(lst);
	exit(0);
}

/*
	Handles the pipe '|' operator.
	Input_fd is -1 when pipes() called for the first time,
		meaning we don't redirect STDIN this iteration.
*/
int	pipes(t_pars **lst, t_all *all, int input_fd)
{
    int 	i;
    int 	**fds;
    pid_t 	*ch_pid;

	fds = create_pipes(lst, &ch_pid, &i);
    while ((*lst) != NULL && (*lst)->isCommand == true)
	{
		if (check_next_operator(*lst) == 4)
		{
				redirect_output(lst, all, input_fd);
				break ;
		}
        ch_pid[i] = fork();
        if (ch_pid[i] == 0)
			pipes_child_func(lst, all, input_fd, fds, i);
        else if (ch_pid[i] < 0)
			fork_error(fds, &ch_pid);
        if (ch_pid[i] > 0 && i > 0)
            close(fds[i - 1][0]);
		close(fds[i][1]);
        input_fd = fds[i++][0];
		if ((*lst)->next && (*lst)->next->isOperator == true && (*lst)->next->operator->pipe == true)
			(*lst) = (*lst)->next->next;	//to skip the pipe operator and go to the next cmd
		else
		{
			if (check_next_operator(*lst) == 2)
				redirect_input(lst, all);
			else if (check_next_operator(*lst) == 3)
				redirect_input_delimitor(lst, all);
			break ;
		}
    }
	free_arr((void **)fds, size_of_ptr_ptr((void **)fds));
	while (i-- > 0)
		wait(NULL);
	free(ch_pid);
	return (input_fd);
}
