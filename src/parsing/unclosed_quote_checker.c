/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quote_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:51:14 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 15:24:50 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	part_1(size_t *i, char *str, char *s_quote, char *closing_quote)
{
	while (str[(*i)] != D_QUOTE && str[(*i)] != S_QUOTE && str[(*i)])
		(*i)++;
	if (str[(*i)] == D_QUOTE || str[(*i)] == S_QUOTE)
	{
		(*s_quote) = str[(*i)];
		(*i)++;
		while (str[(*i)] && (*s_quote) != (*closing_quote))
		{
			if (str[(*i)] == (*s_quote))
			{
				(*closing_quote) = (*s_quote);
				break ;
			}
			(*i)++;
		}
	}
}

bool	unclosed_quotes(char *str)
{
	char	starting_quote;
	char	closing_quote;
	size_t	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		starting_quote = 0;
		closing_quote = 0;
		part_1(&i, str, &starting_quote, &closing_quote);
		if (str[i])
			i++;
	}
	if (starting_quote != closing_quote)
		return (true);
	return (false);
}
