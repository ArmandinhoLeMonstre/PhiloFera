/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:59:01 by armitite          #+#    #+#             */
/*   Updated: 2024/12/27 12:40:21 by armitite         ###   ########.fr       */
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
    long long    starving_t;
    long long    eating_t;
    long long    sleeping_t;
    long long    time;
    int     p_total;
    int     meals_nbr;
    int death;
    int meals_check;
    int meals_eaten;
    pthread_mutex_t *mutex_forks;
    pthread_mutex_t *mutex_print;
    pthread_mutex_t *mutex_data;
} t_data;

typedef struct s_philo
{
    int n;
    int fork_left;
    int fork_right;
    int dead;
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
int	ft_check_num(char **av, int ac);
void	*monitoring(void *arg);
int check_meals(t_data *data);
int philo_dead(t_philo *p, t_data *data);

#endif
