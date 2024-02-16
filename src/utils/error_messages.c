/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:25:45 by flverge           #+#    #+#             */
/*   Updated: 2024/02/16 17:54:34 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_pars **pars)
{
	t_pars *current;

	current = *pars;

	if (current->error_message == 1)  // unclosed quotes 
	{
		perror("Error : Unclosed quote detected.\nAborting.\n");
		current->last_exit_status = 1;
	}
	else if (current->error_message == 2) // double consecutives operators -> puts 1 
	{
		perror("Error : Multiples consecutives operators.\nAborting.\n");
		current->last_exit_status = 2;
	}
	
}