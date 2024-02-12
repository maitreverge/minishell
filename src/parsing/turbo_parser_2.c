/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/02/12 18:22:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_redir_in(t_pars **pars, char **splited, char **cleaned)
{
	int i;

	i = 0;
	while (splited[i])
	{
		if (!ft_strcmp(cleaned[i], RED_IN) && !ft_strcmp(cleaned[i], splited[i]))
		{
			(*pars)->isRedirIn = true;
			break ;	
		} 
		else if (!ft_strcmp(cleaned[i], RED_IN_DELIM) && !ft_strcmp(cleaned[i], splited[i]))
		{
			(*pars)->isRedirIn = true;
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

char *join_path_command(char *splited, char *cleaned, char **paths)
{
	int j; // paths index

	j = 0;
	char *real_path;
	
	real_path = NULL;

	// ! edge case : handle absolute and relative paths
	
	while (paths[j])
	{
		real_path = ft_strjoin(paths[j], cleaned);
		if (!access(real_path, F_OK))
			return (real_path);
		j++;
		free(real_path);
	}

	real_path = cleaned;
	return (real_path);
}


void	pars_alloc(t_pars **pars, t_alloc **u_alloc)
{
	t_pars *last_p_node;
	t_alloc *cur;

	cur = *u_alloc;
	// last_p_node = lstlast(*pars);
	int i; // index of both split and cleaned

	i = 0;
	
	// ! step 1 : detect redir in operator, matching splited and cleaned
	search_redir_in(pars, cur->splitted_prompt, cur->cleaned_prompt);


	// iterate over all tokens	
	while (cur->cleaned_prompt[i])
	{
		// ! Special condition for very first token
		last_p_node = lstlast(*pars);
		if (!last_p_node->prev) // first node == cmd
		{
			if (!is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_command(pars, u_alloc, &i);
			else
			{
				(*pars)->MasterKill = true;
				printf("First Token is a Operator\n");
				break ;
			}
		}
		
		// ! CASE 1 = Last Node is a Command ==> operator
		else if ((is_last_node_cmd(pars)))
		{
			if (is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("Token following a command isn't a operator\n");
				break ;
			}
		}

		// ! CASE 2 = Last Node is a File
		
		else if (is_last_node_file)
		{
			if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i]) || is_token_redit_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("Token following a file isn't a PIPE or RED_OUT operator\n");
				break ;
			}
		}
		
		// ! CASE 3 = Last Node is a Here_Doc
		else if (is_last_node_here_doc(pars))
		{
			if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i]) || is_token_redit_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("Token following a HERE_DOC isn't a PIPE or RED_OUT operator\n");
				break ;
			}
		}
		// ! CASE 4 = Last Node is a Operator
		else if (is_last_node_operator(pars))
		{
			// Whole block checks for double consecutive 
			if (is_last_node_pipe(pars) && !is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_command(pars, u_alloc, &i);
			else if (is_last_node_redir(pars) && !is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_file(pars, cur->cleaned_prompt[i]);
			else if (is_last_node_r_in_delim(pars) && !is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_here_doc(pars, cur->cleaned_prompt[i]);
			else // last case : consecutive two operator_tokens
			{
				(*pars)->MasterKill = true;
				printf("TWO CONSECUTIVE OPERATORS\n\n");
				break ;
			}
		}
		
		if (cur->cleaned_prompt[i])
			i++;
		
		// ! maybe another edge case ???
	}
	
	// ! print the whole struct
	print_final_struct(pars);
}
