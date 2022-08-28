// Fibonacci.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

using namespace std;
int64_t term[100];
int64_t Fibonacci(int number) {
    if ((number == 1) || (number == 0)) {
        return number;
    }
    else {
        return Fibonacci(number - 1) + Fibonacci(number - 2);
    }
}

int64_t fib_memoized(int number)
{
    if ((number == 1) || (number == 0)) {
        return number;
    }

    if (term[number] != 0)
        return term[number];

    else {
        term[number] = fib_memoized(number - 1) + fib_memoized(number - 2);

        return term[number];
    }
}

void multiply(int64_t F[2][2], int64_t M[2][2]) {
    int64_t a = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int64_t b = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int64_t c = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int64_t d = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    F[0][0] = a;
    F[0][1] = b;
    F[1][0] = c;
    F[1][1] = d;
}
void power(int64_t F[2][2], int n) {
    if (n == 0 || n == 1)
        return;
    int64_t M[2][2] = { {1,1},{1,0} };

    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0)
        multiply(F, M);
}

int64_t fibonacci_matrix(int n) {
    int64_t F[2][2] = { {1,1},{1,0} };
    if (n == 0)
        return 0;
    power(F, n - 1);
    return F[0][0];
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    cout << " " << fib_memoized(7) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout <<"Duration with memoized: " << duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    cout << " " << fibonacci_matrix(7) << endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "Duration vector matrix: " << duration.count() << endl;
}   

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
