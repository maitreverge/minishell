/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 15:53:39 by flverge          ###   ########.fr       */
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

void	turbo_parser(char *prompt, t_pars **pars, t_env_list **s_env, t_utils **s_utils)
{
	t_utils	*u;
	t_alloc	*utils_alloc;
	int		len_splited_prompt;

	utils_alloc = malloc(sizeof(t_alloc));
	if (!utils_alloc)
		exit (-1);
	u = *s_utils;
	if (unclosed_quotes(prompt))
	{
		(*pars)->MasterKill = true;
		(*pars)->last_exit_status = 1;
		free(utils_alloc);
		ft_putendl_fd("error : unclosed quotes detected\n", 2);
		return ;
	}
	len_splited_prompt = parsing_countwords(prompt);
	u = utils_init_struct(len_splited_prompt);
	utils_alloc->splitted_prompt = parsing_split(prompt);
	utils_alloc->cleaned_prompt = ft_clean_prompt(utils_alloc->splitted_prompt, &u, s_env, pars);
	utils_alloc->paths = extract_paths(s_env);
	pars_alloc(pars, &utils_alloc);
	free_s_utils(&u);
	free_t_alloc(utils_alloc);
}
