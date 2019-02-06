// Определение типа треугольника(остроугольный, тупоугольный, прямоугольный)

#include<stdio.h>
#include<math.h>

#define OK (0)
#define IO_ERROR (-1)
#define NOT_A_TRIANGLE (-2)

// Функция, вычисляющая скалярное произведение векторов
float sc_multiplication(float x1, float y1, float x2, float y2)
{
    return (x1 * x2 + y1 * y2);
}


// Фунукция, вычисляющая косое (псевдо-скалярное) произведение векторов
float k_multiplication(float x1, float y1, float x2, float y2)
{
    return (x1 * y2 - x2 * y1);
}

/*void check_input(float *x, float *y)
{
    float x1, y1;
    char ch;
    int rc;

    while (((rc = scanf("%f%f%c", &x1, &y1, &ch)) != 3 && rc != EOF) || ch != '\n')
    {
        printf("Incorrect input, try again: ");
        do
        {
            rc = scanf("%c", &ch);
        }
        while(rc != EOF && ch != '\n');
    }
    *x = x1;
    *y = y1;
}*/


// Функция, определяющая тип треугольника
int type_tiangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	// Координаты векторов
	float vector_a_x, vector_a_y;
    float vector_b_x, vector_b_y;
    float vector_c_x, vector_c_y;
	
	// Скалярное произведение векторов
    float a_b_multipl;
    float b_c_multipl;
    float a_c_multipl;
    float total_multipl;

    vector_a_x = x2 - x1;
    vector_a_y = y2 - y1;
    vector_b_x = x3 - x2;
    vector_b_y = y3 - y2;
    vector_c_x = x3 - x1;
    vector_c_y = y3 - y1;	
	
    if ((k_multiplication(vector_a_x, vector_a_y, vector_b_x, vector_b_y)) == 0)
    {
        return NOT_A_TRIANGLE;
    }
	
    a_c_multipl = sc_multiplication(vector_c_x, vector_c_y, vector_a_x, vector_a_y);
    a_b_multipl = sc_multiplication(-vector_a_x, -vector_a_y, vector_b_x, vector_b_y);
    b_c_multipl = sc_multiplication(-vector_b_x, -vector_b_y, -vector_c_x, -vector_c_y);

    total_multipl = a_b_multipl * b_c_multipl * a_c_multipl;


    if (total_multipl == 0)
		return 1;
    else if (total_multipl > 0)
        return 0;
    else
        return 2;
}

// Основная функция
int main(void)
{
    float x1, x2, x3; // Входные координаты
    float y1, y2, y3; // точек вершин треугольника
    int rc = OK;
    int result;

    /*printf("Please, enter the coordinates of the first point: ");
    check_input(&x1, &y1);
    printf("\nPlease, enter the coordinates of the second point: ");
    check_input(&x2, &y2);
    printf("\nPlease, enter the coordinates of the third point: ");
    check_input(&x3, &y3);*/

    printf("Enter the coordinates of the points:\n");
    if (scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3) == 6)
    {
        result = type_tiangle(x1, y1, x2, y2, x3, y3);
        if (result != NOT_A_TRIANGLE)
        {
            printf("%d", result);
        }
        else
            rc = NOT_A_TRIANGLE;
    }
    else
        rc = IO_ERROR;

    return rc;
}
