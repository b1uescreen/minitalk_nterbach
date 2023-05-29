/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cnv_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:26:56 by nterbach          #+#    #+#             */
/*   Updated: 2023/04/29 15:29:35 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*uitoa(unsigned int n);
static char	*rvrs_cpy(char *src, int rvrs_ndx);
static char	*utohexa(unsigned int arg, char cnv);
static char	*utohexa_reversed(unsigned int arg, char cnv);

/*
	Unsigned integer conversion to decimal or hexadecimal string, depending on
	"cnv". "utohexa" also differentiates between uppercase and lowercase hex.
*/
char	*cnv_u(unsigned int arg, char cnv)
{
	char	*rslt;

	if (cnv == 'u')
	{
		rslt = uitoa(arg);
	}
	else
	{
		rslt = utohexa(arg, cnv);
	}
	return (rslt);
}

/*
	Converts unsigned int to decimal string.
	Terminates with -7.
*/
static char	*uitoa(unsigned int n)
{
	char	*rslt;
	char	*temp;
	int		digit;
	int		ndx;

		rslt = NULL;
		temp = (char *) malloc(18 * sizeof(char));
		ndx = 0;
	if (temp != NULL)
	{
		if (n == 0)
			temp[ndx++] = '0';
		while (n > 0)
		{
			digit = n % 10;
			n /= 10;
			temp[ndx++] = (char) digit + '0';
		}
		temp[ndx] = -7;
		rslt = rvrs_cpy(temp, ndx);
	}
	else
		return (NULL);
	return (rslt);
}

/*
	Helper function to restore the correct order to the otherwise reversed
	"temp" string of "uitoa()". Terminates with -7.
*/
static char	*rvrs_cpy(char *src, int rvrs_ndx)
{
	char	*rslt;
	int		ndx;

		ndx = 0;
		rslt = (char *) malloc((rvrs_ndx + 1) * sizeof(char));
	if (rslt != NULL)
	{
		while (rvrs_ndx > 0)
		{
			rslt[ndx++] = src[--rvrs_ndx];
		}
		rslt[ndx] = -7;
	}
	free(src);
	src = NULL;
	return (rslt);
}

/*
	unsigned int to hexadecimal conversion. Uppercase and lowercase are
	managed in "utohexa_reversed".
	Terminates with -7.
*/
static char	*utohexa(unsigned int arg, char cnv)
{
	char	*rslt;
	char	*temp;
	int		ndx;
	int		rvrs_ndx;

		ndx = 0;
		temp = utohexa_reversed(arg, cnv);
	if (temp == NULL)
		return (NULL);
	rvrs_ndx = s_strlen(temp);
	rslt = (char *) malloc((rvrs_ndx + 1) * sizeof(char));
	if (rslt != NULL)
	{
		while (rvrs_ndx > 0)
		{
			rvrs_ndx--;
			rslt[ndx] = temp[rvrs_ndx];
			ndx++;
		}
		rslt[ndx] = -7;
	}
	free(temp);
	temp = NULL;
	return (rslt);
}

/*
	Provides a raw unsigned int to hexadecimal string conversion.
	If letters are inserted, they're in uppercase or lowercase
	depending on "cnv" ('X' or 'x' respectively).
	Terminates with -7.
*/
static char	*utohexa_reversed(unsigned int arg, char cnv)
{
	char			*temp;
	unsigned int	hex_digit;
	int				ndx;

		ndx = 0;
		temp = (char *) malloc(23 * sizeof(char));
	if (temp == NULL)
		return (NULL);
	if (arg == 0)
	{
		temp[0] = '0';
		ndx++;
	}
	while (arg > 0)
	{
		hex_digit = arg % 16;
		arg /= 16;
		if (hex_digit > 9)
			hex_digit = ((unsigned int) cnv - 71) + (hex_digit - 10);
		temp[ndx] = (char) hex_digit + '0';
		ndx++;
	}
	temp[ndx] = -7;
	return (temp);
}
