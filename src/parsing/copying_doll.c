/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpying_doll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:01:30 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 14:41:46 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_exit_status(t_pars **pars, int *start, t_utils *u)
{
	char	*nbr;

	nbr = ft_itoa(lstfirst(*pars)->last_exit_status);
	while (nbr[(*start)])
	{
		u->result[u->i][u->k] = nbr[(*start)];
		u->k++;
		(*start)++;
	}
	free(nbr);
}

static void	part_1(char *buff, int *start, int *i, char **temp_str)
{
	while (!is_any_quote(buff[(*i)]) && buff[(*i)] != DOLL_ENV
		&& !is_whitespace(buff[(*i)]) && buff[(*i)])
		(*i)++;
	(*temp_str) = (char *)ft_calloc(sizeof(char), (*i) + 1);
	ft_strncpy((*temp_str), &buff[(*start)], (*i));
}

static void	part_2(t_env_list *current_env, int *start, t_utils *u)
{
	while (current_env->value[(*start)])
	{
		u->result[u->i][u->k] = current_env->value[(*start)];
		u->k++;
		(*start)++;
	}
}

void	copying_doll(char *buff, t_utils **u, t_env_list **s_env, t_pars **pars)
{
	char		*temp_str;
	int			i;
	int			start;

	temp_str = NULL;
	i = 0;
	start = 0;
	part_1(buff, &start, &i, &temp_str);
	while (*s_env)
	{
		if (!ft_strcmp(temp_str, "?"))
		{
			handle_exit_status(pars, &start, (*u));
			break ;
		}
		else if (!ft_strcmp(temp_str, (*s_env)->key))
		{
			part_2(*s_env, &start, (*u));
			break ;
		}
		(*s_env) = (*s_env)->next;
	}
	(*u)->j += i;
	free(temp_str);
}
