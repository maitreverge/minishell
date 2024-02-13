/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/12 22:14:02 by glambrig         ###   ########.fr       */
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

/*Adds 'line' to the list of environment variables*/
void	ft_export(t_env_list **envp, char *line)
{
	t_env_list 	*temp;
	char 		**s;
	int 		i;

	temp = *envp;
	s = ft_split(line, ' ');	//otherwise we literally get "export FLO=BG" as the env var
	if (*envp == NULL)
		*envp = insert_node_env(s[1]);
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = insert_node_env(s[1]);
	}
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}