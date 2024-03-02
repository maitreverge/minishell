/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2common_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:46:42 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/02 11:38:46 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Returns:
	1 for pipe
	2 for redir in
	3 for heredoc
	4 for redir out or redir out append
	0 for no operators
*/
int	check_next_operator(t_pars *lst)
{
	t_pars	*temp;

	temp = lst;
	while (lst)
	{
		if (lst->is_operator == true)
		{
			if (lst->operator->pipe == true)
				return (1);
			if (lst->operator->redir_in == true)
				return (2);
			if (lst->operator->redir_in_delim == true)
				return (3);
			if (lst->operator->redir_out == true
				|| lst->operator->redir_out_app == true)
				return (4);
		}
		lst = lst->next;
	}
	lst = temp;
	return (0);
}

t_all	*init_t_all_struct(char **envp)
{
	t_all		*new_all;

	new_all = malloc(sizeof(t_all));
	if (!new_all)
		return (NULL);
	new_all->env_lst = NULL;
	new_all->readline_line = NULL;
	copy_env_into_list(&new_all->env_lst, envp);
	new_all->copy_envp = NULL;
	return (new_all);
}

void	reset_t_pars(t_pars **pars)
{
	(*pars)->masterkill = false;
	(*pars)->is_redir_in = false;
	(*pars)->error_message = 0;
}

char	**convert_env_list_to_array(t_env_list **list)
{
	t_env_list	*current;
	char		**result;
	int			size;
	int			j;

	current = *list;
	size = 0;
	j = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	current = *list;
	result = ft_calloc(size + 1, sizeof(char *));
	while (current)
	{
		result[j] = ft_strdup(current->original_envp);
		current = current->next;
		j++;
	}
	return (result);
}

void	refresh_envp(t_all **all)
{
	t_all	*current;

	current = *all;
	free_split(current->copy_envp);
	current->copy_envp = convert_env_list_to_array(&current->env_lst);
}
