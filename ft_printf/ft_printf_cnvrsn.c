/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cnvrsn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:41:36 by nterbach          #+#    #+#             */
/*   Updated: 2023/04/29 15:30:07 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*converter(va_list args, char cnv);
static char	*cnv_s(int arg, char cnv);
static char	*cnv_p(void *arg);
static char	*ptohexa_reversed(unsigned long long arg);

/*
	Does the conversion specified by "cnv" and joins it with the current
	result "rslt".
	The function "s_strjoin" frees the "substring", therefore it's set to
	NULL here.
*/
char	*add_cnvrsn(char *rslt, va_list args, char cnv)
{
	char	*substring;

	substring = converter(args, cnv);
	rslt = s_strjoin(rslt, substring);
	substring = NULL;
	return (rslt);
}

/*
	Decides which function will be used for any given conversion.
	All substrings will be terminated with -7 
	(as long as they're not NULL).
*/
static char	*converter(va_list args, char cnv)
{
	char	*substring;

		substring = NULL;
	if (cnv == 'c' || cnv == 'd' || cnv == 'i')
		substring = cnv_s(va_arg(args, int), cnv);
	else if (cnv == 'u' || cnv == 'x' || cnv == 'X')
		substring = cnv_u(va_arg(args, unsigned int), cnv);
	else if (cnv == 'p')
		substring = cnv_p(va_arg(args, void *));
	else if (cnv == 's')
		substring = s_strdup(va_arg(args, char *));
	else if (cnv == '%')
	{
		substring = (char *) malloc(2 * sizeof(char));
		if (substring != NULL)
		{
			substring[0] = '%';
			substring[1] = -7;
		}
	}
	else
		return (NULL);
	return (substring);
}

/*
	Signed integer conversion, also used for char conversion.
	Terminates with -7.
*/
static char	*cnv_s(int arg, char cnv)
{
	char	*rslt;

		rslt = NULL;
	if (cnv == 'i' || cnv == 'd')
	{
		rslt = s_itoa(arg);
	}
	else if (cnv == 'c')
	{
		rslt = (char *) malloc(2 * sizeof(char));
		if (rslt != NULL)
		{
			rslt[0] = (char) arg;
			rslt[1] = -7;
		}
	}
	return (rslt);
}

/*
	Pointer conversion. Uses an unsigned long long int to represent the
	memory address of the pointer target until it's converted.
	Terminates with -7.
*/
static char	*cnv_p(void *ptr)
{
	char				*rslt;
	char				*temp;
	int					ndx;
	int					rvrs_ndx;
	unsigned long long	addr;

		ndx = 0;
		addr = (unsigned long long) ptr;
	if (ptr == NULL)
		addr = 0;
	temp = ptohexa_reversed(addr);
	if (temp == NULL)
		return (NULL);
	rvrs_ndx = s_strlen(temp);
	rslt = (char *) malloc((rvrs_ndx + 1) * sizeof(char));
	if (rslt != NULL)
	{
		while (rvrs_ndx > 0)
			rslt[ndx++] = temp[--rvrs_ndx];
		rslt[ndx] = -7;
	}
	free(temp);
	temp = NULL;
	return (rslt);
}

/*
	Provides a raw conversion that is in reverse order.
	Again, -7-termination.
*/
static char	*ptohexa_reversed(unsigned long long arg)
{
	char				*temp;
	unsigned long long	hex_digit;
	int					ndx;

		ndx = 0;
		temp = (char *) malloc(23 * sizeof(char));
	if (temp == NULL)
		return (NULL);
	if (arg == 0)
		temp[ndx++] = '0';
	while (arg > 0)
	{
		hex_digit = arg % 16;
		arg /= 16;
		if (hex_digit > 9)
			hex_digit = (hex_digit - 10) + 49;
		temp[ndx++] = (char) hex_digit + '0';
	}
	temp[ndx++] = 'x';
	temp[ndx++] = '0';
	temp[ndx] = -7;
	return (temp);
}
