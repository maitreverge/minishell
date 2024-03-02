/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_doll_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:55:25 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:39:03 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	part_1(t_utils *u, char *buff, t_env_list **s_env, t_pars **pars)
{
	while (!is_any_quote(buff[u->j]) && buff[u->j])
	{
		u->expansion = true;
		if (buff[u->j] == DOLL_ENV && u->expansion)
		{
			u->j++;
			calculate_len_doll(&buff[u->j], &u, s_env, pars);
		}
		else
		{
			u->j++;
			u->real_len++;
		}
	}
}

static void	part_2(t_utils *u, char *buff, t_env_list **s_env, t_pars **pars)
{
	u->starting_quote = buff[u->j];
	u->j++;
	if (u->starting_quote == S_QUOTE)
		u->expansion = false;
	while (buff[u->j] && buff[u->j] != u->starting_quote)
	{
		if (buff[u->j] == DOLL_ENV && u->expansion)
		{
			u->j++;
			calculate_len_doll(&buff[u->j], &u, s_env, pars);
		}
		else
		{
			u->j++;
			u->real_len++;
		}
	}
	u->j++;
}

static void	part_3(t_utils *u, char *buff, t_env_list **s_env, t_pars **pars)
{
	while (!is_any_quote(buff[u->j]) && buff[u->j])
	{
		u->expansion = true;
		if (buff[u->j] == DOLL_ENV && u->expansion)
		{
			u->j++;
			copying_doll(&buff[u->j], &u, s_env, pars);
		}
		else
		{
			u->result[u->i][u->k] = buff[u->j];
			u->j++;
			u->k++;
		}
	}
}

static void	part_4(t_utils *u, char *buff, t_env_list **s_env, t_pars **pars)
{
	u->starting_quote = buff[u->j];
	u->j++;
	if (u->starting_quote == S_QUOTE)
		u->expansion = false;
	while (buff[u->j] && buff[u->j] != u->starting_quote)
	{
		if (buff[u->j] == DOLL_ENV && u->expansion)
		{
			u->j++;
			copying_doll(&buff[u->j], &u, s_env, pars);
		}
		else
		{
			u->result[u->i][u->k] = buff[u->j];
			u->j++;
			u->k++;
		}
	}
	u->j++;
}

void	parsing_doll_var(t_utils **ut, char *b, t_env_list **env, t_pars **pa)
{
	t_utils	*u;

	u = *ut;
	u->expansion = true;
	while (b[u->j])
	{
		part_1(u, b, env, pa);
		if (is_any_quote(b[u->j]))
			part_2(u, b, env, pa);
	}
	u->j = 0;
	u->k = 0;
	u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
	while (b[u->j])
	{
		part_3(u, b, env, pa);
		if (is_any_quote(b[u->j]))
			part_4(u, b, env, pa);
	}
}
