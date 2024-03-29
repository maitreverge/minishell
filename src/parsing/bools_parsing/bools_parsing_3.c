/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:58:47 by flverge           #+#    #+#             */
/*   Updated: 2024/03/04 16:27:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_last_node_pipe(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->operator)
	{
		if (last->operator->pipe)
			return (true);
	}
	return (false);
}

void	search_redir_in(t_pars **pars, char **splited, char **cleaned)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if (!ft_strcmp(cleaned[i], RED_IN)
			&& !ft_strcmp(cleaned[i], splited[i]))
		{
			(*pars)->is_redir_in = true;
			break ;
		}
		else if (!ft_strcmp(cleaned[i], RED_IN_DELIM)
			&& !ft_strcmp(cleaned[i], splited[i]))
		{
			(*pars)->is_redir_in = true;
			break ;
		}
		i++;
	}
}

bool	testing_builtin(char *cleaned)
{
	if (!ft_strcmp(cleaned, "echo"))
		return (true);
	else if (!ft_strcmp(cleaned, "cd"))
		return (true);
	else if (!ft_strcmp(cleaned, "pwd"))
		return (true);
	else if (!ft_strcmp(cleaned, "export"))
		return (true);
	else if (!ft_strcmp(cleaned, "unset"))
		return (true);
	else if (!ft_strcmp(cleaned, "env"))
		return (true);
	else if (!ft_strcmp(cleaned, "exit"))
		return (true);
	return (false);
}

char	*join_path_cmd(char *cleaned, char **paths)
{
	char	*real_path;
	int		j;

	j = 0;
	real_path = NULL;
	if (!access(cleaned, F_OK))
		return (ft_strdup(cleaned));
	if (!paths)
		return (NULL);
	while (paths[j])
	{
		real_path = ft_strjoin(paths[j], cleaned);
		if (!access(real_path, F_OK))
			return (real_path);
		j++;
		free(real_path);
	}
	real_path = NULL;
	return (real_path);
}

char	**extract_paths(t_env_list **s_env)
{
	t_env_list	*current;
	char		**result;
	char		*paths_value;

	paths_value = NULL;
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
	if (!paths_value)
		return (NULL);
	result = path_split(paths_value, ':');
	return (result);
}
