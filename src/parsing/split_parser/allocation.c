/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:36:46 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 11:48:13 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_split_utils *init_u_alloc(void)
{
	t_split_utils *new;

	new->start_quote = 0;
	new->end_quote = 0;
	new->i = 0;
	new->j = 0;
	new->start = 0;
	new->result = 0;
	return (new);
}

static void	sub_detecting_quotes(char *str, t_split_utils **split)
{
	t_split_utils *u;

	u = *split;
	while (is_any_quote(str[u->i]) && str[u->i])
	{
		u->start_quote = str[u->i];
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
		u->end_quote = 0;
		if (is_whitespace(str[u->i]) || !str[u->i])
			break ;
		while (str[u->i] && !is_whitespace(str[u->i])
			&& !is_any_quote(str[u->i]))
			u->i++;
		if (is_whitespace(str[u->i]) || !str[u->i])
			break ;
	}
}

void	allocation(char **buffer, char *str, size_t len_s)
{
	t_split_utils *u;

	u = init_u_alloc();
	if (!str)
		return ;
	while (str[u->i])
	{
		u->start_quote = 0;
		u->end_quote = 0;
		while (is_whitespace(str[u->i]) && str[u->i])
			u->i++;
		if (is_any_quote(str[u->i]) && str[u->i])
		{
			u->start = u->i;
			sub_detecting_quotes(str, &u);
		}
		else if (!is_any_quote(str[u->i]) && str[u->i] && !is_whitespace(str[u->i]))
		{
			u->start = u->i;
			while (!is_any_quote(str[u->i]) && str[u->i] && !is_whitespace(str[u->i]))
			{
				while (str[u->i] && !is_whitespace(str[u->i])
					&& !is_any_quote(str[u->i]))
					u->i++;
				if (is_whitespace(str[u->i]) || !str[u->i])
					break ;
				if (is_any_quote(str[u->i]) && str[u->i])
					sub_detecting_quotes(str, &u);
			}
		}
		if (u->j < len_s)
		{
			buffer[u->j] = ft_calloc(sizeof(char), (u->i - u->start + 1));
			if (!buffer[u->j])
				return ;
			ft_strncpy(buffer[u->j], &str[u->start], u->i - u->start);
			u->j++;
		}
	}
}

