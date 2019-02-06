// Возведение целочисленного числа в степень >= 0
// a - base - основание
// n - power - степень
// res - result - результат вычисления

#include<stdio.h>

#define OK (0)
#define TYPE_ERROR (1)
#define RANGE_ERROR (2)

// Функция возведения в степень
int stepen(int a, int n)
{
    int res;

    res = a;

    while (n > 1)
    {
        res *= a;
        n--;
    }

    return res;
}

// Защита
int quick_pow(int a, int n)
{
	int res = 1;
	int tmp = a;
	
	if (n == 0)
		return 1;
	
	while (n >= 1)
	{
		if (n % 2 == 0)
		{
			tmp *= tmp;
			n /= 2;
		}
		else 
		{
			tmp *= res;
			n--;
			res = tmp;
		}
	}
	res = tmp;
	return res;	
}

// Основная функция
int main(void)
{
    int base, power;
    int result;
    int rc;

    //int scount; // Переменные для
    //char en;    // проверки на ввод

    printf("Please, enter an integer number and a natural integer power of it: ");

    if (scanf("%d%d", &base, &power) == 2)
    {
        if (power > 0)
        {
            result = stepen(base, power);
            rc = OK;
        }
        else
            rc = RANGE_ERROR;
    }
    else
        rc = TYPE_ERROR;

    // проверка на ввод
    /*while(((scount = scanf("%d%d%c", &base, &power, &en)) != 3 && scount != EOF) ||
														en != '\n'|| (power && power < 0))
    {
        if ((power < 0) && (en == '\n') && (scount == 3))
        {
            printf("Error! Please enter a positive power: ");
        }

        else
        {
            printf("Error! Please, enter again: ");
            do
            {
                scount = scanf("%c", &en);
            }
            while(scount != EOF && en != '\n');
        }
    }
    result = stepen(base, power);*/

    // Вывод результата
    if (rc == OK)
        printf("%d\n", result);

    // Защита
    //result = quick_pow(base, power);
    //printf("%d^%d = %d", base, power, result);

    return rc;
}
