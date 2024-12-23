/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:59:01 by armitite          #+#    #+#             */
/*   Updated: 2024/12/23 14:10:06 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


typedef struct s_data
{
    int     p_total;
    long long    starving_t;
    long long    eating_t;
    long long    sleeping_t;
    int     meals_nbr;
    long long    time;
    int death;
    int meals_check;
    int meals_eaten;
    pthread_mutex_t *mutex_forks;
    pthread_mutex_t *mutex_death;
    pthread_mutex_t *mutex_meals;
    pthread_mutex_t *mutex_print;
} t_data;

typedef struct s_philo
{
    int n;
    int fork_left;
    int fork_right;
    long long time;
    long long t_last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;


int	ft_usleep(long long time);
int	ft_atoi(const char *str);
long long	time_now(void);
int create_philo(t_philo **philo, t_data *test);

#endif
