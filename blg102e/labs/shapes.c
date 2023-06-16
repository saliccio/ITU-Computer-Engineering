#include <stdio.h>
#include <math.h>

//#define M_PI 3.14159265358979323846

int main(int argc, char const *argv[])
{
    double len1=0, len2=0, area=0, circ=0;
    char shape = 'x';

    printf("Enter the shape type, e.g., rectangle, square, or circle\n");
    scanf(" %c", &shape);

    switch (shape)
    {
    case 'c':
        printf("Enter the radius of the circle\n");
        scanf("%lf", &len1);
        circ = 2 * M_PI * len1;
        area = M_PI * len1 * len1;
        printf("Circumference: %lf\n", circ);
        printf("Area: %lf\n", area);
        break;
    case 's':
        printf("Enter the side length of the square\n");
        scanf("%lf", &len1);
        circ = 4 * len1;
        area = len1 * len1;
        //printf("Perimeter: 100.000000\n");
        printf("Perimeter: %lf\n", circ);
        printf("Area: %lf\n", area);
        //printf("Area: 625.000000\n");
    case 'r':
        printf("Enter the side lengths of the rectangle\n");
        scanf("%lf %lf", &len1, &len2);
        circ = 2 * (len1 + len2);
        area = len1 * len2;
        printf("Perimeter: %lf\n", circ);
        printf("Area: %lf\n", area);
        break;
    default:
        break;
    }

    return 0;
}
