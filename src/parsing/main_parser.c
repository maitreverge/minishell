/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:26:07 by flverge           #+#    #+#             */
/*   Updated: 2024/01/28 17:37:20 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include "../../include/minishell.h"

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
	
	char *line;
	char *post_pars; // temp checker

	pars = NULL; // init struct to NULL as safety
	post_pars = NULL;

	line = readline("minishell$ "); // This mf leaks, can't do anything
	printf("Line = %s\n", line);
	turbo_parser(line, &pars, envp);
	
	// add_history(line);
	free(line);

}