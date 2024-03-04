/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/03/04 16:27:07 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	turbo_parser(char *p, t_pars **pa, t_env_list **env, t_utils **s_u)
{
	t_utils	*u;
	t_alloc	*utils;
	int		len_splited_prompt;

	if (!p || *p == '\0')
		return (1);
	utils = malloc(sizeof(t_alloc));
	if (!utils)
		exit (-1);
	u = *s_u;
	if (unclosed_quotes(p))
	{
		return ((*pa)->masterkill = true, g_last_exit_status = 1,
			free(utils),
			ft_putendl_fd("error : unclosed quotes detected", 2), 0);
	}
	len_splited_prompt = parsing_countwords(p);
	u = utils_init_struct(len_splited_prompt);
	utils->splitted_prompt = parsing_split(p);
	utils->cleaned_prompt = clean_prpt(utils->splitted_prompt, &u, env);
	utils->paths = extract_paths(env);
	pars_alloc(pa, &utils);
	free_s_utils(&u);
	free_t_alloc(utils);
	return (0);
}
