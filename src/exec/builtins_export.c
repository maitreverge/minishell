/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/27 10:54:08 by flverge          ###   ########.fr       */
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
	while (str[i])
	{
		if (is_whitespace(str[i]))
			return (false);
		if (str[i] == '=')
		{
			if (equal_sign)
				return (false);
			equal_sign = true;
		}
		i++;
	}
	return (true);
}

/*Adds 'line' to the list of environment variables*/
void	ft_export(t_env_list **envp, char *line, t_all *all)
{
	char 		**new_envp;
	char		**split_value;
	char		*key;
	char		*value;
	char *s;

	s = ft_strtrim(line, "export");
	if (!s)
		ft_env(all); // fuck this shit seriously
	// ! CHECK IF EXPORT FOLLOW THE ___=___ 
	else if (!correct_export_format(s))
	
		

	// ! CHECK IS THE VALUE ALREADY EXISTS
	// * THE KEY EXISTS = MODIFY THE KEY
	// * THE KEY DOESN'T EXISTS => ENV_LSTADD_BACK
	
	new_envp = ft_split(line, ' ');
	split_value = ft_2_split(new_envp[1], '='); // allows me to extract key and value
	key = split_value[0];
	value = split_value[1];
	env_lstadd_back(envp, env_lstnew(key, value, new_envp[1]));
	
	free_split(new_envp);
	free_split(split_value);
	free(s); // free the trimed string
}

// export edge cases :
// need to check

