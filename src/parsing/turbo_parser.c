/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 18:09:44 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_buff_part_1(char *starting_quote, int *i, char *str)
{
	(*starting_quote) = str[(*i)];
	(*i)++;
	while (str[(*i)] && str[(*i)] != (*starting_quote))
	{
		if ((*starting_quote) == D_QUOTE && str[(*i)] == DOLL_ENV
			&& str[(*i) + 1] && str[(*i) + 1] != (*starting_quote))
			return (true);
		(*i)++;
	}
	return (false);
}

bool	is_buff_valid_doll(char *str)
{
	char	starting_quote;
	int		i;

	i = 0;
	starting_quote = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		while (!is_any_quote(str[i]) && str[i])
		{
			if (str[i] == DOLL_ENV && str[i + 1] && !is_any_quote(str[i + 1]))
				return (true);
			i++;
		}
		if (is_any_quote(str[i]) && str[i])
		{
			if (is_buff_part_1(&starting_quote, &i, str))
				return (true);
		}
		if (str[i])
			i++;
	}
	return (false);
}

void	turbo_parser(char *p, t_pars **pars, t_env_list **env, t_utils **s_u)
{
	t_utils	*u;
	t_alloc	*utils;
	int		len_splited_prompt;

	utils = malloc(sizeof(t_alloc));
	if (!utils)
		exit (-1);
	u = *s_u;
	if (unclosed_quotes(p))
	{
		(*pars)->MasterKill = true;
		(*pars)->last_exit_status = 1;
		free(utils);
		ft_putendl_fd("error : unclosed quotes detected\n", 2);
		return ;
	}
	len_splited_prompt = parsing_countwords(p);
	u = utils_init_struct(len_splited_prompt);
	utils->splitted_prompt = parsing_split(p);
	utils->cleaned_prompt = clean_prompt(utils->splitted_prompt, &u, env, pars);
	utils->paths = extract_paths(env);
	pars_alloc(pars, &utils);
	free_s_utils(&u);
	free_t_alloc(utils);
}
