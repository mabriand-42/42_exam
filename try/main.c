/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:31:59 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/19 13:48:30 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	int ret;
	int ptf;

	ret = ft_printf("Moi c'est %s, j'ai %d ans soit en héxadécimal %x ans ! Mais pas de négatif en héxa par contre : %d => %x\n", "marie briand", 23, 23, -42, -42);
	ptf = printf("Moi c'est %s, j'ai %d ans soit en héxadécimal %x ans ! Mais pas de négatif en héxa par contre : %d => %x\n", "marie briand", 23, 23, -42, -42);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("Moi c'est %s\n", "marie briand");
	ptf = printf("Moi c'est %s\n", "marie briand");
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("j'ai %d ans\n", 23);
	ptf = printf("j'ai %d ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("soit en héxadécimal %x ans\n", 23);
	ptf = printf("soit en héxadécimal %x ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("Moi c'est %2.s\n", "marie briand");
	ptf = printf("Moi c'est %2.s\n", "marie briand");
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("j'ai %6.5d ans\n", 23);
	ptf = printf("j'ai %6.5d ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("soit en héxadécimal %3.3x ans\n", 23);
	ptf = printf("soit en héxadécimal %3.3x ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("Moi c'est %2.9s\n", "marie briand");
	ptf = printf("Moi c'est %2.9s\n", "marie briand");
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("j'ai %6.10d ans\n", 23);
	ptf = printf("j'ai %6.10d ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("soit en héxadécimal %3.0x ans\n", 23);
	ptf = printf("soit en héxadécimal %3.0x ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("Moi c'est %2s\n", "marie briand");
	ptf = printf("Moi c'est %2s\n", "marie briand");
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("j'ai %10d ans\n", 23);
	ptf = printf("j'ai %10d ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	ret = ft_printf("soit en héxadécimal %12x ans\n", 23);
	ptf = printf("soit en héxadécimal %12x ans\n", 23);
	printf("ret = %d || ptf = %d\n", ret, ptf);
	printf("--------------\n");
	return (0);
}
