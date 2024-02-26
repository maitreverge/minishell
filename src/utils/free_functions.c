/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:40:52 by flverge           #+#    #+#             */
/*   Updated: 2024/02/26 10:55:30 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **to_free)
{
	char	**current;
	int		i;
	int 	len;

	if (!to_free)
		return;

	i = 0;
	len = 0;
	current = to_free;
	while (current[len] != NULL)
		len++;
	current = to_free;
	while (i < len)
	{
		if (current[i])
		{
			free(current[i]);
			current[i] = NULL;  // set the pointer to NULL after freeing it
		}
		i++;
	}
	free(to_free);
}

void	free_s_env(t_env_list **env)
{
	t_env_list	*current;
	t_env_list	*temp;

	current = *env;
	while (current)
	{
		temp = current;
		free(current->original_envp);
		free(current->key);
		free(current->value);
		current = current->next;
		free(temp);
	}
	// free(*env); // free the node itself
}

void	free_s_utils(t_utils **utils)
{
	t_utils	*current;

	current = *utils;
	free_split(current->result);
	free(current);
}

void	free_firstnode_pars(t_pars **pars)
{
	free(*pars);
}

void	free_t_alloc(t_alloc *alloc)
{
	// t_alloc *to_free;
	
	// to_free = *alloc;
	free_split(alloc->splitted_prompt);
	free_split(alloc->paths);
	// free_split(alloc->cleaned_prompt); // already free in t_utils function
	free(alloc);
}

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
			free(to_free->cmd->command_name);
			if (to_free->cmd->command_path)
				free(to_free->cmd->command_path);
			free_split(to_free->cmd->name_options_args);
			free(to_free->cmd); // free the sub_node
		}
		else if (to_free->isFile)
		{
			free(to_free->fl->file_name);
			free(to_free->fl);
		}
		if (to_free->isOperator && to_free->operator)
			free(to_free->operator);
		
		if (to_free->isHereDoc) // only need to free the node
			free(to_free->here_doc); // newly allocated node
		to_free = to_free->next;
		free(temp);
	}
}

void	free_all(t_all **all)
{
	t_all *current;

	current = *all;

	free_s_env(&current->env_lst); // free the struct content + the node itself

	if (current->copy_envp)
		free_split(current->copy_envp);

	if (current->readline_line != NULL)
		free(current->readline_line);
	
	free(*all); // free the t_all node
	
}

void	free_full_t_pars(t_pars **pars)
{
	t_pars	*to_free;
	t_pars *temp; // for freeing the node itself

	to_free = *pars;

	while (to_free)
	{
		temp = to_free;
		if (to_free->isCommand && to_free->cmd)
		{
			free(to_free->cmd->command_name);
			if (to_free->cmd->command_path)
				free(to_free->cmd->command_path);
			free_split(to_free->cmd->name_options_args);
			free(to_free->cmd); // free the sub_node
		}
		else if (to_free->isFile)
		{
			free(to_free->fl->file_name);
			free(to_free->fl);
		}
		if (to_free->isOperator && to_free->operator)
			free(to_free->operator);
		
		if (to_free->isHereDoc) // only need to free the node
			free(to_free->here_doc); // newly allocated node
		to_free = to_free->next;
		free(temp);
	}
}

