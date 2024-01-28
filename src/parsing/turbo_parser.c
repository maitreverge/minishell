/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/01/28 08:33:57 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	turbo_parser(char *prompt, t_pars **pars, char **envp)
{
	// ? 🤔 Does this function needs to be called during the nodes init 
	init_pars_struct(pars);
	
	// ! STEP 1 : Take the whole string and "clean it"
	
	
	// ! STEP 2 : Create a new node each and everytime I met a Pipe, redirection, or something else
	// ! STEP 3 : Allocate substrings into substructures for commands and files
}