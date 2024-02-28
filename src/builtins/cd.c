/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:41 by flverge           #+#    #+#             */
/*   Updated: 2024/02/28 18:44:55 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *get_home_path(t_env_list **envp)
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

static char *get_current_path(t_env_list **envp)
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

// static char *get_old_path(t_env_list **envp)
// {
// 	t_env_list	*current;
// 	char		*result;

// 	current = *envp;
// 	result = NULL;
// 	while (current)
// 	{
// 		if (!ft_strcmp(current->key, "OLDPWD"))
// 			result = current->value;
// 		current = current->next;
// 	}
// 	return (result);
// }

void	update_pwd(t_env_list **envp, char *to_change, char *target)
{
	t_env_list *current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->key, target))
		{
			free(current->value);
			current->value = ft_strdup(to_change);
			return ;
		}
		current = current->next;
	}
}

// void	multiple_free_paths(char *s1, char *s2)
// {
// 	free(s1);
// 	free(s2);
// }

void	ft_cd(t_pars **pars, t_env_list **envp)
{
	char	**name_args;
	char	*homepath;
	char	*current_path;
	// char	*old_path;
	char 	*regular_path;

	name_args = (*pars)->cmd->name_options_args;

	homepath = ft_strdup(get_home_path(envp));
	current_path = ft_strdup(get_current_path(envp));
	// old_path = ft_strdup(get_old_path(&envp));

	
	if (!name_args[1]) // prompt = 'cd'
	{
		chdir(homepath);
		update_pwd(envp, current_path, "OLDPWD"); // update OLDPWD
		update_pwd(envp, homepath, "PWD"); // update PWD to HOMEPATH
		// multiple_free_paths(homepath, current_path);
		// return ;
	}
	else if (name_args[2]) // prompt = 'cd .. earfdgkjkaedtf'
	{
		// free(homepath);
		// free(current_path);
		ft_putendl_fd("cd : too may arguments\n", 2);
		// multiple_free_paths(homepath, free)
		// return;
	}
	else
	{
		regular_path = name_args[1];
		chdir(regular_path);
		update_pwd(envp, current_path, "OLDPWD"); // update OLDPWD
		free(current_path);
		current_path = ft_strdup(get_current_path(envp)); // refresh current path
		update_pwd(envp, current_path, "PWD"); // update PWD
	}
	free(homepath);
	free(current_path);
	// // tokens = NULL;
	// // if (ft_strchr(s, ' ') != NULL)
	// // 	tokens = ft_split(s, ' ');
	// /*cd with no parameters changes to home directory*/
	// if ((tokens != NULL && tokens[1] == NULL) || tokens == NULL)
	// {
	// 	homepath = ft_strjoin("/home/", getenv("USER"));
	// 	free(homepath);
	// 	free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
	// 	ft_pwd(&envp, false);
	// 	return (0);
	// }
	// else if (tokens != NULL)
	// {
	// 	chdir(tokens[1]);
	// 	ft_pwd(&envp, false);
	// }
	// free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));


	// free(old_path);
}
