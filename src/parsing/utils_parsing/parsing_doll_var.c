/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_doll_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:55:25 by flverge           #+#    #+#             */
/*   Updated: 2024/03/04 13:17:34 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	x_1(t_utils *u, char *buff, t_env_list **s_env)
{
	while (!is_any_quote(buff[u->j]) && buff[u->j])
	{
		u->expansion = true;
		if (buff[u->j] == DOLL_ENV && u->expansion)
		{
			u->j++;
			calc_len_doll(&buff[u->j], &u, s_env); // ! leaks
		}
		else
		{
			u->j++;
			u->real_len++;
		}
	}
}

static void	x_2(t_utils *u, char *buff, t_env_list **s_env)
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
			calc_len_doll(&buff[u->j], &u, s_env);
		}
		else
		{
			u->j++;
			u->real_len++;
		}
	}
	u->j++;
}

static void	x_3(t_utils *u, char *buff, t_env_list **s_env)
{
	while (!is_any_quote(buff[u->j]) && buff[u->j])
	{
		u->expansion = true;
		if (buff[u->j] == DOLL_ENV && u->expansion)
		{
			u->j++;
			cop_doll(&buff[u->j], &u, s_env);
		}
		else
		{
			u->result[u->i][u->k] = buff[u->j];
			u->j++;
			u->k++;
		}
	}
}

static void	x_4(t_utils *u, char *buff, t_env_list **s_env)
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
			cop_doll(&buff[u->j], &u, s_env);
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

void	par_doll_var(t_utils **ut, char *b, t_env_list **env)
{
	t_utils	*u;

	u = *ut;
	u->expansion = true;
	while (b[u->j])
	{
		x_1(u, b, env); // ! leaks
		if (is_any_quote(b[u->j]))
			x_2(u, b, env);
	}
	u->j = 0;
	u->k = 0;
	u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
	while (b[u->j])
	{
		x_3(u, b, env);
		if (is_any_quote(b[u->j]))
			x_4(u, b, env);
	}
}
