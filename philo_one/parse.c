/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:33:32 by hjung             #+#    #+#             */
/*   Updated: 2021/02/07 00:30:01 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	parse_num(char *str)
{
	int		i;
	int		num;
	
	i = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (-1);
		i++;
	}
	num = ft_atoi(str);
	if (num <= 0)
		return (-1);
	else
		return (num);
}

int			parse(t_table *table, char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (i == 1 && ((table->nbr_philos = parse_num(argv[i])) == -1))
			return (1);
		if (i == 2 && (table->time_to_die = parse_num(argv[i])) == -1)
			return (1);
		if (i == 3 && (table->time_to_eat = parse_num(argv[i])) == -1)
			return (1);
		if (i == 4 && (table->time_to_sleep = parse_num(argv[i])) == -1)
			return (1);
		if (i == 5 && (table->nbr_eat = parse_num(argv[i])) == -1)
			return (1);
		i++;
	}
	return (0);
}