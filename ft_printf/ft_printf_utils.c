/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:47:03 by nterbach          #+#    #+#             */
/*   Updated: 2023/04/29 15:30:24 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	s_str_writer(char *s1, char *s2, char *rslt);

/*
	Basically strlen but it expects a terminating -7 (integer notation).
*/
int	s_strlen(char *str)
{
	int	ndx;

		ndx = 0;
	while (str[ndx] != -7)
	{
		ndx++;
	}
	return (ndx);
}

/*
	Customized strjoin. If the update is NULL (-> something went wrong),
	the current string "main_str" is freed if it's not also NULL.
	If the update exists but there is no main_str, then update is returned.
	If both aren't NULL, it joins them using the -7-terminating
	"s_str_writer".
*/
char	*s_strjoin(char *main_str, char *update)
{
	char	*rslt;
	int		main_len;
	int		updt_len;

	if (update == NULL && main_str != NULL)
	{
		free(main_str);
		return (NULL);
	}
	else if (main_str == NULL)
	{
		return (update);
	}
	else
	{
		main_len = s_strlen(main_str);
		updt_len = s_strlen(update);
		rslt = (char *) malloc(main_len + updt_len + 1);
		s_str_writer(main_str, update, rslt);
		main_str = NULL;
		update = NULL;
		return (rslt);
	}
}

/*
	This function joins two strings into a third one ("rslt").
	"rslt" has to be allocated with the right size beforehand.
	Both strings s1 and s2 have to be -7-terminated and the result
	will also be terminated with -7 (integer notation).
	s1 and s2 are freed after joining.
*/
static void	s_str_writer(char *s1, char *s2, char *rslt)
{
	int	ndx;
	int	s2_ndx;

		ndx = 0;
		s2_ndx = 0;
	if (rslt != NULL)
	{
		while (s1[ndx] != -7)
		{
			rslt[ndx] = s1[ndx];
			ndx++;
		}
		while (s2[s2_ndx] != -7)
		{
			rslt[ndx] = s2[s2_ndx];
			ndx++;
			s2_ndx++;
		}
		rslt[ndx] = -7;
	}
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
}

/*
	Basically strdup but it handles NULL as a string with content "(null)".
	It also terminates the duplicate with -7 while still expecting a null-
	terminated string as input.
*/
char	*s_strdup(char *s)
{
	char	*copy;
	int		ndx;

		ndx = 0;
	if (s == NULL)
	{
		s = "(null)";
	}
	while (s[ndx] != '\0')
	{
		ndx++;
	}
	copy = (char *) malloc((ndx + 1) * sizeof(char));
	if (copy != NULL)
	{
		ndx = 0;
		while (s[ndx] != '\0')
		{
			copy[ndx] = s[ndx];
			ndx++;
		}
		copy[ndx] = -7;
	}
	return (copy);
}
