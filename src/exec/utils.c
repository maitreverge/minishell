/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:34:17 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/02 10:15:42 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	num_of_pipes(t_pars *lst)
{
	size_t	len;
	t_pars	*temp;

	temp = lst;
	len = 0;
	while (lst)
	{
		if (lst->is_operator && lst->operator->pipe == true)
			len++;
		lst = lst->next;
	}
	lst = temp;
	return (len);
}

void	fork_error(int **fds, pid_t **ch_pid)
{
	perror("fork");
	free_arr((void **)fds, size_of_ptr_ptr((void **)fds));
	free(*ch_pid);
	exit(EXIT_FAILURE);
}

/*
	Deletes the t_pars node passed as an arg, and the next one.
	Rearranges the pointers to not lose the rest of the list.
*/
void	del_t_pars_node(t_pars *lst)
{
	if (lst->is_command == true)
	{
		free(lst->cmd->command_name);
		free(lst->cmd->command_path);
		free_arr((void **)lst->cmd->name_options_args,
			size_of_ptr_ptr((void **)lst->cmd->name_options_args));
		free(lst->cmd);
	}
	else if (lst->is_file == true)
	{
		free(lst->fl->file_name);
		free(lst->fl);
	}
	lst->prev->next = lst->next;
}

int	num_of_out_redirs(t_pars *lst)
{
	int		len;
	t_pars	*temp;

	temp = lst;
	len = 0;
	while (lst)
	{
		if (lst->is_operator && (lst->operator->redir_out == true
				|| lst->operator->redir_out_app == true))
			len++;
		lst = lst->next;
	}
	lst = temp;
	return (len);
}
