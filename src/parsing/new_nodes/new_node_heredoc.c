/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:53:26 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:16:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	new_node_here_doc(t_pars **pars, char *cleaned)
{
	t_pars	*new_node;

	new_node = malloc(sizeof(t_pars));
	if (!new_node)
		return ;
	new_node->is_here_doc = true;
	new_node->here_doc = ft_strdup(cleaned);
	new_node->is_command = false;
	new_node->cmd = NULL;
	new_node->is_file = false;
	new_node->fl = NULL;
	new_node->is_operator = false;
	new_node->operator = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	lstadd_back(pars, new_node);
}
