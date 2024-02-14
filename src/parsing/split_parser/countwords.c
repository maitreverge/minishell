/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:51:26 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 11:35:24 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
		if (is_any_quote(str[i]) && str[i])
		{
			while (is_any_quote(str[i]) && str[i])
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
				end_quote = 0;
				if (is_whitespace(str[i]) || !str[i])
				{
					result++;
					break ;
				}
				while (str[i] && !is_whitespace(str[i])
					&& !is_any_quote(str[i]))
					i++;
				if (is_whitespace(str[i]) || !str[i])
				{
					result++;
					break ;
				}
			}
		}
		else if (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]))
		{
			while (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]))
			{
				while (str[i] && !is_whitespace(str[i])
					&& !is_any_quote(str[i]))
					i++;
				if (is_whitespace(str[i]) || !str[i])
				{
					result++;
					break ;
				}
				if (is_any_quote(str[i]) && str[i])
				{
					while (is_any_quote(str[i]) && str[i])
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
						end_quote = 0;
						if (is_whitespace(str[i]) || !str[i])
						{
							result++;
							break ;
						}
						while (str[i] && !is_whitespace(str[i])
							&& !is_any_quote(str[i]))
							i++;
						if (is_whitespace(str[i]) || !str[i])
						{
							result++;
							break ;
						}
					}
				}
			}
		}
	}
	return (result);
}
