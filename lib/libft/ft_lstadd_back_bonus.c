/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:34:32 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/12 12:10:34 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
/*
#include <stdio.h>

 int	main(void)
{
	printf("Testing ....\n");
	printf("Test (NULL, NULL) cases\n");
	ft_lstadd_back(NULL, NULL);
	printf("Passed Ok!\n");
	printf("Test ("", NULL) cases\n");
	ft_lstadd_back(0x0, NULL);
	printf("Passed Ok!\n");
	printf("Test (NULL, NULL) cases\n");
	ft_lstadd_back(0x0, NULL);
	printf("Passed Ok!\n");
	return (0);
}
*/