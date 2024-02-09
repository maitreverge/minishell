/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:29:53 by flverge           #+#    #+#             */
/*   Updated: 2024/02/09 09:55:58 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **extract_paths(t_env_list **s_env)
{
	t_env_list	*current;
	char		**result;
	char		*paths_value;

	current = *s_env;

	while (current)
	{
		if (!ft_strncmp(current->key, "PATH", 5))
		{
			paths_value = current->value;
			break ;
		}
		current = current->next;
	}
	result = path_split(paths_value, ':');
	return (result);
}
