/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:36:46 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 19:55:36 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	allocation(char **buffer, char const *str, size_t len_s)
{
	char	start_quote;
	char	end_quote;
	size_t	i;
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
					break ;
				while (str[i] && !is_whitespace(str[i])
					&& !is_any_quote(str[i]))
					i++;
				if (is_whitespace(str[i]) || !str[i])
					break ;
			}
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
							break ;
						while (str[i] && !is_whitespace(str[i])
							&& !is_any_quote(str[i]))
							i++;
						if (is_whitespace(str[i]) || !str[i])
							break ;
					}
				}
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

