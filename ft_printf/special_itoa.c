/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:19:04 by nterbach          #+#    #+#             */
/*   Updated: 2023/04/29 15:31:16 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	size_calc(int n);
static char	*negative_conversion(int n, int size);
static char	*positive_conversion(int n, int size);

/*
	Basically ft_itoa but it terminates the string with -7 instead of 0
	(the positive and negative conversion functions do that to be precise).
*/
char	*s_itoa(int n)
{
	char	*result;
	int		size;

		size = size_calc(n);
	if (n < 0)
		result = negative_conversion(n, size);
	else
		result = positive_conversion(n, size);
	return (result);
}

/*
	Calculates the size that n will occupy when converted to a string,
	assuming sizeof(char) = 1. The terminating character is taken into
	account as well as the '-' if necessary.
*/
static int	size_calc(int n)
{
	int	size;
	int	test;	

		test = n;
	if (n < 0)
	{
		size = 3;
		while (test <= -10)
		{
			test /= 10;
			size++;
		}
	}
	if (n >= 0)
	{
		size = 2;
		while (test >= 10)
		{
			test /= 10;
			size++;
		}
	}
	return (size);
}

static char	*negative_conversion(int n, int size)
{
	char	*str;
	int		digit;

		str = (char *) malloc(size * sizeof(char));
	if (str != NULL)
	{
		str[0] = '-';
		size--;
		str[size] = -7;
		while (size > 1)
		{
			size--;
			digit = (n % 10) * (-1);
			n /= 10;
			str[size] = (char) digit + '0';
		}
	}
	return (str);
}

static char	*positive_conversion(int n, int size)
{
	char	*str;
	int		digit;

		str = (char *) malloc(size * sizeof(char));
	if (str != NULL)
	{
		size--;
		str[size] = -7;
		while (size > 0)
		{
			size--;
			digit = n % 10;
			n /= 10;
			str[size] = (char) digit + '0';
		}
	}
	return (str);
}
