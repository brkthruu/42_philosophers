/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:18:49 by hjung             #+#    #+#             */
/*   Updated: 2021/02/12 12:48:57 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int argc, char *argv[])
{
	t_table		table;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (p_error("Error: put right number of arguments\n"));
	if (parse(&table, argv))
		return (p_error("Error: bad argument\n"));
	if (!(philos = malloc(sizeof(t_philo) * table.nbr_philos)))
		return (p_error("Error: malloc failed\n"));
	init_table(&table, philos);
	close_sem(&table);
	free(philos);
	return (0);
}