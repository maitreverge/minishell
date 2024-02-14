/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:28:16 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 09:29:46 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_t_cmd(t_command *cmd)
{
	free(cmd->command_name);
	free(cmd->command_path);
	free_arr((void **)cmd->name_options_args, size_of_ptr_ptr((void **)cmd->name_options_args));
}

void free_t_file(t_file *file)
{
	free(file->file_name);
}