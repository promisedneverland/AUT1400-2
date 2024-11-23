#ifndef Q1_H
#define Q1_H

#include <functional>
namespace q1
{
    

const double h = 1e-5;
const double iteration = 1e6;

template<typename T>
T gradient(T x, std::function<T(T)> func) {
    return (func(x + h) - func(x)) / h;
}


template<typename T >
double gradient_descent(T init, T step, std::function<double(double)> func) {
    double cur = init;
    for(int i = 0; i < iteration; i++){
        cur = cur - gradient(cur, func) * step;
    }
    return cur;
}

template<typename T, class Func> 
double gradient_descent(T init, T step) {
    return gradient_descent(init, step, Func());
}
} // namespace q1
#endif //Q1_H