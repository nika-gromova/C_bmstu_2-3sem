/* Вычисляет площадь прямоугольника.
*/

#include<stdio.h>
# define PI 3.14

float sq_rectangle(float w, float h)
{
    float square;
    square = w*h;
    return square;
}

float sq_circle(float radius){
    float square;
    square = radius*radius*PI;
    return square;
}

int main(void)
{
    //int a, b;
    //int r;
    float a, b, r;
    float sr, sc;
    float s;

    printf("Input a and b: ");
    scanf("%f%f", &a, &b);

    sr = sq_rectangle(a,b);

    printf("Square of rectangle is %8.3f\n", sr);

    printf("Input r: ");
    scanf("%f", &r);

    sc = sq_circle(r);

    printf("Square of circle is %8.3f\n", sc);

    s = sc+sr;

    printf("Square of both figures is %8.4f\n", s);


    return 0;
}
