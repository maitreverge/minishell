/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp_into_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:39:27 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/29 15:17:03 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env_list *lst)
{
	t_env_list *temp;

	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp->env_line);
		free(temp);
	}
	//free(lst);
	lst = NULL;
}

t_env_list	*insert_node_env(char *s)
{
	t_env_list *new;

	new = ft_calloc(sizeof(t_env_list), 1);
	new->env_line = ft_strdup(s);
	new->next = NULL;
	return (new);
}

t_env_list	*copy_env_into_list(char **envp)
{
	t_env_list *head;
	t_env_list *current;
	int			i;
	int			len;

	len = 0;
	while (envp[len])
		len++;
	len--;
	current = insert_node_env(envp[len--]);
	head = current;
	i = 0;
	while (i <= len)
	{
		current->next = insert_node_env(envp[i]);
		current = current->next;
		i++;
	}
	current->next = NULL;
	return (head);
}