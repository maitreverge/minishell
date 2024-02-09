/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/02/09 14:44:19 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_redir_in(t_pars **pars, char **splited, char **cleaned)
{
	int i;

	i = 0;
	while (splited[i])
	{
		if (!ft_strncmp(cleaned[i], RED_IN, 2) && !ft_strncmp(cleaned[i], splited[i], 2))
		{
			(*pars)->isRedirIn = true;
			break ;	
		} 
		else if (!ft_strncmp(cleaned[i], RED_IN_DELIM, 3) && !ft_strncmp(cleaned[i], splited[i], 3))
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

bool	is_token_command(char *splited, char *cleaned, char **paths)
{
	int j; // paths index

	j = 0;
	char *supposed_command;
	
	supposed_command = NULL;
	// ! IMPORTANT : builtin needs to be tested first
	// ! because access will trow a false positive on builtin commands anyway
	// testing builtin presence first, for avoiding access 
	if (testing_builtin(cleaned))
	{
		printf("Command is a builtin\n");
		return true;
	}
		
	// testing paths for regular commands with access
	while (paths[j])
	{
		supposed_command = ft_strjoin(paths[j], cleaned);
		if (!access(supposed_command, F_OK))
		{
			free(supposed_command);
			return true;
		}
		j++;
		free(supposed_command);
	}
	return false;
}

void	new_node_command(t_pars **pars, t_alloc **utils, int *i)
{
	// ! Allocate a new node;
	t_pars	*new_node;
	t_command *new_node_command;
	t_alloc *u;

	u = *utils;
	// char **comb_execve;
	int start;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	new_node_command = malloc(sizeof(t_command));
	if (!new_node_command)
		return ;
	
	// -------------------global init node--------------------

	// ! STEP 1 : init bools switches
	new_node->isCommand = true;
	new_node->isFile = false;
	new_node->isOperator = false;

	// ! STEP 2 :connecting the t_command node
	new_node->cmd = new_node_command;
	
	// ! STEP 3 : NULL init other substructures nodes
	new_node->fl = NULL;
	new_node->operator = NULL;

	// ! STEP 4 : init prev and next both to NULL
	new_node->prev = NULL;
	new_node->next = NULL;
	// -------------------global init node--------------------
	
	
	// -------------------init substructure--------------------
	
	// ! STEP 1 :  init name of command
	new_node->cmd->command_name = u->cleaned_prompt[*i];
	
	// ! STEP 2 : is command builtin ??
	if (testing_builtin(u->cleaned_prompt[*i]))
	{
		new_node->cmd->isBuiltin = true;
		new_node->cmd->command_path = u->cleaned_prompt[*i]; // ! keeping coherence betweem builtins and not builtins
	}
	else
		new_node->cmd->isBuiltin = false;
	// -------------------init substructure--------------------
	
	/*
	builtin
	char *argv[] = {"echo", "-l", NULL};

	cmd normalle
	char *argv[] = {"/bin/ls", "-l", NULL};

	
	if (execve("/bin/ls", argv, envp) == -1) {
	*/
	
	// ! calculatting the lenght of split, then allocating the buffer within the cleaned split
	start = *i;
	while (u->cleaned_prompt[*i])
	{
		if (is_token_operator(u->splitted_prompt[*i], u->cleaned_prompt[*i]))
			break ;
		(*i)++;
	}
	
	// malloc de cette horreur char *argv[] = {"/bin/ls", "-l", NULL};
	new_node->cmd->name_options_args = (char **)ft_calloc(((*i) - start + 1), sizeof(char *));
	if (!new_node->cmd->name_options_args)
		exit (-1); // ! failed malloc
	
	// ! assigning commands
	
	
	
	
	// ! last step : lstaddback
	
}

bool	is_token_file(char *splited, char *cleaned)
{
	
}

void	new_node_file(t_pars **pars, char *splited, char *cleaned)
{
	
}

bool	is_token_operator(char *splited, char *cleaned)
{
	// ! checks if there is a operator intead of an operator within quotes
	if (ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, RED_IN))
			return (true);
		else if (!ft_strcmp(cleaned, RED_IN_DELIM))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT_APP))
			return (true);
		else if (!ft_strcmp(cleaned, PIPE))
			return (true);
	}
	return (false);
}

void	new_node_operator(t_pars **pars, char *splited, char *cleaned)
{
	
}

void	pars_alloc(t_pars **pars, t_alloc **u_alloc)
{
	t_alloc *cur;

	cur = *u_alloc;
	int i; // index of both split and cleaned

	i = 0;
	
	// ! step 1 : detect redir in operator, matching splited and cleaned
	search_redir_in(pars, cur->splitted_prompt, cur->cleaned_prompt);


	// ! allocate the struct whatsoever
	while (cleaned[i]) // iterate over all tokens	
	{
		if (is_token_command(cur->splitted_prompt[i], cur->cleaned_prompt[i], cur->paths))
			new_node_command(pars, cur, &i); // prompts + paths
		else if (is_token_file(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
			new_node_file(pars, cur->splitted_prompt[i], cur->cleaned_prompt[i]);
		else if (is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
			new_node_operator(pars, cur->splitted_prompt[i], cur->cleaned_prompt[i]);
		// ! maybe another edge case ???
		i++;
	}
	
	// ! print the whole struct
}
