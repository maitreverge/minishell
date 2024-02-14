/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:28:16 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 13:42:29 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_t_cmd(t_command *cmd) // ! function not referenced into minishell.h
{
	free(cmd->command_name);
	free(cmd->command_path);
	free_arr((void **)cmd->name_options_args, size_of_ptr_ptr((void **)cmd->name_options_args));
}

void free_t_file(t_file *file) // ! function not referenced into minishell.h
{
	free(file->file_name);
}

void	free_t_pars(t_pars **lst)
{
	t_pars	*temp;

	while ((*lst)->next)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd != NULL)
			free_t_cmd((*lst)->cmd);
		if ((*lst)->fl != NULL)
			free_t_file((*lst)->fl);
		free((*lst));
		(*lst) = temp;
	}
}
