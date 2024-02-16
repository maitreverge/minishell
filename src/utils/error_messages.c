/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:25:45 by flverge           #+#    #+#             */
/*   Updated: 2024/02/16 15:29:10 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_pars **pars)
{
	t_pars *current;

	current = *pars;

	if (current->error_message == 1) // double consecutives operators -> puts 1
	{
		
	}
}