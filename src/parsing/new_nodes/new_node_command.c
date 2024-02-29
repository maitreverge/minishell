/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:14:45 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 18:34:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static t_pars	*initialize_new_node(t_alloc *u, int i)
{
	t_command	*new_node_command;
	t_pars		*new_node;

	new_node_command = malloc(sizeof(t_command));
	new_node = malloc(sizeof(t_pars));
	if (!new_node || !new_node_command)
		return (NULL);
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
	new_node->cmd->command_name = ft_strdup(u->cleaned_prompt[i]);
	return (new_node);
}

static void	new_node_cmd_2(t_pars *node, t_alloc *u, int start, int *i)
{
	int	j;
	int	len;

	j = 0;
	len = (*i) - start + 2;
	node->cmd->name_options_args = (char **)ft_calloc(len, sizeof(char *));
	if (!node->cmd->name_options_args)
		exit (-1);
	node->cmd->name_options_args[j] = ft_strdup(node->cmd->command_path);
	j++;
	start++;
	while (j < len - 1)
	{
		node->cmd->name_options_args[j] = ft_strdup(u->cleaned_prompt[start]);
		j++;
		start++;
	}
}

void	new_node_command(t_pars **pars, t_alloc **utils, int *i)
{
	t_alloc		*u;
	t_pars		*nde;
	int			start;

	u = *utils;
	nde = initialize_new_node(u, *i);
	if (testing_builtin(u->cleaned_prompt[*i]))
	{
		nde->cmd->isBuiltin = true;
		nde->cmd->command_path = ft_strdup(u->cleaned_prompt[*i]);
	}
	else
	{
		nde->cmd->isBuiltin = false;
		nde->cmd->command_path = join_path_cmd(u->cleaned_prompt[*i], u->paths);
	}
	start = *i;
	while (u->cleaned_prompt[*i])
	{
		if (is_token_opr(u->splitted_prompt[*i + 1], u->cleaned_prompt[*i + 1]))
			break ;
		(*i)++;
	}
	new_node_cmd_2(nde, u, start, i);
	lstadd_back(pars, nde);
}
