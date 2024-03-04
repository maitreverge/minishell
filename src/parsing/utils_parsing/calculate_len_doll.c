/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_doll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:43:40 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:36:28 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	p_p_1(char *buff, int *start, int *i, char **temp_str)
{
	while (!is_any_quote(buff[(*i)]) && buff[(*i)] != DOLL_ENV
		&& !is_whitespace(buff[(*i)]) && buff[(*i)])
		(*i)++;
	(*temp_str) = (char *)ft_calloc(sizeof(char), (*i) + 1);
	ft_strncpy((*temp_str), &buff[(*start)], (*i));
}

void	calc_len_doll(char *b, t_utils **u, t_env_list **env)
{
	char		*temp_str;
	int			i;
	int			start;
	t_env_list *temp;

	temp = *env; // * fixed leaks
	i = 0;
	start = 0;
	p_p_1(b, &start, &i, &temp_str);
	while (temp)
	{
		if (!ft_strcmp(temp_str, "?"))
		{
			(*u)->real_len += int_len(g_last_exit_status);
			break ;
		}
		else if (!ft_strcmp(temp_str, temp->key))
		{
			(*u)->real_len += ft_strlen(temp->value);
			break ;
		}
		temp = temp->next;
	}
	(*u)->j += i;
	free(temp_str);
}
