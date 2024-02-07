/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_struct_fts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:22:54 by flverge           #+#    #+#             */
/*   Updated: 2024/02/07 18:22:36 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	init_pars_struct(t_pars **pars)
// {
// 	t_pars *current;

// 	current = *pars;
// 	current->test = 'X'; // to delete in the .h as well
// 	current->command = false;
// 	current->file = false;
// 	current->pipe = false;
// 	current->red_in = false;
// 	current->red_in_delim = false;
// 	current->red_in = false;
// 	current->red_out_app = false;
	
// }

t_utils *utils_init_struct(int len) // ! free this single node
{
	t_utils *current;

	current = malloc(sizeof(t_utils));
	if (!current)
		exit(-1);

	// current = *utils;
	// current->result = NULL;

	current->result = ft_calloc((len + 1), sizeof(char *));
	if (!current->result)
		exit(-1); // ! maybe freeing shit right here

	current->result[len] = 0;
	current->to_allocate = NULL;
	current->i = 0;
	current->j = 0;
	current->k = 0;
	current->starting_quote = 0;
	current->end_quote = 0;
	current->real_len = 0;
	
	return (current);
}