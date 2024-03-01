/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:48:00 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/01 15:49:24 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

size_t	lstlen(t_pars *lst)
{
	size_t	res;
	t_pars	*temp;

	temp = lst;
	res = 0;
	while (lst)
	{
		res++;
		lst = lst->next;
	}
	lst = temp;
	return (res);
}

/*Returns the number of elements in a given void ** array.*/
size_t	size_of_ptr_ptr(void **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (0);
	while ((char *)arr[len] != NULL)
		len++;
	return (len);
}
