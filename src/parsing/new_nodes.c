/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:14:45 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 15:27:20 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	new_node_command(t_pars **pars, t_alloc **utils, int *i)
{
	t_command	*new_node_command;
	t_alloc		*u;
	t_pars		*new_node;
	int			start;
	int			j;

	u = *utils;
	j = 0;
	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	new_node_command = malloc(sizeof(t_command));
	if (!new_node_command)
		return ;
	new_node->isCommand = true;
	new_node->cmd = new_node_command;
	new_node->isFile = false;
	new_node->fl = NULL;
	new_node->isOperator = false;
	new_node->operator = NULL;
	new_node->isHereDoc = false;
	new_node->here_doc = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->cmd->command_name = u->cleaned_prompt[*i];
	if (testing_builtin(u->cleaned_prompt[*i]))
	{
		new_node->cmd->isBuiltin = true;
		new_node->cmd->command_path = u->cleaned_prompt[*i];
	}
	else
	{
		new_node->cmd->command_path = join_path_command(u->cleaned_prompt[*i], u->paths);
		new_node->cmd->isBuiltin = false;
	}
	start = *i;
	while (u->cleaned_prompt[*i])
	{
		if (is_token_operator(u->splitted_prompt[*i + 1], u->cleaned_prompt[*i + 1]))
			break ;
		(*i)++;
	}
	int len = (*i) - start + 2;
	new_node->cmd->name_options_args = (char **)ft_calloc(len, sizeof(char *));
	if (!new_node->cmd->name_options_args)
		exit (-1);
	new_node->cmd->name_options_args[j] = new_node->cmd->command_path;
	j++;
	start++;
	while (j < len - 1)
	{
		new_node->cmd->name_options_args[j] = u->cleaned_prompt[start];
		j++;
		start++;
	}
	lstadd_back(pars, new_node);
}

void	new_node_file(t_pars **pars, char *cleaned)
{
	t_pars	*new_node;
	t_file	*node_file;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	node_file = malloc(sizeof(t_file));
	if (!node_file)
		return ;
	new_node->isFile = true;
	new_node->fl = node_file;
	new_node->isCommand = false;
	new_node->cmd = NULL;
	new_node->isOperator = false;
	new_node->operator = NULL;
	new_node->isHereDoc = false;
	new_node->here_doc = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->fl->file_name = cleaned;
	new_node->fl->file_exist = false;
	new_node->fl->auth_r = false;
	new_node->fl->auth_w = false;
	new_node->fl->auth_x = false;
	if (access(cleaned, F_OK) == 0)
	{
		new_node->fl->file_exist = true;
		if (access(cleaned, R_OK) == 0)
			new_node->fl->auth_r = true;
		if (access(cleaned, W_OK) == 0)
			new_node->fl->auth_w = true;
		if (access(cleaned, X_OK) == 0)
			new_node->fl->auth_x = true;
	}
	lstadd_back(pars, new_node);
}

void	new_node_operator(t_pars **pars, char *cleaned)
{
	t_operator	*node_operator;
	t_pars		*new_node;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	node_operator = malloc(sizeof(t_operator));
	if (!node_operator)
		return ;
	new_node->isOperator = true;
	new_node->operator = node_operator;
	new_node->isCommand = false;
	new_node->cmd = NULL;
	new_node->isFile = false;
	new_node->fl = NULL;
	new_node->isHereDoc = false;
	new_node->here_doc = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->operator->pipe = false;
	new_node->operator->redir_in = false;
	new_node->operator->redir_in_delim = false;
	new_node->operator->redir_out = false;
	new_node->operator->redir_out_app = false;
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
	lstadd_back(pars, new_node);
}

void	new_node_here_doc(t_pars **pars, char *cleaned)
{
	t_pars	*new_node;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	new_node->isHereDoc = true;
	new_node->here_doc = cleaned;
	new_node->isCommand = false;
	new_node->cmd = NULL;
	new_node->isFile = false;
	new_node->fl = NULL;
	new_node->isOperator = false;
	new_node->operator = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	lstadd_back(pars, new_node);
}
