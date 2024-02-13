/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:36:46 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 20:34:40 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	detecting_quotes(char *str, int *start_quote, int *end_quote, int *i)
{
	while (is_any_quote(str[(*i)]) && str[(*i)])
	{
		*start_quote = str[(*i)];
		while (str[(*i)] && *start_quote != *end_quote)
		{
			(*i)++;
			if (str[(*i)] == *start_quote)
			{
				*end_quote = *start_quote;
				(*i)++;
				break ;
			}
		}
		*end_quote = 0;
		if (is_whitespace(str[(*i)]) || !str[(*i)])
			break ;
		while (str[(*i)] && !is_whitespace(str[(*i)])
			&& !is_any_quote(str[(*i)]))
			(*i)++;
		if (is_whitespace(str[(*i)]) || !str[(*i)])
			break ;
	}
}

void	allocation(char **buffer, char *str, size_t len_s)
{
	int	start_quote;
	int	end_quote;
	int	i;
	size_t	j;
	size_t	start;

	j = 0;
	i = 0;
	start = 0;
	if (!str)
		return ;
	while (str[i])
	{
		start_quote = 0;
		end_quote = 0;
		while (is_whitespace(str[i]) && str[i])
			i++;
		if (is_any_quote(str[i]) && str[i])
		{
			start = i;
			detecting_quotes(str, &start_quote, &end_quote, &i);
		}
		else if (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]))
		{
			start = i;
			while (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]))
			{
				while (str[i] && !is_whitespace(str[i])
					&& !is_any_quote(str[i]))
					i++;
				if (is_whitespace(str[i]) || !str[i])
					break ;
				if (is_any_quote(str[i]) && str[i])
					detecting_quotes(str, &start_quote, &end_quote, &i);
			}
		}
		if (j < len_s)
		{
			buffer[j] = ft_calloc(sizeof(char), (i - start + 1));
			if (!buffer[j])
				return ;
			ft_strncpy(buffer[j], &str[start], i - start);
			j++;
		}
	}
}

