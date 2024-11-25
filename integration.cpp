#include "integration.h"


double NumericalIntegrator::parabola(const std::function<double(double)>& f) {
    // Проверяем, что число точек в сетке корректно для метода Симпсона
    if (grid.size() < 2) {
        throw std::invalid_argument("Grid size must be at least 2");
    }

    // Для метода Симпсона количество отрезков должно быть четным
    if ((grid.size() - 1) % 2 != 0) {
        throw std::invalid_argument("The number of intervals must be even");
    }

    double integral = 0.0;

    // Применяем формулу Симпсона на каждом отрезке
    for (size_t i = 0; i < grid.size() - 1; i += 2) {
        double x0 = grid[i];
        double x1 = grid[i + 1];
        double x2 = grid[i + 2];

        double h_segment = (x2 - x0) / 2.0;

        integral += (h_segment / 3.0) * (f(x0) + 4.0 * f(x1) + f(x2));
    }

    return integral;
}

double NumericalIntegrator::gauss2(const std::function<double(double)>& f) {
    const double gauss_points[] = {-1.0 / sqrt(3.0), 1.0 / sqrt(3.0)};
    const double gauss_weights[] = {1.0, 1.0};

    double result = 0.0;

    // Проходим по всем отрезкам сетки
    for (size_t i = 0; i < grid.size() - 1; ++i) {
        double x0 = grid[i];
        double x1 = grid[i + 1];
        double mid = (x0 + x1) / 2.0;            // Центр отрезка
        double half_length = (x1 - x0) / 2.0;   // Половина длины отрезка

        // Применяем формулу Гаусса
        for (int j = 0; j < 2; ++j) {
            double xi = mid + half_length * gauss_points[j];
            result += gauss_weights[j] * f(xi) * half_length;
        }
    }

    return result;
}

void NumericalIntegrator::buildGrid() {
    grid.clear();
    int n = static_cast<int>((b - a) / h);
    if (n % 2 != 0) {
        throw std::invalid_argument("buildGrid: The number of intervals must be even.");
    }
    for (int i = 0; i <= n; ++i) {
        grid.push_back(a + i * h);
    }
}


double NumericalIntegrator::get_h() {
    return h;
}

void NumericalIntegrator::set_h(double new_h) {
    h = new_h;
    int n = static_cast<int>((b - a) / h);
    if (n % 2 != 0) {
        n += 1; 
        h = (b - a) / n; 
    }
    buildGrid(); 
}
