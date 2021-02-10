/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_all_philos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:25:46 by hjung             #+#    #+#             */
/*   Updated: 2021/02/10 18:23:13 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		someone_dead(t_philo *philo, unsigned long current_time)
{
	sem_wait(philo->table->m_dead);
	if (philo->table->is_dead > 0 ||
		current_time - philo->last_meal > philo->table->time_to_die)
	{
		sem_post(philo->table->m_dead);
		return (1);
	}
	sem_post(philo->table->m_dead);
	return (0);
}

int		fully_eat(t_philo *philo)
{
	if (philo->table->nbr_eat == -1)
		return (0);
	sem_wait(philo->table->m_eat);
	if (philo->table->tot_eat == philo->table->nbr_philos)
	{
		sem_post(philo->table->m_eat);
		return (1);
	}
	sem_post(philo->table->m_eat);
	return (0);
}
