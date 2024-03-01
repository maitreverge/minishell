/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:47:41 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 18:48:43 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	alloc_pars(char *str, t_split_utils *u)
{
	u->start = u->i;
	if ((str[u->i] == '<' && str[u->i + 1] == '<')
		|| (str[u->i] == '>' && str[u->i + 1] == '>'))
		u->i += 2;
	else
		u->i++;
}

void	loop_sub_quote(char *str, t_split_utils *u)
{
	while (str[u->i] && u->start_quote != u->end_quote)
	{
		u->i++;
		if (str[u->i] == u->start_quote)
		{
			u->end_quote = u->start_quote;
			u->i++;
			break ;
		}
	}
}
