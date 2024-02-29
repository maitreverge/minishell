/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:20 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 09:45:32 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	correct_export_format(char *str)
{
	bool	equal_sign;
	int		i;

	i = 0;
	equal_sign = false;
	if (str[0] == '=')
		return (false);
	while (str[i])
	{
		if (is_whitespace(str[i]))
			return (false);
		if (str[i] == '=')
		{
			if (str[i + 1] == '=')
				return (false);
			equal_sign = true;
		}
		i++;
	}
	if (equal_sign)
		return (true);
	return (false);
}

static t_env_list	*env_key_exist(t_env_list **envp, char *key)
{
	t_env_list	*current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			break ;
		current = current->next;
	}
	return (current);
}

static bool	right_format(char *s_final_trim, t_pars **pars)
{
	if (!correct_export_format(s_final_trim))
	{
		lstfirst(*pars)->last_exit_status = 1;
		ft_putendl_fd("Wrong export format\n", 2);
		return (false);
	}
	return (true);
}

static void	ft_export_2(t_env_list **e, char **s, t_env_list *cur, char *trim)
{
	if (env_key_exist(e, s[0]))
	{
		cur = env_key_exist(e, s[0]);
		free(cur->value);
		cur->value = ft_strdup(s[1]);
	}
	else
		env_lstadd_back(e, env_lstnew(s[0], s[1], trim));
}

void	ft_export(t_env_list **envp, char **name_args, t_all *all, t_pars **pars)
{
	t_env_list	*current_env;
	char		**split_t;

	current_env = *envp;
	if (!name_args[1])
	{
		ft_env(name_args, all, pars);
		return ;
	}
	if (ft_isdigit(name_args[1][0]))
	{
		ft_putendl_fd("export : environment variable can't start with a number", 2);
		lstfirst(*pars)->last_exit_status = 1;
		return;
	}
	if (!right_format(name_args[1], pars))
		return ;
	split_t = ft_2_split(name_args[1], '=');
	ft_export_2(envp, split_t, current_env, name_args[1]);
	lstfirst(*pars)->last_exit_status = 0;
	free_split(split_t);
}
