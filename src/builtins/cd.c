/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:41 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 13:43:36 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_home_path(t_env_list **envp)
{
	t_env_list	*current;
	char		*result;

	current = *envp;
	result = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, "HOME"))
			result = current->value;
		current = current->next;
	}
	return (result);
}

static char	*get_current_path(t_env_list **envp)
{
	t_env_list	*current;
	char		*result;

	current = *envp;
	result = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, "PWD"))
			result = current->value;
		current = current->next;
	}
	return (result);
}

static void	update_pwd(t_env_list **envp, char *new_value, char *target)
{
	t_env_list	*current;
	char		*before_equal;
	char		*join_new_full_envp;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->key, target))
		{
			free(current->original_envp);
			before_equal = ft_strjoin(target, "=");
			join_new_full_envp = ft_strjoin(before_equal, new_value);
			current->original_envp = ft_strdup(join_new_full_envp);
			free(current->value);
			current->value = ft_strdup(new_value);
			free(join_new_full_envp);
			free(before_equal);
			return ;
		}
		current = current->next;
	}
}

static void	regular_cd(t_env_list **envp, char **name_args, char *current_path)
{
	char	*regular_path;
	char	*temp;

	regular_path = name_args[1];
	chdir(regular_path);
	update_pwd(envp, current_path, "OLDPWD");
	temp = getcwd(NULL, 0);
	update_pwd(envp, temp, "PWD");
	free(temp);
}

void	ft_cd(t_pars **pars, t_env_list **envp)
{
	char	**name_args;
	char	*homepath;
	char	*current_path;

	name_args = (*pars)->cmd->name_options_args;
	homepath = ft_strdup(get_home_path(envp));
	current_path = ft_strdup(get_current_path(envp));
	if (!name_args[1] || !ft_strcmp(name_args[1], "~"))
	{
		chdir(homepath);
		update_pwd(envp, current_path, "OLDPWD");
		update_pwd(envp, homepath, "PWD");
	}
	else if (name_args[2])
		ft_putendl_fd("cd : too may arguments\n", 2);
	else
		regular_cd(envp, name_args, current_path);
	free(homepath);
	free(current_path);
}
