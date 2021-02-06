/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:01:58 by hjung             #+#    #+#             */
/*   Updated: 2021/02/07 01:18:23 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init_table(t_table *table, t_philo *philo)
{
	int			i;
	
	i = 0;
	if (!(table->fork = malloc(sizeof(pthread_mutex_t) * table->nbr_philos)))
		return(p_error("Error: malloc failed\n"));
	
	
}

int main(int argc, char *argv[])
{
	t_table		table;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (p_error("Error: put right number of arguments\n"));
	if (parse(&table, argv))
		return (p_error("Error: bad argument\n"));
	if (!(philos = malloc(sizeof(t_philo) * table.nbr_philos)))
		return (p_error("Error: malloc failed\n"));
	
	return (0);
}