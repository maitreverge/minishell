/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:28:16 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 13:53:29 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void free_t_cmd(t_command *cmd) // ! function not referenced into minishell.h
// {
// 	free(cmd->command_name);
// 	free(cmd->command_path);
// 	free_arr((void **)cmd->name_options_args, size_of_ptr_ptr((void **)cmd->name_options_args));
// }

// void free_t_file(t_file *file) // ! function not referenced into minishell.h
// {
// 	free(file->file_name);
// }

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
		if (to_free->isCommand && to_free->cmd)
		{
			// free(to_free->cmd->command_name);
			free(to_free->cmd->command_path);
			free_split(to_free->cmd->name_options_args);
			free(to_free->cmd); // free the sub_node
		}
		else if (to_free->isFile)
		{
			// free(to_free->fl->file_name);
			free(to_free->fl);
		}
		if (to_free->isOperator && to_free->operator)
			free(to_free->operator);
		
		// if (to_free->isHereDoc) // only need to free the node
		to_free = to_free->next;
		free(temp);
	}
}
