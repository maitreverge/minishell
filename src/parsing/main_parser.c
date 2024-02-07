/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:26:07 by flverge           #+#    #+#             */
/*   Updated: 2024/02/07 18:22:09 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pars *init_1st_node_pars(void)
{
	t_pars *new;
	new = lstnew(0);
	return (new);
}

int main(int ac, char **av, char **envp)//, char **env
{
	t_env_list	*s_env;
	t_utils		*utils;
	t_pars		*pars;

	char *line;

	s_env = NULL;
	utils = NULL;
	pars = NULL;
	
	copy_env_into_list(&s_env, envp);

	line = readline("minishell$ ");


	// ! init the first node
	if (!pars)
		pars = init_1st_node_pars();
	
	turbo_parser(line, &pars, &s_env, &utils);

	// ! execution function
	// execution(&pars, &s_env, s)
	
	free_s_env(&s_env);
	
	
	free(line);

}