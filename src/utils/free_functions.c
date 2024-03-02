/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:40:52 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 12:09:12 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_cmd_node(t_pars *to_free)
{
	free(to_free->cmd->command_name);
	if (to_free->cmd->command_path)
		free(to_free->cmd->command_path);
	free_split(to_free->cmd->name_options_args);
	free(to_free->cmd);
}

// ! Function free every node of t_pars except the first one
void	free_t_pars(t_pars **pars)
{
	t_pars	*first_node;
	t_pars	*to_free;
	t_pars	*temp;

	first_node = lstfirst(*pars);
	to_free = first_node->next;
	first_node->next = NULL;
	while (to_free)
	{
		temp = to_free;
		if (to_free->is_command && to_free->cmd)
			free_cmd_node(to_free);
		else if (to_free->is_file && to_free->fl)
		{
			free(to_free->fl->file_name);
			free(to_free->fl);
		}
		else if (to_free->is_operator && to_free->operator)
			free(to_free->operator);
		else if (to_free->is_here_doc)
		{
			if (to_free->here_doc)
				free(to_free->here_doc);
		}
		to_free = to_free->next;
		free(temp);
	}
}

void	free_all(t_all **all)
{
	t_all	*current;

	current = *all;
	free_s_env(&current->env_lst);
	if (current->copy_envp)
		free_split(current->copy_envp);
	if (current->readline_line != NULL)
		free(current->readline_line);
	free(*all);
}

void	free_full_t_pars(t_pars **pars)
{
	t_pars	*to_free;
	t_pars	*temp;

	to_free = *pars;
	while (to_free)
	{
		temp = to_free;
		if (to_free->is_command && to_free->cmd)
			free_cmd_node(to_free);
		else if (to_free->is_file)
		{
			free(to_free->fl->file_name);
			free(to_free->fl);
		}
		if (to_free->is_operator && to_free->operator)
			free(to_free->operator);
		if (to_free->is_here_doc)
			free(to_free->here_doc);
		to_free = to_free->next;
		free(temp);
	}
}
