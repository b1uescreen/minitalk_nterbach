/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:28:59 by nterbach          #+#    #+#             */
/*   Updated: 2023/04/28 19:40:55 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

extern int		ft_printf(const char *format, ...);
extern char		*add_cnvrsn(char *rslt, va_list args, char cnv);
extern char		*cnv_u(unsigned int arg, char cnv);
extern char		*s_strdup(char *s);
extern char		*s_strjoin(char *main_str, char *update);
extern char		*s_itoa(int n);
extern int		s_strlen(char *str);

#endif
