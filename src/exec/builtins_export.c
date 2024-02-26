/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/26 14:12:16 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	print_list(t_env_list *envp)
// {
// 	t_env_list * temp = envp;

// 	while (envp != NULL)
// 	{
// 		printf("%s\n", envp->original_envp);
// 		envp = envp->next;
// 	}
// 	envp = temp;
// }

/*Removes 'line' from the list of environment variables*/
void	ft_unset(t_env_list **envp, char *line)
{
	t_env_list *current;
	t_env_list *first_node;
	t_env_list *last_node;
	t_env_list *previous_node;
	t_env_list *next_node;
	
	current = *envp;
	first_node = *envp;
	last_node = env_lstlast(*envp);

	while (current)
	{
		// ! EDGE CASE 1 : target is on the first node
		if (!ft_strcmp(first_node->key, line))
		{
			(*envp) = (*envp)->next; // move the head to the next
			free(first_node);
		}
		// ! EDGE CASE 2 : target is on the last node
		else if (!ft_strcmp(last_node->key, line))
		{
			
		}
		current = current->next;
	}
	
	// char *line = KEY
		
}

/*Adds 'line' to the list of environment variables*/
void	ft_export(t_env_list **envp, char *line)
{
	char 		**new_envp;
	char		**split_value;
	char		*key;
	char		*value;

	new_envp = ft_split(line, ' ');
	split_value = ft_2_split(new_envp[1], '='); // allows me to extract key and value
	key = split_value[0];
	value = split_value[1];
	env_lstadd_back(envp, env_lstnew(key, value, new_envp[1]));
	
	free_split(new_envp);
	free_split(split_value);
}

