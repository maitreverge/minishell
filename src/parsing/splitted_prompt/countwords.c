/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:51:26 by flverge           #+#    #+#             */
/*   Updated: 2024/02/15 16:07:55 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_operator_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

// ! simplified version which split with operators
size_t	parsing_countwords(char *str)
{
	int	start_quote;
	int	end_quote;
	int	i;
	size_t	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		start_quote = 0;
		end_quote = 0;
		while (is_whitespace(str[i]) && str[i])
			i++;
		if (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]) && !is_operator_char(str[i]))
		{
			while (str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]) && !is_operator_char(str[i]))
				i++;
			result++;
		}
		else if (is_any_quote(str[i]) && str[i])
		{
			start_quote = str[i];
			while (str[i] && start_quote != end_quote)
			{
				i++;
				if (str[i] == start_quote)
				{
					end_quote = start_quote;
					i++;
					break ;
				}
			}
			result++;
		}
		else if (is_operator_char(str[i]) && str[i])
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				i += 2;
			else
				i++;
			result++;
		}
	}
	return (result);
}
