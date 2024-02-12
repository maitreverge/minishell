/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/02/12 14:36:19 by flverge          ###   ########.fr       */
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

bool	is_token_command(char *splited, char *cleaned, char **paths)
{
	int j; // paths index

	j = 0;
	char *supposed_command;
	
	supposed_command = NULL;
	// ! IMPORTANT : builtin needs to be tested first
	// ! because access will trow a false positive on builtin commands anyway
	// testing builtin presence first, for avoiding access 
	// if (cleaned[0] = '\000') // gnnnnnnnnnnnnnnn false positive
	// 	return (false);
	if (testing_builtin(cleaned))
	{
		// printf("Command is a builtin\n");
		return true;
	}
	// testing paths for regular commands with access
	while (paths[j])
	{
		supposed_command = ft_strjoin(paths[j], cleaned);
		// if (!access(supposed_command, F_OK) && paths[j] != supposed_command)
		if (!access(supposed_command, F_OK) && ft_strcmp(paths[j], supposed_command)) // ! add extra condition for excluding empty cleaned buffer
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

	// index for new_node->cmd->name_options_args
	
	int j;
	j = 0;

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
	new_node->isDelim = false;
	new_node->DELIM = NULL;


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
	{
		new_node->cmd->command_path = join_path_command(u->splitted_prompt[*i], u->cleaned_prompt[*i], u->paths);
		new_node->cmd->isBuiltin = false;
	}
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
		if (is_token_operator(u->splitted_prompt[*i + 1], u->cleaned_prompt[*i + 1]))
			break ;
		(*i)++;
	}
	
	int len = (*i) - start + 2;
	printf("Len = %i\n", len);
	// malloc de cette horreur char *argv[] = {"/bin/ls", "-l", NULL};
	new_node->cmd->name_options_args = (char **)ft_calloc(len, sizeof(char *));
	if (!new_node->cmd->name_options_args)
		exit (-1); // ! failed malloc
	
	
	// -------------------assigning char** substructure--------------------
	// ! assigning path = first node
	new_node->cmd->name_options_args[j] = new_node->cmd->command_path;
	// printf("new_node->cmd->name_options_args[%i] = %s\n",j, new_node->cmd->name_options_args[j]);
	j++;
	start++;
	while (j < len - 1)
	{
		// printf("Current cleaned prompt = %s\n", u->cleaned_prompt[start]);
		new_node->cmd->name_options_args[j] = u->cleaned_prompt[start];
		// printf("new_node->cmd->name_options_args[%i] = %s\n",j, new_node->cmd->name_options_args[j]);
		j++;
		start++;
	}
	// -------------------assigning char** substructure--------------------
	
	// ! last step : lstaddback
	lstadd_back(pars, new_node);
}

void	new_node_file(t_pars **pars, char *cleaned)
{
	// ! Allocate a new node;
	t_pars	*new_node;
	t_file *node_file;
	

	// -------------------malloc t_pars node + sub_node--------------------
	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	node_file = malloc(sizeof(t_file));
	if (!node_file)
		return ;
	// -------------------malloc t_pars node + sub_node--------------------




	// -------------------global init node--------------------

	// ! STEP 1 : init bools switches
	new_node->isCommand = false;
	new_node->isFile = true;
	new_node->isOperator = false;
	new_node->isDelim = false;
	new_node->DELIM = NULL;

	// ! STEP 2 :connecting the t_operator node
	new_node->fl = node_file;
	
	// ! STEP 3 : NULL init other substructures nodes
	new_node->operator = NULL;
	new_node->cmd = NULL;

	// ! STEP 4 : init prev and next both to NULL
	new_node->prev = NULL;
	new_node->next = NULL;
	// -------------------global init node--------------------



	// -------------------init substructure--------------------
	
	// ! STEP 1 : init file name
	new_node->fl->file_name = cleaned;
	
	// ! STEP 2 : false init everything
	new_node->fl->file_exist = false;
	new_node->fl->auth_r = false;
	new_node->fl->auth_w = false;
	new_node->fl->auth_x = false;
	
	
	// ! STEP 3 : access functions
	if (access(cleaned, F_OK) == 0)
	{
		new_node->fl->file_exist = true;
		if (access(cleaned, R_OK) == 0)
			new_node->fl->auth_r = true;
		if (access(cleaned, W_OK) == 0)
			new_node->fl->auth_w = true;
		if (access(cleaned, X_OK) == 0) // really usefull ?
			new_node->fl->auth_x = true;
	}

	// -------------------init substructure--------------------

	// ! last step : lstaddback
	lstadd_back(pars, new_node);
}

