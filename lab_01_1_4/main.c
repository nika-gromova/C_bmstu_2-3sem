/* Определение номера подъезда и этажа по номеру квартиры
*/

#include<stdio.h>
#define MAX_FLATS_IN_ENTRANCE (36)
#define MAX_FLATS_ON_FLOOR (4)

int main(void)
{
    setbuf(stdout, NULL);
    int num_flat;
    int num_floor, num_ent;
    int temp;

    printf("Input number of the flat: ");
    scanf("%d", &num_flat);

	num_ent = (num_flat + MAX_FLATS_IN_ENTRANCE - 1) / MAX_FLATS_IN_ENTRANCE;
    temp = num_flat - (num_ent - 1) * MAX_FLATS_IN_ENTRANCE;
    num_floor = (temp + MAX_FLATS_ON_FLOOR - 1) / MAX_FLATS_ON_FLOOR;

	printf("Entrance number: %d\n", num_ent);
    printf("Floor number: %d\n", num_floor);
    

    return 0;
}
