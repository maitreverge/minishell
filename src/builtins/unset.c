/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:58:42 by flverge           #+#    #+#             */
/*   Updated: 2024/03/03 14:44:22 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	del_first_node(t_env_list **envp, t_env_list *first_node)
{
	(*envp) = (*envp)->next;
	free(first_node->key);
	free(first_node->value);
	free(first_node->original_envp);
	free(first_node);
}

static void	del_middle_node(t_env_list **envp, char *line)
{
	t_env_list	*current;
	t_env_list	*previous_node;
	t_env_list	*next_node;
	t_env_list	*temp;

	temp = *envp;
	while (temp)
	{
		if (!ft_strcmp(temp->key, line))
			break ;
		previous_node = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	current = previous_node->next;
	next_node = current->next;
	previous_node->next = next_node;
	free(current->key);
	free(current->value);
	free(current->original_envp);
	free(current);
}

static void	del_last_node(t_env_list *cur, char *e_key, t_env_list *last_node)
{
	while (ft_strcmp(cur->next->key, e_key))
		cur = cur->next;
	cur->next = NULL;
	free(last_node->key);
	free(last_node->original_envp);
	free(last_node->value);
	free(last_node);
}

void	ft_unset(t_env_list **envp, char **name_args, t_pars **parsing)
{
	t_env_list	*current;
	t_env_list	*first_node;
	t_env_list	*last_node;
	char		*extracted_key;

	current = *envp;
	first_node = *envp;
	last_node = env_lstlast(*envp);
	if (!name_args[1])
	{
		ft_putendl_fd("unset : not enough arguments\n", 2);
		last_exit_status = 1;
	}
	extracted_key = ft_strdup((*parsing)->cmd->name_options_args[1]);
	if (!ft_strcmp(first_node->key, extracted_key))
		del_first_node(envp, first_node);
	else if (!ft_strcmp(last_node->key, extracted_key))
		del_last_node(current, extracted_key, last_node);
	else
		del_middle_node(envp, extracted_key);
	last_exit_status = 0;
	free(extracted_key);
}