bool	is_token_operator(char *splited, char *cleaned)
{
	// ! checks if there is a operator intead of an operator within quotes
	if (!ft_strcmp(splited, cleaned))
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

bool is_token_redir_delim(char *cleaned)
{
	if (!ft_strcmp(cleaned, RED_IN_DELIM))
		return true;
	return false;
	
}

void	new_node_operator(t_pars **pars, char *cleaned)
{
	// ! Allocate a new node;
	t_pars	*new_node;
	t_operator *node_operator;
	

	// -------------------malloc t_pars node + sub_node--------------------
	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	node_operator = malloc(sizeof(t_operator));
	if (!node_operator)
		return ;
	// -------------------malloc t_pars node + sub_node--------------------




	// -------------------global init node--------------------

	// ! STEP 1 : init bools switches
	new_node->isCommand = false;
	new_node->cmd = NULL;

	new_node->isFile = false;
	new_node->fl = NULL;

	new_node->isDelim = false;
	new_node->DELIM = NULL;

	new_node->isOperator = true;
	new_node->operator = node_operator;
	
	new_node->prev = NULL;
	new_node->next = NULL;

	// ! STEP 2 :connecting the t_operator node
	
	// -------------------global init node--------------------

	// -------------------init substructure--------------------
	
	// ! STEP 1 : Init everything at false;
	new_node->operator->pipe = false;
	new_node->operator->redir_in = false;
	new_node->operator->redir_in_delim = false;
	new_node->operator->redir_out = false;
	new_node->operator->redir_out_app = false;
	
	// ! STEP 2 : Init the right switch
	if (!ft_strcmp(cleaned, PIPE))
		new_node->operator->pipe = true;
	else if (!ft_strcmp(cleaned, RED_IN))
		new_node->operator->redir_in = true;
	else if (!ft_strcmp(cleaned, RED_IN_DELIM))
		new_node->operator->redir_in_delim = true;
	else if (!ft_strcmp(cleaned, RED_OUT))
		new_node->operator->redir_out = true;
	else if (!ft_strcmp(cleaned, RED_OUT_APP))
		new_node->operator->redir_out_app = true;

	// -------------------init substructure--------------------

	// ! last step : lstaddback
	lstadd_back(pars, new_node);
}

bool is_last_node_operator(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isOperator)
		return (true);
	return (false);
}

bool is_last_node_pipe(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->operator->pipe)
		return (true);
	return (false);
}

bool is_last_node_redir(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->operator->redir_in || last->operator->redir_out || last->operator->redir_out_app)
		return (true);
	return (false);
}

bool is_last_node_redir_delim(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->operator->redir_in_delim)
		return (true);
	return (false);
}

bool is_last_node_cmd(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isCommand)
		return (true);
	return (false);
}

bool is_last_node_file(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isFile)
		return (true);
	return (false);
}

void	new_node_delim(t_pars **pars, char *cleaned)
{
	// ! Allocate a new node;
	t_pars	*new_node;

	// -------------------malloc t_pars node + sub_node--------------------
	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	// -------------------malloc t_pars node + sub_node--------------------




	// -------------------global init node--------------------

	// ! STEP 1 : init bools switches
	new_node->isDelim = true;
	new_node->DELIM = cleaned;

	
	new_node->isCommand = false;
	new_node->cmd = NULL;
	
	new_node->isFile = false;
	new_node->fl = NULL;
	
	new_node->isOperator = false;
	new_node->operator = NULL;
	

	// ! STEP 3 : init prev and next both to NULL
	new_node->prev = NULL;
	new_node->next = NULL;
	// -------------------global init node--------------------


	// ! last step : lstaddback
	lstadd_back(pars, new_node);

}

bool is_token_pipe(char *splited, char *cleaned)
{
	if (!ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, PIPE))
			return (true);
	}
	return (false);
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


	// ! allocate the struct + checks
	while (cur->cleaned_prompt[i]) // iterate over all tokens	
	{
		last_p_node = lstlast(*pars);
		if (!last_p_node->prev) // first node == cmd
		{
			new_node_command(pars, u_alloc, &i);
			// i++;
		}
		
		else if ((is_last_node_cmd(pars)))
		{
			if (is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
		}

		else if (is_last_node_operator(pars))
		{
			if (is_last_node_pipe(pars) && !is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_command(pars, u_alloc, &i);
			else if (is_last_node_redir(pars) && !is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_file(pars, cur->cleaned_prompt[i]);
			else if (is_last_node_redir_delim(pars) && !is_token_operator(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_delim(pars, cur->cleaned_prompt[i]);
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
