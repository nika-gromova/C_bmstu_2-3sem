/* Вычисление объема и температуры смеси
*/
#include<stdio.h>
int main(void)
{
    setbuf(stdout, NULL);

    float volume_1, volume_2;
    float temperature_1, temperature_2;
    float result_volume, result_temperature;

    printf("Input volume1 and temperature1: ");
    scanf("%f%f", &volume_1, &temperature_1);
	
    printf("Input volume2 and temperature2: ");
    scanf("%f%f", &volume_2, &temperature_2);
	
    result_volume = volume_1 + volume_2;
    result_temperature = (volume_1 * temperature_1 + volume_2 * temperature_2) / result_volume;
    printf("The result volume is %8.4f\n", result_volume);
    printf("The result temperature is %8.4f", result_temperature);
    return 0;
}
