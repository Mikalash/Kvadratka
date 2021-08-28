/**
@file
ðåøåíèå êâàäðàòíûõ óðàâíåíèé
*/

#include <stdio.h>
#include <math.h>
#include <cfloat>
#include <assert.h>
#include <windows.h>
//doxygen
const double ALMOST_0 = 0.00000001;


/**
Çàäà¸ò çíà÷åíèÿ, êîòîðûå áóäóò âîçâðàùàòü ôóíêöèè
ROOT_1 - 1 êîðåíü
ROOT_2 - 2 êîðíÿ
ROOT_INF - áåñêîíå÷íîñòü êîðíåé
ROOT_NO - íåò êîðíåé
*/
enum ROOTS {
    ROOT_1 = 1,
    ROOT_2 = 2,
    ROOT_INF = -1,
    ROOT_NO = -2,
};


/**
Ïðîâåðÿåò çíà÷åíèÿ a,b,c íà òî, ïðèíàäëåæàò ëè îíè NAN
*/
int input_check (double a, double b, double c);

/**
Ñðàâíèâàåò çíà÷åíèå value c 0
*/
int cmp_with_0 (double value);

/**
Ðåøàåò ëèíåéíóþ ôóíêèöþ âèäà bx+c=0; x1-íîìåð ÿ÷åéêè, â êîòîðóþ áóäåò ñîñëàí îòâåò.
*/
int linear_equation (double b, double c, double* x1);

/**
Ðåøàåò ëèíåéíóþ ôóíêèöþ âèäà ax^2+bx+c=0; x1,x2-íîìåðf ÿ÷ååê, â êîòîðûå áóäåò ñîñëàí îòâåò.
*/
int quadratic_equation (double a, double b, double c, double* x1, double* x2);

/**
Ñ÷èòàåò äèñêðèìèíàíò êâàäðàòíîãî óðàâíåíèÿ âèäà ax^2+bx+c=0
*/
double discriminant (double a, double b, double c);

/**
Î÷èùàåò áóôåð ââîäà
*/
int clear_input ()
{
    while (getchar () != '\n') ;
}

/**
Òåñèòèðîâàíèå
*/
int unit_test();

double round_6(double volume);

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
    scanf ("%lg %lg %lg", &a, &b, &c);

    if (input_check (a, b, c) == 0)
    {
        printf ("Wrong input");
        clear_input ();
        return -1;
    }

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

int input_check (double a, double b, double c)
{
    return (isfinite (a) || isfinite (b) || isfinite (c));
}

int cmp_with_0 (double value)
{
    return (fabs (value) < ALMOST_0);
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
    return b * b - 4 * a * c;
}

int unit_test()
{
    double tests[10][6] = {
        {1, 4, 2, -0.585786, -3.41421, 2},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {1, 12, 12, -1.10102, -10.899, 2},
        {2, 5, 3, -1, -1.5, 2},
        {12, 23, 11, -0.916667, -1, 2},
        {1, 4, 4, -2, 0, 1},
        {3, 65, 32, -0.504033, -21.1626, 2}
    };

    for (int i = 0; i < 10; i++)
    {
        double x1 = 0, x2 = 0;
        int n_ans = 0;

        n_ans = quadratic_equation (tests[i][0], tests[i][1], tests[i][2], &x1, &x2);

        x1 = round_6 (x1);
        x2 = round_6 (x2);

        //printf("%d %lg %lg %lg %lg %lg\n\t", n_ans, tests[i][5], x1, tests[i][3], x2, tests[i][4]);

        if (tests[i][5] == 2)
            if (n_ans == 2 && x1 == tests[i][3] && x2 == tests[i][4])
                printf ("Test number %d - OK\n", i+1);
            else
                printf ("Test number %d - ERROR\n", i+1);

        if (tests[i][5] == 1)
            if (n_ans == 1 && x1 == tests[i][3])
                printf ("Test number %d - OK\n", i+1);
            else
                printf ("Test number %d - ERROR\n", i+1);

        if (tests[i][5] == 0)
            if (n_ans != 1 && n_ans != 2)
                printf ("Test number %d - OK\n", i+1);
            else
                printf ("Test number %d - ERROR\n", i+1);
    }
}

double round_6(double volume)
{
    double multi_volume = (volume * 1000000);
    int int_multi_volume = multi_volume;

    multi_volume = int_multi_volume;
    multi_volume = multi_volume / 1000000;

    return (multi_volume);
}
