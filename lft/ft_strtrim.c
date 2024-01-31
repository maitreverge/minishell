/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:18 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/18 12:23:56 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* For start_i:
 * Instead of looking for i in set, we're iterating through set to find s[i]
 * and stopping if it's not found,
 * thus delimiting the start index of our new string
 *
 * For end_i:
 * end_i >= start_i because start_i is the start of our new string*/

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start_i;
	int		end_i;
	char	*new;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen((char *)s1);
	start_i = 0;
	while (start_i < len && ft_strchr(set, s1[start_i]))
		start_i++;
	end_i = len - 1;
	while (end_i >= start_i && ft_strchr(set, s1[end_i]))
		end_i--;
	new = ft_substr(s1, start_i, (end_i - start_i + 1));
	return (new);
}
