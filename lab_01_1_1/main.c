//Найти площадь трапеции по заданным основаниям и углом при большем основании.
#include <stdio.h>
#include <math.h>
#define PI (3.141592653589793)
int main(void)
{
    setbuf(stdout, NULL);
    float a, b;
    float h, sqare;
    float alpha;
    printf("Введите основания трапеции a и b:");
    scanf("%f%f", &a, &b);
    printf("\nВведите угол при большем основании (в градусах):");
    scanf("%f", &alpha);
    alpha = (alpha * PI) / 180; //Перевод градусов в радианы
    h = (fabs((b - a)) / 2) * tan(alpha); //Нахождение высоты
    sqare = ((a + b) / 2) * h; //Нахождение площади
    printf("Площадь трапеции = %.4f", sqare);
    return 0;
}
