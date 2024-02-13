/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/13 16:17:51 by glambrig         ###   ########.fr       */
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
		free(temp->original_envp);
		free(temp);
	}	
}

/* Inserts a new node with the given environment variable into the list */
t_env_list *insert_node_env(char **env_var)
{
	t_env_list *new_node;
	
	new_node = malloc(sizeof(t_env_list));
	if (new_node == NULL)
	{
		perror("Failed to allocate memory for new node");
		exit(EXIT_FAILURE);
	}
	new_node->key = env_var[0];
	new_node->value = env_var[1];
	new_node->original_envp = ft_strjoin(env_var[0], env_var[1]);
	new_node->next = NULL;
	return new_node;
}

/*Adds 'line' to the list of environment variables*/
void	ft_export(t_env_list **envp, char *line)
{
	t_env_list 	*temp;
	char 		**s;
	int 		i;

	temp = *envp;
	s = ft_split(line, ' ');	//otherwise we literally get "export FLO=BG" as the env var
	if (*envp == NULL)
		*envp = insert_node_env(s);
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = insert_node_env(s);
	}
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

