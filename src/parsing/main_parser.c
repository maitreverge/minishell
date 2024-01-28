/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:26:07 by flverge           #+#    #+#             */
/*   Updated: 2024/01/28 07:41:36 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int main(int ac, char **av, char **envp)//, char **env
{
	// (void)ac;
	// (void)av;
	char *line;

	printf("AC = %i\n", ac);
	line = readline("minishell$ ");
	printf("Line = %s\n", line);
	// add_history(line);
	free(line);

}