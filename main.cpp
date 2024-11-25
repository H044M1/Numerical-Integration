#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <iomanip>
#include "integration.h"

#define exact_I -0.274653072167027422848811309230631426161872639455687362933673583

using namespace std;

// Функция для интегрирования
double function_to_integrate(double x) {
    return 1 / (x * x - 4);
}

void runIntegration(const function<double(double)>& f, double a, double b) {
    vector<double> h_values = {0.1, 0.05, 0.025};
    cout << fixed << setprecision(10);

    // Создаем интегратор
    NumericalIntegrator integrator(a, b, h_values[0]);

    // --- Метод парабол ---
    cout << "\nParabola Results:\n";
    vector<double> parabola_results;

    for (double h : h_values) {
        integrator.set_h(h);
        double result = integrator.parabola(f);

        parabola_results.push_back(result);
        cout << "h = " << h << " : " << result;
        if (exact_I != 0.0) { 
            double error = fabs(result - exact_I);
            cout << " Error: " << error;
        }
        cout << endl;
    }

    // --- Оценка ошибки методом Рунге и уточнение по Ричардсону ---
    cout << "\nParabola Error Analysis (Runge and Richardson):\n";
    cout << setw(15) << "h"
         << setw(15) << "Runge"
         << setw(15) << "Richardson"
         << setw(15) << "Error_Richardson" << endl;

    for (size_t i = 1; i < parabola_results.size(); ++i) {
        double runge = (parabola_results[i - 1] - parabola_results[i]) / (pow(2, 4) - 1); // Порядок метода = 4
        double richardson = parabola_results[i] + runge;
        double err_richardson = (exact_I != 0.0) ? fabs(exact_I - richardson) : 0.0;

        cout << setw(15) << h_values[i]
             << setw(15) << runge
             << setw(15) << richardson
             << setw(15) << err_richardson << endl;
    }

    // --- Метод Гаусса-2 ---
    cout << "\nGauss-2 Results:\n";
    vector<double> gauss2_results;

    for (double h : h_values) {
        integrator.set_h(h);
        double result = integrator.gauss2(f);
        gauss2_results.push_back(result);
        cout << "h = " << h << " : " << result;
        if (exact_I != 0.0) {
            double error = fabs(result - exact_I);
            cout << " Error: " << error;
        }
        cout << endl;
    }

    //Оценка ошибки методом Рунге и уточнение по Ричардсону для Гаусса-2
    cout << "\nGauss-2 Error Analysis (Runge and Richardson):\n";
    cout << setw(15) << "h"
         << setw(15) << "Runge"
         << setw(15) << "Richardson"
         << setw(15) << "Error_Richardson" << endl;

    for (size_t i = 1; i < gauss2_results.size(); ++i) {
        double runge = (gauss2_results[i - 1] - gauss2_results[i]) / (pow(2, 4) - 1); // Порядок метода = 4
        double richardson = gauss2_results[i] + runge;
        double err_richardson = (exact_I != 0.0) ? fabs(exact_I - richardson) : 0.0;

        cout << setw(15) << h_values[i]
             << setw(15) << runge
             << setw(15) << richardson
             << setw(15) << err_richardson << endl;
    }
}

int main() {
    double a = 0.0, b = 1.0; // Пример области интегрирования
    runIntegration(function_to_integrate, a, b);
    return 0;
}