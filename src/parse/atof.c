/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benhajdahmaneilyes <benhajdahmaneilyes@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:35 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:29:40 by benhajdahma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <ctype.h>

double	ft_atof(const char *str)
{
	double	result;
	double	factor;
	int		sign;
	int		seen_dot;

	result = 0.0;
	factor = 1.0;
	sign = 1;
	seen_dot = 0;
	while (isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (seen_dot)
				break ;
			seen_dot = 1;
		}
		else if (ft_isdigit(*str))
		{
			if (seen_dot)
			{
				factor /= 10.0;
				result = result + (*str - '0') * factor;
			}
			else
				result = result * 10.0 + (*str - '0');
		}
		else
			break ;
		str++;
	}
	return (sign * result);
}
