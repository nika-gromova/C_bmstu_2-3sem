// Вычисление приближенного и точного значения функции

#include<stdio.h>
#include<math.h>

#define OK (0)
#define INP_ERROR (1)
#define RANGE_ERROR (2)

// Функция вычисления экспоненты через несходящийся ряд
float calc_exp(float eps, float x)
{
    int n = 1;
    float sum = 1, current_x = x;
    while (fabs(current_x) > eps)
    {
        sum += fabs(current_x);
        current_x *= x / (n + 1);
        n++;
    }
	if (x < 0)
		return 1 / sum;
    return sum;
}

// Основная функция
int main(void)
{
    float eps;
    float f_func, s_func;
    float x;

    float abs_err, nom_err; // Абсолютная и относительная погрешности

    int rc = OK;
    //char ch;

    printf("Input x and eps: ");
    if (scanf("%f%f", &x, &eps) == 2)
    {
        if ((eps >= 0) && (eps <= 1))
        {
            s_func = calc_exp(eps, x);
            f_func = exp(x);

            

            abs_err = fabs(f_func - s_func);
            nom_err = abs_err / f_func;
			printf("%8.6f\n", s_func);
            printf("%8.6f\n", f_func);
            printf("%8.6f\n", abs_err);
            printf("%8.6f\n", nom_err);
        }
        else
            rc = RANGE_ERROR;
    }
    else
        rc = INP_ERROR;

    /*// Проверка на ввод x
    while(((rc = scanf("%f%c", &x, &ch) != 2) && rc != EOF) || ch != '\n')
    {
        printf("Input error, try again: ");
        do
        {
            rc = scanf("%c", &ch);
        }
        while(rc != EOF && ch != '\n');
    }
    // Проверка на ввод eps
    while(((rc = scanf("%f%c", &eps, &ch) != 2) && rc != EOF) || ch != '\n' ||\
          (eps <= 0 || eps > 1))
    {

        if ((eps <= 0 || eps > 1) && ch == '\n' && (rc == 2 || rc == 0))
        {
            printf("Eps out of possible range, input again: ");
        }
        else
        {
            printf("Input error, try again: ");
            do
            {
                rc = scanf("%c", &ch);
            }
            while(rc != EOF && ch != '\n');
        }

    }*/

    return rc;
}
