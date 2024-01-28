/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:56:58 by glambrig          #+#    #+#             */
/*   Updated: 2023/05/08 11:49:11 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LONG_MIN -9223372036854775806LL
# define LONG_MAX 9223372036854775807LL
# include "../libft.h"
# include <stdarg.h>
# include <stdint.h>

int		put_c(int n);
int		put_s(char *str);
int		put_p(void *num, char mode);
int		put_d(int n);
int		put_u(unsigned int n, unsigned int counter);
int		put_small_x(long long int n);
int		put_big_x(long long int n);
int		check_char(const char *str, int i, va_list list);
int		ft_printf(const char *str, ...);
char	put_alpha(long long rem);
char	put_alpha_lowcase(long long rem);
int		counter_func(size_t num);
int		convert_dec_to_hex(unsigned long n, char mode, int *i);
int		convert_dec_to_hex_x(unsigned int n, char mode, int *i);

#endif
