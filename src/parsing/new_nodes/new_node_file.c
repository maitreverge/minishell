/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:46:46 by flverge           #+#    #+#             */
/*   Updated: 2024/02/26 11:58:04 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static t_pars	*initialize_new_node(char *cleaned)
{
	t_pars	*new_node;
	t_file	*node_file;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return (NULL);
	node_file = malloc(sizeof(t_file));
	if (!node_file)
		return (NULL);
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
	new_node->fl->file_name = ft_strdup(cleaned);
	new_node->fl->file_exist = false;
	new_node->fl->auth_r = false;
	new_node->fl->auth_w = false;
	new_node->fl->auth_x = false;
	return (new_node);
}

void	new_node_file(t_pars **pars, char *cleaned)
{
	t_pars	*new_node;

	new_node = initialize_new_node(cleaned);
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
	else
	{
		new_node->fl->auth_r = true;
		new_node->fl->auth_w = true;
		new_node->fl->auth_x = true; // recently added
	}
	lstadd_back(pars, new_node);
}
