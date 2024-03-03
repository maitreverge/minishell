/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copying_doll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:01:30 by flverge           #+#    #+#             */
/*   Updated: 2024/03/03 15:04:40 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	handle_exit_status(int *start, t_utils *u)
{
	char	*nbr;

	nbr = ft_itoa(last_exit_status);
	while (nbr[(*start)])
	{
		u->result[u->i][u->k] = nbr[(*start)];
		u->k++;
		(*start)++;
	}
	free(nbr);
}

static void	j_1(char *buff, int *start, int *i, char **temp_str)
{
	while (!is_any_quote(buff[(*i)]) && buff[(*i)] != DOLL_ENV
		&& !is_whitespace(buff[(*i)]) && buff[(*i)])
		(*i)++;
	(*temp_str) = (char *)ft_calloc(sizeof(char), (*i) + 1);
	ft_strncpy((*temp_str), &buff[(*start)], (*i));
}

static void	j_2(t_env_list *current_env, int *start, t_utils *u)
{
	while (current_env->value[(*start)])
	{
		u->result[u->i][u->k] = current_env->value[(*start)];
		u->k++;
		(*start)++;
	}
}

void	cop_doll(char *bu, t_utils **u, t_env_list **s_env)
{
	char		*temp_str;
	int			i;
	int			start;

	temp_str = NULL;
	i = 0;
	start = 0;
	j_1(bu, &start, &i, &temp_str);
	while (*s_env)
	{
		if (!ft_strcmp(temp_str, "?"))
		{
			handle_exit_status(&start, (*u));
			break ;
		}
		else if (!ft_strcmp(temp_str, (*s_env)->key))
		{
			j_2(*s_env, &start, (*u));
			break ;
		}
		(*s_env) = (*s_env)->next;
	}
	(*u)->j += i;
	free(temp_str);
}
