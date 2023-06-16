#include <stdio.h>

#define PI 3.14159265358979323846

double rect_area(double edge1, double edge2){
    return edge1 * edge2;
}

double rect_perimeter(double edge1, double edge2){
    return (edge1 + edge2) * 2;
}

double square_area(double edge){
    return edge * edge;
}

double square_perimeter(double edge){
    return edge * 4;
}

double circle_area(double radius){
    return radius * radius * PI;
}


double circle_perimeter(double radius){
    return 2 * radius * PI;
}

int main(){
    printf("Enter the shape type, e.g., rectangle, square, or circle\n");
    char type;
    scanf("%c", &type);
    switch(type){
        case 'c':
            printf("Enter the radius of the circle\n");
            double radius;
            scanf("%lf", &radius);
            printf("Circumference: %lf\n", circle_perimeter(radius));
            printf("Area: %lf\n", circle_area(radius));
            break;
        case 's':
            printf("Enter the side length of the square\n");
            double side;
            scanf("%lf", &side);
            printf("Perimeter: %lf\n", square_perimeter(side));
            printf("Area: %lf\n", square_area(side));
            break;
        case 'r':
            printf("Enter the side lengths of the rectangle\n");
            double side1, side2;
            scanf("%lf %lf", &side1, &side2);
            printf("Perimeter: %lf\n", rect_perimeter(side1, side2));
            printf("Area: %lf\n", rect_area(side1, side2));
            break;
    }
    return 0;
}