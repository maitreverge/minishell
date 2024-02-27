/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/27 12:07:29 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	find_middle_node(t_env_list **envp, char *line)
{
	t_env_list *current;
	t_env_list *previous_node;
	t_env_list *next_node;
	t_env_list *temp;
	
	temp = *envp;
	
	while (temp)
	{
		if (!ft_strcmp(temp->key, line))
			break;
		previous_node = temp;
		temp = temp->next;
	}
	if (!temp) // if variable not found, exit function to avoid segfault
		return;
	current = previous_node->next;
	next_node = current->next;
	previous_node->next = next_node;
	free(current);
}

/*Removes 'line' from the list of environment variables*/
void	ft_unset(t_env_list **envp, char *line, t_pars **parsing)
{
	t_env_list *current;
	t_env_list *first_node;
	t_env_list *last_node;
	
	current = *envp;
	first_node = *envp;
	last_node = env_lstlast(*envp);

	// ! CASE 1 : target is on the first node
	if (!ft_strcmp(first_node->key, line))
	{
		(*envp) = (*envp)->next; // move the head of the struct itself to the next node
		free(first_node);
	}
	// ! CASE 2 : target is on the last node
	else if (!ft_strcmp(last_node->key, line))
	{
		while (ft_strcmp(current->next->key, line))
			current = current->next;
		current->next = NULL;
		free(last_node);
	}
	else // ! CASE 3 : the target node is in the middle
		find_middle_node(envp, line);
	lstfirst(*parsing)->last_exit_status = 0; // unset last_exit_status ==> 0 in every case !
}

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
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*Adds 'line' to the list of environment variables*/
void	ft_export(t_env_list **envp, char *line, t_all *all, t_pars **pars)
{
	t_env_list *current_env;
	char 		**new_envp;
	char		**split_tokens;
	char *s_trimmed;

	current_env = *envp;

	s_trimmed = ft_strtrim(line, "export"); // trim export from the argument, because idk what's supposed to land on the function
	if (!s_trimmed)
		ft_env(all); // fuck this shit seriously
	else if (!correct_export_format(s_trimmed)) // ! CHECK IF EXPORT FOLLOW THE ___= format (at least)
	{
		lstfirst(*pars)->last_exit_status = 1;
		printf("Wrong export format\n");
		return ;
	}
	split_tokens = ft_2_split(s_trimmed, '='); // allows me to extract key and value
	
	if (env_key_exist(envp, split_tokens[0]))
	{
		// * THE KEY EXISTS => LOAD THE NEW VALUE
		current_env = env_key_exist(envp, split_tokens[0]);
		free(current_env->value); // free the current value
		current_env->value = ft_strdup(split_tokens[1]); // load the new value
	}
	else
	{
	// * THE KEY DOESN'T EXISTS => ENV_LSTADD_BACK
		env_lstadd_back(envp, env_lstnew(split_tokens[0], split_tokens[1], s_trimmed));
	}
	lstfirst(*pars)->last_exit_status = 0;
	free_split(split_tokens);
	free(s_trimmed);
}

// export edge cases :
// need to check

