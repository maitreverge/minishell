/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:52:19 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 19:36:56 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static t_pars	*initialize_new_node(void)
{
	t_pars		*new_node;
	t_operator	*node_operator;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return (NULL);
	node_operator = malloc(sizeof(t_operator));
	if (!node_operator)
		return (NULL);
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
	return (new_node);
}

void	new_node_operator(t_pars **pars, char *cleaned)
{
	t_pars		*new_node;

	new_node = initialize_new_node();
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
