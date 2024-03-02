/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:40:52 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:16:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ! Function free every node of t_pars except the first one
void	free_t_pars(t_pars **pars)
{
	t_pars *first_node;
	t_pars	*to_free;
	t_pars *temp; // for freeing the node itself

	first_node = *pars;
	to_free = first_node->next;
	first_node->next = NULL;
	while (to_free)
	{
		temp = to_free;
		if (to_free->is_command && to_free->cmd)
		{
			free(to_free->cmd->command_name);
			if (to_free->cmd->command_path)
				free(to_free->cmd->command_path);
			free_split(to_free->cmd->name_options_args);
			free(to_free->cmd); // free the sub_node
		}
		// else if (to_free->is_file && to_free->fl)
		// {
		// 	free(to_free->fl->file_name);
		// 	free(to_free->fl);
		// }
		else if (to_free->is_operator && to_free->operator)
			free(to_free->operator);
		
		else if (to_free->is_here_doc) // only need to free the node
		{
			if (to_free->here_doc)
				free(to_free->here_doc); // newly allocated node
		}
		to_free = to_free->next;
		free(temp);
	}
}

void	free_all(t_all **all)
{
	t_all *current;

	current = *all;

	free_s_env(&current->env_lst);
	if (current->copy_envp)
		free_split(current->copy_envp);
	if (current->readline_line != NULL)
		free(current->readline_line);
	free(*all);
}

// free(pars); // ! recently added
void	free_full_t_pars(t_pars **pars)
{
	t_pars	*to_free;
	t_pars *temp;

	to_free = *pars;

	while (to_free)
	{
		temp = to_free;
		if (to_free->is_command && to_free->cmd)
		{
			free(to_free->cmd->command_name);
			if (to_free->cmd->command_path)
				free(to_free->cmd->command_path);
			free_split(to_free->cmd->name_options_args);
			free(to_free->cmd);
		}
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

