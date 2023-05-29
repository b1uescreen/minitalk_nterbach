/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:25:55 by nterbach          #+#    #+#             */
/*   Updated: 2023/04/29 15:30:51 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*mission_ctrl(const char *format, va_list args);
static char	*add_str(const char *format, char *crr, int start, int sub_len);

/*
	Imitates the standard conversions cspdiuxX% of printf.
*/
int	ft_printf(const char *format, ...)
{
	char	*rslt;
	va_list	args;
	int		rslt_len;
	int		bytes_written;

	if (format == NULL)
	{
		return (-3);
	}
	va_start(args, format);
	rslt = mission_ctrl(format, args);
	va_end(args);
	if (rslt == NULL)
	{
		return (-2);
	}
	else
	{
		rslt_len = s_strlen(rslt);
		bytes_written = write(1, rslt, rslt_len);
		free(rslt);
		rslt = NULL;
		return (bytes_written);
	}
}

/*
	Loops through the format string and manages all conversions.
*/
static char	*mission_ctrl(const char *format, va_list args)
{
	char	*rslt;
	int		anchor;
	int		ndx;

		rslt = NULL;
		anchor = 0;
		ndx = 0;
	while (format[ndx])
	{
		if (format[ndx++] == '%')
		{
			rslt = add_str(format, rslt, anchor, (ndx - 1 - anchor));
			anchor = ndx + 1;
			rslt = add_cnvrsn(rslt, args, format[ndx]);
			ndx++;
		}
	}
	rslt = add_str(format, rslt, anchor, (ndx - anchor));
	return (rslt);
}

/*
	Adds the part of the format string that has been traversed by 
	"mission_control" so far. It's joined with the current string
	if there is one.
*/
static char	*add_str(const char *format, char *crr, int start, int sub_len)
{
	char	*rslt;
	char	*temp;
	int		ndx;

		rslt = NULL;
		ndx = 0;
	if (sub_len >= 0)
	{
		temp = (char *) malloc((sub_len + 1) * sizeof(char));
		if (temp != NULL)
		{
			while (ndx < sub_len)
			{
				temp[ndx] = format[start + ndx];
				ndx++;
			}
			temp[ndx] = -7;
			rslt = s_strjoin(crr, temp);
			temp = NULL;
		}
		return (rslt);
	}
	return (crr);
}
