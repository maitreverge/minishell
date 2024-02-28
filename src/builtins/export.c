/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:20 by flverge           #+#    #+#             */
/*   Updated: 2024/02/28 12:00:42 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool correct_export_format(char *str)
{
	int	i;
	bool equal_sign;

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

static t_env_list *env_key_exist(t_env_list **envp, char *key)
{
	t_env_list *current;

	current = *envp;

	while (current)
	{
		if (!ft_strcmp(current->key, key))
			break ; // return the current pointer to the targeted node
		current = current->next;
	}
	return (current); // can return NULL if node has not been found
}

/*Adds 'line' to the list of environment variables*/
void	ft_export(t_env_list **envp, char *line, t_all *all, t_pars **pars)
{
	t_env_list *current_env;
	char		**split_tokens;
	char *s_trimmed_export;
	char *s_final_trim;
	char *trim_line;

	current_env = *envp;
	trim_line = ft_strtrim(line, " ");
	if (!ft_strcmp(trim_line, "export"))
	{
		ft_env((*pars)->cmd->name_options_args, all, pars);
		return ;
	}

	s_trimmed_export = ft_strtrim(line, "export"); // trim export from the argument, because idk what's supposed to land on the function
	s_final_trim = ft_strtrim(s_trimmed_export, " "); // trim whitespaces
	
	if (!correct_export_format(s_final_trim)) // ! CHECK IF EXPORT FOLLOW THE ___= format (at least)
	{
		lstfirst(*pars)->last_exit_status = 1;
		printf("Wrong export format\n");
		return ;
	}
	split_tokens = ft_2_split(s_final_trim, '='); // allows me to extract key and value
	
	if (env_key_exist(envp, split_tokens[0]))
	{
		// * THE KEY EXISTS => LOAD THE NEW VALUE
		current_env = env_key_exist(envp, split_tokens[0]);
		free(current_env->value); // free the current value
		current_env->value = ft_strdup(split_tokens[1]); // load the new value in the heap
	}
	else
	{
	// * THE KEY DOESN'T EXISTS => NEW_NODE
		env_lstadd_back(envp, env_lstnew(split_tokens[0], split_tokens[1], s_final_trim));
	}
	lstfirst(*pars)->last_exit_status = 0;
	free_split(split_tokens);
	free(s_trimmed_export);
	free(s_final_trim);
	free(trim_line);
}