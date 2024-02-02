/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:34:17 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/02 17:48:28 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(void **array, int size)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
