/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:07:25 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 11:32:41 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	s_1(t_utils *u, char **buff, t_env_list **s_env, t_pars **pars)
{
	u->j = 0;
	u->real_len = 0;
	par_doll_var(&u, buff[u->i], s_env, pars);
	u->i++;
}

static void	s_2(t_utils *u, char **buff)
{
	while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j] != 0)
	{
		u->j++;
		u->real_len++;
	}
	if (is_any_quote(buff[u->i][u->j]))
	{
		u->starting_quote = buff[u->i][u->j];
		u->j++;
		while (buff[u->i][u->j]
			&& buff[u->i][u->j] != u->starting_quote)
		{
			u->j++;
			u->real_len++;
		}
		u->j++;
	}
}

static void	s_3(t_utils *u, char **buff)
{
	while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j])
	{
		u->result[u->i][u->k] = buff[u->i][u->j];
		u->j++;
		u->k++;
	}
	if (is_any_quote(buff[u->i][u->j]))
	{
		u->starting_quote = buff[u->i][u->j];
		u->j++;
		while (buff[u->i][u->j]
			&& buff[u->i][u->j] != u->starting_quote)
		{
			u->result[u->i][u->k] = buff[u->i][u->j];
			u->j++;
			u->k++;
		}
		u->j++;
	}
}

char	**clean_prpt(char **b, t_utils **ut, t_env_list **env, t_pars **p)
{
	t_utils	*u;

	u = *ut;
	while (b[u->i])
	{
		while (is_buff_valid_doll(b[u->i]))
			s_1(u, b, env, p);
		if (!b[u->i])
			break ;
		u->j = 0;
		u->real_len = 0;
		while (b[u->i][u->j] != 0)
			s_2(u, b);
		u->j = 0;
		u->k = 0;
		u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
		while (b[u->i][u->j] != 0)
			s_3(u, b);
		u->i++;
	}
	return (u->result);
}
