#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf_compose.h"


/*
 *
 * int a = 11;
	int e = 22;

	printf("%*2$1$d\n", a, e);
 *                     11
 */

// printf("% *3$.*2$*4$.*1$d\n", 7, 10, 20, 30);

// printf("%hhzhhhh hhd\n", (long)9000000000000086677);

// printf("|%10*#02$d|\n", 100, 6);


// TODO printf("\n\n///%*** 1$d", (long)5, (long)12, (int)20, (long)45);

// TODO printf("\n\n///%***1 $d", (long)5, (long)12, (int)20, (long)45);

// TODO SEGFAULT!!! ft_printf("%d %d %1$f", 999999222, 999999222/*, 666.5l*/);

/* TODO FIX
 * ft_printf("|%020.*1$d|\n", -10, 101);
	printf("|%020.*1$d|\n", -10, 101);
 */

/* TODO FIX
 * ft_printf("|%020.*d|\n", 10, 101);
	printf("|%020.*d|\n", 10, 101);
 */

#include "ft_printf.h"

#include <wchar.h>

#include <locale.h>



/*void test1(char *s, ...)
{
	va_list vl;
	va_start(vl, s);
	for (int e = 0; e < 10; e++)
	{
		ft_print_va_struct(vl);
		printf("\n");
		char c = va_arg(vl, char);
	}
	printf("\n");
	ft_print_va_struct(vl);
}*/

typedef union s_1
{
	double	d;
	unsigned long 	l;
}			t_1;

#include <math.h>
#include <limits.h>

#include <locale.h>
#include <langinfo.h>


int main()
{
	//char ref[] = "gggg %hhd %hd %hhhd %hld %d %c %zu ";
	/**char ref[] = "%lc %llc %lllc %c %%g gg %% %Lf %S %o %w %hhh+zhhhd";
	char *tst = (char*)malloc(sizeof(char) * ft_strlen(ref) + 1);
	for (int e = 0; e < ft_strlen(ref) + 1; e++)
	{
		tst[e] = ref[e];
	}
	t_string *sizes = ft_get_va_lst_sizes(tst);
	for (int e = 0; e < sizes->len; e++)
	{
		printf("%d ", sizes->data[e]);
	}
	printf("\n%hhhhhh+hzhhd", 2000000000000);
	return (0);*/
																				 //11642099651136453756
	//ft_printf("", 1, 2, 3, 4, (__int128_t)5555555555555555555 * (__int128_t)5000, 6, 7, 8, (float)77.7, (float)77.5, (float)55.5, (float)77.5, (float)773.5, \
			(float)77.5, (float)737.5, (float)773.5, (float)77.5, \
			(float)77.15, (float)771.5, (float)33.4, /*(float)666.6,*/ (__int128_t)10999999999999999991 * (__int128_t)5000, (float)99.35, \
			(float)773.5, (float)773.5, (float)737.5, (float)77.5, \
			(float)77.51, (float)77.35, (float)773.5, (float)737.5, (float)77.53, (float)77.51, (float)77.532, (float)77.54, (float)77.55); \
	//ft_printf("tttt|%3$d| %2$d %1$d %10.*2$0% %*000$d\n", 10, 20, 30, 1, 1, 1 ,1 ,1 ,1 , 1, 1, 1);
	//printf("tttt|%3$d| %2$d %1$d |%10.*2$0%| |%*000$d|\n", 10, 20, 30, 1, 1, 1 ,1 ,1 ,1 , 1, 1, 1);
	//ft_printf("ggg");

	//printf("|%20.0+f|", -23.76);

	char flag = '+';
	char sign;
	long n = 1222;
	unsigned char cc = 200;
	unsigned long ul = 18446744073709551615;
	long lm = -9223372036854775806;
	int prec = 1;



	//char *rr = (char *) _NL_CURRENT (LC_NUMERIC, THOUSANDS_SEP)

	//((*_nl_current_4)->values[_NL_ITEM_INDEX (item)].string)

	//n = ~n;

	//sign = flag;
	//sign = (n < 0) ? (char)'-' : flag;

	// todo not PLUS in case of unsigned convertions

	//printf("|%s|\n", ft_printf_itoa_pro(ft_printf_int_caster(n, DEFAULT, 1), 8, prec, flag));
	//printf("|%s|\n", ft_printf_itoa_pro(ft_printf_int_caster(0, DEFAULT, 0), 10, prec, flag));
	//printf("|%#.*x|\n", prec, n);
	//printf("|%.*p|\n", prec, n);

	//printf("<|%+ -5d|>\n", 0);

	//printf("|%20.0020f|\n", 22.2);

	//printf("<");
	//ft_printf("%d %d", 10001, 200002);
	//ft_printf("%p", &flag);

	/*ft_printf("|% 020d|\n", -13);
	printf("|%d|\n", -13);
	printf("|%s|\n", ft_printf_itoa_pro(ft_printf_int_caster(-13, DEFAULT, 0), 10, 0, 0));
	printf("|%llu|\n", ft_printf_int_caster(-13, DEFAULT, 0));*/

	/*char *res = ft_strnew(100);
*/
	double k = 200.545646666666666666;
	double fin = k;
	double dec = 1.0;
	double k_c = k;
	int log = 0;
	while (k_c > 1.0)
	{
		dec *= 10.0;
		log++;
		k_c /= 10.0;
	}
	while (dec > 1.0)
	{
		dec /= 10.0;
		int idx = k / dec;
		printf("%c", idx + '0');
		k -= dec * idx;

	}
	printf("\n");
	printf("log = %d\n", log);
	k *= pow(10, 6);
	printf("%f\n", fin);
	printf("%f\n", k);
	//printf("%f\n", k);
	//printf("%f\n", dec);
	//printf("%f\n", pow(10, 38));
/*


	int in = (int)k;
	double k2 = k - 22222233326662453453453453453453.0;
	printf("<<< %f %f\n",(double)in, k2);
	for (int e = 0; e < 15; e++)
	{
		printf("%d >> %f\n", e, k);
		k *= 10;
	}
	//printf("%d\n", (int)((double)29.545 / 1) % 10);

	printf("<<<%lld\n", (long int)(22.4 * pow(10, 10)));

	double nan = 0.0 / 0.0;


	printf("%f  %d\n", nan, nan != nan);

	t_1 dd;
	dd.d = 9999999999999999999999999999999999999999999999999999999999999999999999999999.0;
	ft_print_bits(dd.l);

	//printf("%3$Lf %2$Lf %1$Lf\n", (long double)10.1, (long double)11.2, (long double)666.45);*/

	//setlocale(LC_NUMERIC, "da_DK");

	//112402762000
	//10000000000
	int x;

	///ft_printf("|%020.*d|\n", 10, 101);
	///printf("|%020.*d|\n", 10, 101);

	//printf("|%'.0lB|\n", 1000);

	ft_printf("|%020.*1$d|\n", -10, 101);
	printf("|%020.*1$d|\n", -10, 101);

	ft_printf("%010.20d\n", 10, 20, 101);
	printf("%010.20d\n", 10, 20, 101);


	printf("%e\n", 13252365.341235223245);





	//printf("%zu\n", sizeof(long double));

	///setlocale(LC_NUMERIC, "da_DK");
	///printf("%#'lX\n", (long)1000000000000000000);



	/*printf("%u\n", (unsigned)(-2147483648 * (-1)));
	ft_print_bits((long)-2147483648);
	printf("\n");*/

	return(0);

}


