/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iben-haj <iben-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:10:35 by iben-haj          #+#    #+#             */
/*   Updated: 2024/11/22 09:10:36 by iben-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <ctype.h>

double ft_atof(const char *str)
{
    double result = 0.0;
    double factor = 1.0;
    int sign = 1;
    int seen_dot = 0;

    // Skip whitespace
    while (isspace(*str)) // TODO: forbiden Function 
        str++;

    // Handle sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Process digits
    while (*str)
    {
        if (*str == '.')
        {
            if (seen_dot)
                break;  // Second dot, stop parsing
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
            {
                result = result * 10.0 + (*str - '0');
            }
        }
        else
        {
            break;  // Non-digit character, stop parsing
        }
        str++;
    }

    return sign * result;
}