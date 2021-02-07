/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:03:24 by hjung             #+#    #+#             */
/*   Updated: 2021/02/07 16:41:49 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
# include <sys/time.h>

typedef struct		s_table
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_eat;		
	int				cnt_tot_eat;		// 철학자 모두가 밥을 먹은 횟수
	int				is_dead;		// 죽은 철학자가 있는지 체크하는 변수
	unsigned long	base_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_msg;		// 메시지 출력을 꼬이게 하지 않기 위해 mutex 사용
}					t_table;

typedef struct		s_philo
{
	int				nbr;
	int				fork1;
	int				fork2;
	int				cnt_eat;
	long			last_meal;		// 마지막으로 식사시작 시간을 저장해 죽을때가 됐는지 판단하기 위함
	pthread_mutex_t lock;			// 철학자가 각자 mutex 잠금을 할 수 있는 자물쇠를 하나씩 가진다고 생각하면 될듯
	pthread_t		tid;			// thread_create 후 tid가 저장될 변수
	t_table			*table;			// 함수 매개변수로 table 안 들고 다녀도 philo 를 통해 테이블 참조할수 있게 하기 위함.
}					t_philo;

int					parse(t_table *table, char **argv);
int					init_table(t_table *table, t_philo *philos);

int					ft_atoi(const char *str);
unsigned long		get_time(void);

int					p_error(char *str);

#endif