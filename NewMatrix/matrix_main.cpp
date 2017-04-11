#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{   

    system("clear");

    Matrix<int> matrix_a("A", 3, 3);
    Matrix<int> matrix_b("B", 2, 3);
    Matrix<int> matrix_c("C", 3, 1);

    matrix_a.SetElements();
    matrix_b.SetElements();

    matrix_a.Show();
    matrix_b.Show();

    matrix_c = matrix_a + matrix_b;

    matrix_c.Show();

    matrix_a = matrix_b = matrix_c + matrix_c + matrix_a;

    matrix_a.Show();
    matrix_b.Show();
    matrix_c.Show();

    return 0;
}
