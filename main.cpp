/**
@file
решение квадратных уравнений
*/

#include <stdio.h>
#include <math.h>
//#include <cfloat>
#include <assert.h>
#include <windows.h>
//doxygen
const double ALMOST_0 = 0.0001;


/**
\brief Задаёт значения, которые будут возвращать функции
\param ROOT_1 1 корень
\param ROOT_2 2 корня
\param ROOT_INF бесконечность корней
\param ROOT_NO нет корней
*/
enum ROOTS {
    ROOT_1 = 1,
    ROOT_2 = 2,
    ROOT_INF = -1,
    ROOT_NO = -2,
};


/**
\brief Сравнивает значение c 0
\param Значение, сравниваемое с 0
*/
int cmp_with_0 (double value);

/**
\brief Считывает значения с их проверкой
\param a первое значение
\param b первое значение
\param c первое значение
*/
int clever_input(double* a, double* b, double* c);

/**
\brief Решает линейную функицю вида bx+c=0
\param значение b
\param значение c
\param *x1 номер ячейки, в которую будет сослан ответ
*/
int linear_equation (double b, double c, double* x1);

/**
\brief Решает линейную функицю вида ax^2+bx+c=0
\param значение a
\param значение b
\param значение c
\param *x1 значение номер ячейки, в которую будет сослан ответ
\param *x2 значение номер ячейки, в которую будет сослан ответ.
*/
int quadratic_equation (double a, double b, double c, double* x1, double* x2);

/**
\brief Считает дискриминант квадратного уравнения вида ax^2+bx+c=0
\param значение a
\param значение b
\param значение c
*/
double discriminant (double a, double b, double c);

/**
\brief Очищает буфер ввода
*/
int clear_input ()
{
    while (getchar () != '\n') ;
}

/**
\brief Теситирование решения квадратного уравнения
*/
int unit_test();

int main ()
{
    unit_test();

    double a = NAN;
    double b = NAN;
    double c = NAN;

    double x1 = NAN;
    double x2 = NAN;

    printf ("Bozhik Nikolai presents:\nQuadratic equation solver (2021)\n");
    printf ("Give a b c to solve ax^2+bx+c=0\n");

    if (clever_input(&a, &b, &c) != 3)
        return -1;

    int value_quadratic = quadratic_equation (a, b, c, &x1, &x2);

    switch (value_quadratic)
    {
        case ROOT_1:
            printf ("x=%lg", x1);
            break;
        case ROOT_2:
            printf ("x1=%lg x2=%lg", x1, x2);
            break;
        case ROOT_NO:
            printf ("No solution");
            break;
        case ROOT_INF:
            printf ("Infinite number of solutions");
            break;
    }

    return 0;
}

int cmp_with_0 (double value)
{
    return (fabs (value) < ALMOST_0);
}

int clever_input(double* a, double* b, double* c)
{
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);
    assert (a != b && a != c && b != c);

    double abc[3];
    for (int i = 0; i < 3; i++)
    {
        double in = NAN;
        scanf ("%lg", &in);
        if (!isfinite (in))
        {
            printf ("\nWrong input\n");
            clear_input ();
            return -1;
        }
        abc[i] = in;
    }

    *a = abc[0];
    *b = abc[1];
    *c = abc[2];
    return 3;
}

int linear_equation (double b, double c, double* x1)
{
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != NULL);

    if (cmp_with_0 (b))
    {
        if (cmp_with_0 (c))
            return ROOT_INF;
        else
            return ROOT_NO;
    }

    *x1 = (0 - b) / c;
    return ROOT_1;
}

int quadratic_equation(double a, double b, double c, double* x1, double* x2)
{
    assert (x1 != x2);

    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1 != NULL);
    assert (x2 != NULL);

    double discr = discriminant (a, b, c);
    //printf("%lg\n", discr);

    if (cmp_with_0 (a))
        return linear_equation (b, c, x1);

    if (cmp_with_0 (discr))
    {
        *x1 = (0 - b) / (2 * a);
        return ROOT_1;
    }

    if (discr < 0)
        return ROOT_NO;

    *x1 = (-b + sqrt (discr)) / (2 * a);
    *x2 = (-b - sqrt (discr)) / (2 * a);
    return ROOT_2;
}

double discriminant (double a, double b, double c)
{
    return (b * b - 4 * a * c);
}

int unit_test()
{
    double tests[10][6] = {
        {1,  4,  2,  -0.585786, -3.41421,  2}, // 1
        {0,  0,  0,  0,                0, -1}, // 2
        {0,  0,  1,  0,                0, -2}, // 3
        {1,  1,  1,  0,                0, -2}, // 4
        {1,  1,  1,  0,                1, -2}, // 5 error
        {1,  12, 12, -1.10102,   -10.899,  2}, // 6
        {2,  5,  3,  -1,            -1.5,  2}, // 7
        {12, 23, 11, -0.916667,       -1,  2}, // 8
        {0,  5,  3,  -1.66667,         0,  1}, // 9
        {3,  65, 32, -0.504033, -21.1626,  2}  // 10
    };//a,b,c,x1,x2,n_ans

    for (int i = 0; i < 10; i++)
    {
        double x1 = 0, x2 = 0;

        int n_ans = quadratic_equation (tests[i][0], tests[i][1], tests[i][2], &x1, &x2);

        //printf("got %d roots (ref. %lg), x1 = %lg (ref. %lg), x2 = %lg (ref. %lg)\n\t", n_ans, tests[i][5], x1, tests[i][3], x2, tests[i][4]);

        if (tests[i][5] == n_ans &&
            cmp_with_0 (x1 - tests[i][3]) &&
            cmp_with_0 (x2 - tests[i][4]))

            printf ("Test number %3d - OK\n", i+1);
        else
        {
            printf ("Test number %3d - ERROR\n", i+1);
            printf ("In: a=%lg b=%lg c=%lg\n", tests[i][0], tests[i][1], tests[i][2]);
            printf ("Expected out: x1=%lg x2=%lg n_roots=%d\n", tests[i][3], tests[i][4], tests[i][5]);
            printf ("Real     out: x1=%lg x2=%lg n_roots=%d\n\n", x1, x2, n_ans);
        }
    }
}
