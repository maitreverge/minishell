/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:51:26 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 19:05:32 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	part_1(char *str, int *i, size_t *result)
{
	while (str[(*i)] && !is_whitespace(str[(*i)])
		&& !is_any_quote(str[(*i)]) && !is_operator_char(str[(*i)]))
		(*i)++;
	(*result)++;
}

void	part_2(int *start_quote, int *end_quote, char *str, int *i)
{
	(*start_quote) = str[(*i)];
	while (str[(*i)] && (*start_quote) != (*end_quote))
	{
		(*i)++;
		if (str[(*i)] == (*start_quote))
		{
			(*end_quote) = (*start_quote);
			(*i)++;
			break ;
		}
	}
}

void	part_3(char *str, int *i, size_t *result)
{
	if ((str[(*i)] == '<' && str[(*i) + 1] == '<')
		|| (str[(*i)] == '>' && str[(*i) + 1] == '>'))
		(*i) += 2;
	else
		(*i)++;
	(*result)++;
}

size_t	parsing_countwords(char *str)
{
	size_t	result;
	int		start_quote;
	int		end_quote;
	int		i;

	i = 0;
	result = 0;
	while (str[i])
	{
		start_quote = 0;
		end_quote = 0;
		while (is_whitespace(str[i]) && str[i])
			i++;
		if (!is_any_quote(str[i]) && str[i]
			&& !is_whitespace(str[i]) && !is_operator_char(str[i]))
			part_1(str, &i, &result);
		else if (is_any_quote(str[i]) && str[i])
		{
			part_2(&start_quote, &end_quote, str, &i);
			result++;
		}
		else if (is_operator_char(str[i]) && str[i])
			part_3(str, &i, &result);
	}
	return (result);
}
