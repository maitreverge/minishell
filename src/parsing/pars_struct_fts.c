/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_struct_fts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:22:54 by flverge           #+#    #+#             */
/*   Updated: 2024/01/28 08:33:30 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_pars_struct(t_pars **pars)
{
	t_pars *current;

	current = *pars;
	current->test = 'X'; // to delete in the .h as well
	current->command = false;
	current->file = false;
	current->pipe = false;
	current->red_in = false;
	current->red_in_delim = false;
	current->red_in = false;
	current->red_out_app = false;
	
}