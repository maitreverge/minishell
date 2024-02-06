/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:26:07 by flverge           #+#    #+#             */
/*   Updated: 2024/02/06 13:04:19 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/**
 * @brief My main function for parsing checking only
 * 
 * @param ac 
 * @param av 
 * @param envp 
 * @return int 
 */
int main(int ac, char **av, char **envp)//, char **env
{
	t_pars *pars; // mains struct which will contains the parsing output
	t_env_list *s_env;
	char *line;

	s_env = NULL;
	
	copy_env_into_list(&s_env, envp); // copy env into struct
	char *post_pars; // temp checker

	

	pars = NULL; // init struct to NULL as safety

	line = readline("minishell$ "); // This mf leaks, can't do anything
	turbo_parser(line, &pars, &s_env);
	
	// add_history(line);
	free(line);

}