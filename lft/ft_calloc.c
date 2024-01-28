/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:43:43 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/16 14:34:22 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*lignes 23-24 servent a eviter des calculs de non-entiers*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*dest;
	size_t		res;

	dest = NULL;
	if (!nmemb || !size)
		return (malloc(0));
	res = size * nmemb;
	if (res / size != nmemb)
		return (0);
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero((unsigned char *)dest, res);
	return (dest);
}
