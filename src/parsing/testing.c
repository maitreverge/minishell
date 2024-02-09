// #include "../../minishell.h"

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_split.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/02 15:21:44 by flverge           #+#    #+#             */
// /*   Updated: 2023/10/06 16:10:26 by flverge          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../minishell.h"

// void	p_alloc(char *splited, char *cleaned)
// {
// 	int i; // index of both split and cleaned

// 	i = 0;
// 	// ! step 1 : chase redir in operator, matching splited and cleaned
	
// 	if (!ft_strncmp(cleaned, RED_IN, 2) && !ft_strncmp(cleaned, splited, 2))
// 	{
// 		// (*pars)->isRedirIn = true;
// 		printf("OUI");
// 		return ;
// 		// break ;	
// 	} 
// 	else if (!ft_strncmp(cleaned, RED_IN_DELIM, 3) && !ft_strncmp(cleaned, splited, 3))
// 	{
// 		// (*pars)->isRedirIn = true;
// 		printf("OUI");
// 		return ;
// 		// break ;
// 	}
// 		// i++;

// 	printf("mdr nope");
// 	// * YES ==> Turn off the operator in the first node
	
// }

// // int main(int ac, char **av)
// int main()
// {
// 	// char *split = av[0];
// 	// char *clean = av[1];

// 	char split[] = "<<";
// 	char clean[] = "<";

// 	printf("Split = %s\n", split);
// 	printf("Clean = %s\n", clean);

// 	p_alloc(split, clean);
// }