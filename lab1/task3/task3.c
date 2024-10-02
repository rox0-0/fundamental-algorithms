#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 

typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT_ERROR,
    ANY
} status; 

status solution(double eps, double coeffs[], double *x1, double *x2)
{
    double a = coeffs[0], b = coeffs[1], c = coeffs[2];

    if (fabs(a) < eps)
    {
        if(fabs(b)<eps && fabs(c)< eps) return ANY;
        else if (fabs(b)<eps && fabs(c)>= eps ) return WRONG_INPUT_ERROR;
        else
        {
            *x1 = -c/b;
            *x2 = -c/b;
            return OK;
        }
    }
    else
    {
        double D = b*b - 4*a*c;
        if (D < eps) return WRONG_INPUT_ERROR;
        else
        {
            *x1 = (-b + sqrt(D))/(2*a);
            *x2 = (-b - sqrt(D))/(2*a);
            return OK;
        }
    }
}

void print_solution(double eps, double coeffs[])
{
    double x1 = 0, x2 = 0;
    status result = solution(eps, coeffs, &x1, &x2);

    if (result == WRONG_INPUT_ERROR) {
        printf("Решений нет\n");
    } else if (result == ANY) {
        printf("Решением является любое вещественное число\n");
    } else if (result == OK) {
        if (fabs(x1 - x2) < eps)
            printf("x = %lf\n", x1);
        else
            printf("x1 = %lf, x2 = %lf\n", x1, x2);
    }
}

void reverse(double arr[], int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        double temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2 || !(argv[1][2] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-')))
    {
        printf("Неправильный ввод\n");
        return WRONG_INPUT_ERROR;
    }

    double eps, coeffs[4];
    long int first_number, second_number;

    switch (argv[1][1])
    {
        case 'h':
            if (argc != 6 || (sscanf(argv[2], "%lf", &eps) != 1) ||
                (sscanf(argv[3], "%lf", &coeffs[0]) != 1) ||
                (sscanf(argv[4], "%lf", &coeffs[1]) != 1) ||
                (sscanf(argv[5], "%lf", &coeffs[2]) != 1))
            {
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }

            if (eps <= 0) {
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }
            double current_coeffs[3] = {coeffs[0], coeffs[1], coeffs[2]};
            for (int j = 0; j < 6; j++) {

                printf("Перестановка: a=%lf, b=%lf, c=%lf\n", current_coeffs[0], current_coeffs[1], current_coeffs[2]);
                print_solution(eps, current_coeffs);

                double temp = current_coeffs[0];
                current_coeffs[0] = current_coeffs[1];
                current_coeffs[1] = current_coeffs[2];
                current_coeffs[2] = temp;
                if (j==2) reverse(current_coeffs, 3);

            }







            break;

        case 'm':
            if (argc != 4 || (sscanf(argv[2], "%ld", &first_number) != 1) ||
                (sscanf(argv[3], "%ld", &second_number) != 1))
            {
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }
            if (first_number == 0 || second_number == 0)
            {
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }
            if (first_number % second_number == 0 && first_number >= second_number)
            {
                printf("Число a=%ld кратно b=%ld\n", first_number, second_number);
            }
            else
            {
                printf("Введенные числа не кратны друг другу\n");
            }
            break;

        case 't':
            if (argc != 6 || (sscanf(argv[2], "%lf", &eps) != 1) ||
                (sscanf(argv[3], "%lf", &coeffs[0]) != 1) ||
                (sscanf(argv[4], "%lf", &coeffs[1]) != 1) ||
                (sscanf(argv[5], "%lf", &coeffs[2]) != 1))
            {
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }

            if (eps <= 0) {
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }

            if (fabs(coeffs[0]*coeffs[0] + coeffs[1]*coeffs[1] - coeffs[2]*coeffs[2]) < eps)
                printf("Существует прямоугольный треугольник с катетами a=%lf, b=%lf, и гипотенузой c=%lf\n", coeffs[0], coeffs[1], coeffs[2]);
            else if (fabs(coeffs[0]*coeffs[0] + coeffs[2]*coeffs[2] - coeffs[1]*coeffs[1]) < eps)
                printf("Существует прямоугольный треугольник с катетами a=%lf, b=%lf, и гипотенузой c=%lf\n", coeffs[0], coeffs[2], coeffs[1]);
            else if (fabs(coeffs[1]*coeffs[1] + coeffs[2]*coeffs[2] - coeffs[0]*coeffs[0]) < eps)
                printf("Существует прямоугольный треугольник с катетами a=%lf, b=%lf, и гипотенузой c=%lf\n", coeffs[1], coeffs[2], coeffs[0]);
            else
                printf("Введенные числа не могут являться длинами сторон прямоугольного треугольника\n");
            break;

        default:
            printf("Неправильный флаг\n");
            return WRONG_INPUT_ERROR;
    }

    return OK;
}
