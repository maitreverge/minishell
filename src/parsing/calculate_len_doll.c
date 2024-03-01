/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_len_doll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:43:40 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 14:48:05 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	part_1(char *buff, int *start, int *i, char **temp_str)
{
	while (!is_any_quote(buff[(*i)]) && buff[(*i)] != DOLL_ENV
		&& !is_whitespace(buff[(*i)]) && buff[(*i)])
		(*i)++;
	(*temp_str) = (char *)ft_calloc(sizeof(char), (*i) + 1);
	ft_strncpy((*temp_str), &buff[(*start)], (*i));
}

void	calculate_len_doll(char *buff, t_utils **u, t_env_list **s_env, t_pars **pars)
{
	char		*temp_str;
	int			i;
	int			start;

	i = 0;
	start = 0;
	part_1(buff, &start, &i, &temp_str);
	while (*s_env)
	{
		if (!ft_strcmp(temp_str, "?"))
		{
			(*u)->real_len += int_len((*pars)->last_exit_status);
			break ;
		}
		else if (!ft_strcmp(temp_str, (*s_env)->key))
		{
			(*u)->real_len += ft_strlen((*s_env)->value);
			break ;
		}
		(*s_env) = (*s_env)->next;
	}
	(*u)->j += i;
	free(temp_str);
}
