/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/25 22:07:21 by flverge          ###   ########.fr       */
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
	t_env_list *temp;
	t_env_list *prev;

	temp = *envp;
	prev = temp;////
	if (line == NULL)
	{
		free_s_env(envp);
		perror("ft_unset error: line == NULL");
		exit(EXIT_FAILURE);
	}
	while (temp->next != NULL && ft_strncmp(temp->original_envp, line, ft_strlen(line)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp != NULL)
	{
		prev->next = temp->next;
		// free(temp->original_envp);
		// free(temp->key);
		// free(temp->value);
		// free(temp);
	}	
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

