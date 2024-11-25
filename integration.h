#ifndef integration_h
#define integration_h

#include <vector>
#include <cmath>
#include <functional>
#include <iostream>


class NumericalIntegrator {
public:
    NumericalIntegrator(double a, double b, double h) : a(a), b(b), h(h) {
        buildGrid();
    }
    double parabola(const std::function<double(double)>& f);
    double gauss2(const std::function<double(double)>& f);
    double get_h();
    void set_h(double new_h);
private:
    double a, b, h;
    std::vector<double> grid;

    void buildGrid();
};
#endif