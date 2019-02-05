/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 04:20:43 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_parser.h"
#include "ft_printf.h"

#define DAY 86400

// TODO Think about additional seconds

typedef struct	s_date
{
	int	year; /// 1970 ?
	char		mth; /// 0 ?
	char		day; ///1
	char 		hr; /// 0 ?
	char 		min; /// 0 ?
	char 		sec; /// 0 ?
}				t_date;

static char mts[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int ft_upd_year(t_date *dt, long int *n)
{
	if ((*n < (IS_LEAP_YEAR(dt->year) + 365) * DAY && *n >= 0) ||
			(*n > -1 * (IS_LEAP_YEAR(dt->year - 1) + 365) * DAY && *n < 0))
		return (0);
	if (*n > 0)
	{
		*n -= (IS_LEAP_YEAR(dt->year) + 365) * DAY;
		++dt->year;
		return (1);
	}
	*n += (IS_LEAP_YEAR(dt->year - 1) + 365) * DAY;
	--dt->year;
	return (1);
}

int ft_upd_month(t_date *dt, long int *n)
{
	if ((*n < (mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY
			&& *n >= 0) || (*n > -1 *
			(mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY
			&& *n < 0))
		return (0);
	if (*n > 0)
	{
		if (*n < (mts[dt->mth] + (dt->mth==1 && IS_LEAP_YEAR(dt->year))) * DAY)
			return (0);
		*n -= (mts[dt->mth] + (dt->mth==1 && IS_LEAP_YEAR(dt->year))) * DAY;
		if (dt->mth == 11 && !(dt->mth = 0))
			++dt->year;
		else
			++dt->mth;
		return (1);
	}
	if (*n < (mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY)
		return (0);
	*n -= (mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY;
	if (dt->mth == 0 && (dt->mth = 11))
		--dt->year;
	else
		--dt->mth;
	return (1);
}

int ft_upd_day(t_date *dt, long int *n)
{
	if ((*n < DAY && *n >= 0) || (*n > -1 * DAY && *n < 0))
		return (0);
	if (*n > 0)
	{
		*n -= DAY;
		if (dt->day == mts[dt->mth] +
									(dt->mth == 1 && IS_LEAP_YEAR(dt->year))
				&& (dt->day = 1))
			if (dt->mth == 11 && !(dt->mth = 0))
				++dt->year;
			else
				++dt->mth;
		else
			++dt->day;
		return (1);
	}
	*n += DAY;
	if (dt->day == 1 && (dt->day = mts[dt->mth] +
									(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
		if (dt->mth == 0 && (dt->mth = 11))
			--dt->year;
		else
			--dt->mth;
	else
		--dt->day;
	return (1);
}

int ft_add_hour(t_date *dt, long int *n)
{
	if (*n < 3600)
		return (0);
	*n -= 3600;
	if (dt->hr == 23 && !(dt->hr = 0))
		if (dt->day == mts[dt->mth] + (dt->mth == 1 &&
									IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
			if (dt->mth == 11 && !(dt->mth = 0))
				++dt->year;
			else
				++dt->mth;
		else
			++dt->day;
	else
		++dt->hr;
	return (1);
}

int ft_sub_hour(t_date *dt, long int *n)
{
	if (*n > -3600)
		return (0);
	*n += 3600;
	if (dt->hr == 0 && (dt->hr = 23))
		if (dt->day == 1 && (dt->day = mts[dt->mth] +
				(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
			if (dt->mth == 0 && (dt->mth = 11))
				--dt->year;
			else
				--dt->mth;
		else
			--dt->day;
	else
		--dt->hr;
	return (1);
}

int ft_add_minute(t_date *dt, long int *n)
{
	if (*n < 60)
		return (0);
	*n -= 60;
	if (dt->min == 59 && !(dt->min = 0))
		if (dt->hr == 23 && !(dt->hr = 0))
			if (dt->day == mts[dt->mth] + (dt->mth == 1 &&
									IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
				if (dt->mth == 11 && !(dt->mth = 0))
					++dt->year;
				else
					++dt->mth;
			else
				++dt->day;
		else
			++dt->hr;
	else
		++dt->min;
	return (1);
}

int ft_sub_minute(t_date *dt, long int *n)
{
	if (*n > -60)
		return (0);
	*n += 60;
	if (dt->min == 00 && (dt->min = 59))
		if (dt->hr == 00 && (dt->hr = 23))
			if (dt->day == 1 && (dt->day = mts[dt->mth] +
					(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
				if (dt->mth == 0 && (dt->mth = 11))
					--dt->year;
				else
					--dt->mth;
			else
				--dt->day;
		else
			--dt->hr;
	else
		--dt->min;
	return (1);
}

int ft_add_second(t_date *dt, long int *n)
{
	if (*n < 1)
		return (0);
	*n -= 1;
	if (dt->sec == 59 && !(dt->sec = 0))
		if (dt->min == 59 && !(dt->min = 0))
			if (dt->hr == 23 && !(dt->hr = 0))
				if (dt->day == mts[dt->mth] + (dt->mth == 1 &&
						IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
					if (dt->mth == 11 && !(dt->mth = 0))
						++dt->year;
					else
						++dt->mth;
				else
					++dt->day;
			else
				++dt->hr;
		else
			++dt->min;
	else
		++dt->sec;
	return (1);
}

int ft_sub_second(t_date *dt, long int *n)
{
	if (*n > -1)
		return (0);
	*n += 1;
	if (dt->sec == 0 && (dt->sec = 59))
		if (dt->min == 0 && (dt->min = 59))
			if (dt->hr == 0 && (dt->hr = 23))
				if (dt->day == 1 && (dt->day = mts[dt->mth] +
									(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
					if (dt->mth == 0 && (dt->mth = 11))
						--dt->year;
					else
						--dt->mth;
				else
					--dt->day;
			else
				--dt->hr;
		else
			--dt->min;
	else
		--dt->sec;
	return (1);
}

int		ft_printf_date_compose(t_arg_data *ad, void* arg, t_string **str)
{
	t_date *dt;
	long int n;

	if (!(dt = (t_date*)malloc(sizeof(t_date))))
		return (0);
	n = *(long int*)arg;
	*dt = (t_date){1970, 0, 1, 0, 0, 0};
	while (ft_upd_year(dt, &n))
		;
	while (ft_upd_month(dt, &n))
		;
	while (ft_upd_day(dt, &n))
		;
	while (n >= 0 ? ft_add_hour(dt, &n) : ft_sub_hour(dt, &n))
		;
	while (n >= 0 ? ft_add_minute(dt, &n) : ft_sub_minute(dt, &n))
		;
	while (n >= 0 ? ft_add_second(dt, &n) : ft_sub_second(dt, &n))
		;
	ft_printf("%d.%d.%d %d:%d:%d\n", dt->year, dt->mth, dt->day, dt->hr, dt->min, dt->sec);
	return (1);
}