/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:57:43 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:40:43 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_any_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (true);
	return (false);
}

bool	is_operator_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

bool	is_buff_part_1(char *starting_quote, int *i, char *str)
{
	(*starting_quote) = str[(*i)];
	(*i)++;
	while (str[(*i)] && str[(*i)] != (*starting_quote))
	{
		if ((*starting_quote) == D_QUOTE && str[(*i)] == DOLL_ENV
			&& str[(*i) + 1] && str[(*i) + 1] != (*starting_quote))
			return (true);
		(*i)++;
	}
	return (false);
}

bool	is_buff_valid_doll(char *str)
{
	char	starting_quote;
	int		i;

	i = 0;
	starting_quote = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		while (!is_any_quote(str[i]) && str[i])
		{
			if (str[i] == DOLL_ENV && str[i + 1] && !is_any_quote(str[i + 1]))
				return (true);
			i++;
		}
		if (is_any_quote(str[i]) && str[i])
		{
			if (is_buff_part_1(&starting_quote, &i, str))
				return (true);
		}
		if (str[i])
			i++;
	}
	return (false);
}
