/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:35 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 16:09:32 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <ctype.h>

static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

static double	process_digits(const char **str, double *factor, int *seen_dot)
{
	double	result;

	result = 0.0;
	while (**str)
	{
		if (**str == '.')
		{
			if (*seen_dot)
				break ;
			*seen_dot = 1;
		}
		else if (isdigit(**str))
		{
			if (*seen_dot)
				result += (**str - '0') * (*factor /= 10.0);
			else
				result = result * 10.0 + (**str - '0');
		}
		else
			break ;
		(*str)++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	double	factor;
	int		sign;
	int		seen_dot;

	while (isspace(*str))
		str++;
	sign = handle_sign(&str);
	factor = 1.0;
	seen_dot = 0;
	result = process_digits(&str, &factor, &seen_dot);
	return (sign * result);
}
