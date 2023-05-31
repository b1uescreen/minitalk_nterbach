/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:28:59 by nterbach          #+#    #+#             */
/*   Updated: 2023/05/31 17:29:54 by nterbach         ###   ########.fr       */
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
extern char		*nt_strdup(char *s);
extern char		*nt_strjoin(char *main_str, char *update);
extern char		*nt_itoa(int n);
extern int		nt_strlen(char *str);

#endif
