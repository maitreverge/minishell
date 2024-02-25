/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/25 15:10:39 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Allocates space for fds and child pid array,
		and creates the pipe links in fds
*/
int	**create_pipes(t_pars **lst, pid_t **ch_pid)
{
    int		len;
    int		i;
    int 	**fds;

	len = lstlen(*lst) - num_of_pipes(*lst);
	*ch_pid = ft_calloc(sizeof(pid_t), len);
	fds = ft_calloc(sizeof(int *), len);
	i = 0;
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
	t_pars *first_node;

	first_node = lstfirst(*lst);
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
	if ((*lst)->cmd->isBuiltin == true)
		exec_builtin(*lst, all);
	else
	{
		if (!(*lst)->cmd->command_path)
		{
			printf("Command not found\n");
			first_node->last_exit_status = 127;
		}
		else
			execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args, NULL);
	}
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
    int 	len;
    int 	**fds;
    pid_t 	*ch_pid;

	i = 0;
	fds = create_pipes(lst, &ch_pid);
    while ((*lst) != NULL && (*lst)->isCommand == true)
	{
        ch_pid[i] = fork();
        if (ch_pid[i] == 0)
			pipes_child_func(lst, all, input_fd, fds, i);
        else if (ch_pid[i] < 0)
			fork_error(fds, &ch_pid);
        if (ch_pid[i] > 0 && i > 0)
            close(fds[i - 1][0]);
    	close(fds[i][1]);
        input_fd = fds[i++][0];
		if ((*lst)->next && (*lst)->next->isOperator == true && (*lst)->next->operator->pipe == true && (*lst)->next->next)
			(*lst) = (*lst)->next->next;	//to skip the pipe operator and go to the next cmd
		else
		{
			if (check_next_operator(*lst) == 2)
				redirect_input(lst);
			else if (check_next_operator(*lst) == 3)
				redirect_input_delimitor(lst);
			else if (check_next_operator(*lst) == 4)
				redirect_output(lst, all, input_fd);
			break ;
		}
    }
	len = 0;
	while (ch_pid[len])
		len++;
    while (len > 0)
	{
		wait(NULL);
		len--;
	}
	free(ch_pid);
	return (input_fd);
}
