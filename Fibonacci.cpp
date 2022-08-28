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
    cout << " " << fib_memoized(60) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout <<"Duration with memoized: " << duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    cout << " " << fibonacci_matrix(60) << endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "Duration vector matrix: " << duration.count() << endl;
}
