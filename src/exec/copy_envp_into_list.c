/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp_into_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:39:27 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/23 14:18:07 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_env_list	*env_lstnew(char *s_key, char *s_value, char *envp)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->original_envp = envp;
	new_node->key = s_key;
	new_node->value = s_value;
	new_node->next = NULL;
	return (new_node);
}

static t_env_list	*env_lstlast(t_env_list *lst)
{
	t_env_list	*current;

	current = lst;
	if (!current)
		return (0);
	if (!current->next)
		return (current);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

static void	env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*tail;

	tail = env_lstlast(*lst);
	tail->next = new;
}

void	copy_env_into_list(t_env_list **env, char **envp)
{
	t_env_list	*current;
	char		*s_key;
	char		*s_value;
	char		**splitted_value;
	int			i;

	current = *env;
	i = 0;
	while (envp[i])
	{
		splitted_value = ft_2_split(envp[i], '=');
		s_key = ft_strdup(splitted_value[0]);
		s_value = ft_strdup(splitted_value[1]);
		if (!current)
		{
			current = env_lstnew(s_key, s_value, envp[i]);
			*env = current;
		}
		else
			env_lstadd_back(&current, env_lstnew(s_key, s_value, envp[i]));
		i++;
		free(splitted_value);
	}
}
