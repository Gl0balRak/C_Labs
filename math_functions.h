#pragma once

#include <iostream>
#include <cmath>
#include <vector>


template<typename T> class Roots { // Класс для хранения решения уравнения
private:
    vector<T> roots; // Список корней
    bool infinity;   // Флаг бесконечного числа решений

public:
    Roots() : roots(), infinity(false) {}


    // Геттеры
    bool inf() { return infinity; }

    int size() {
        return roots.size();
    }

    // Сеттеры
    void set_inf(const bool infinity) { this->infinity = infinity; };

    void add_root(T root) {
        roots.push_back(root);
    }

    T& operator[] (int index) {
        return roots[index];
    }

};


template<typename T> class Function {  // Абстрактный класс математической функции
public:
    virtual Roots<T> roots() { return Roots<T>({}); };
    virtual T operator() (T x) { return T(0); };
};

template<typename T> class Polynom : public Function<T> { // Класс полинома
protected:
    vector<T> coefficients; // Список коэфицентов

public:
    Polynom(vector<T> coefficients) : Function<T>(), coefficients(coefficients) {}

    // Перегружаем оператор индексации
    T& operator[] (int index) {
        return coefficients[index];
    }

    // Перегруужаем оператор ()
    T operator() (T x) override {
        T result(0);
        for (T& const coef : coefficients)
            result = coef + result * x;

        return result;
    }

    // Перегружаем оператор <<
    friend ostream& operator<<(ostream& os, const Polynom& poly) {
        int size = poly.coefficients.size();
        os << poly.coefficients[size - 1];
        for (int i = size - 2;i > -1; i--)
            os << " + " << poly.coefficients[i] << "*x^" << size - i - 1;

        return os;
    }
};


template<typename T> class Polynom2 : public Polynom <T> {  // Класс квадратичной функции
public:
    Polynom2(vector<T> coefficients) : Polynom<T>(vector<T>(coefficients.begin(), coefficients.begin() + 3)) {}

    // Функция для поиска корней квадратного уравнения
    Roots<T> roots() override {
        Roots<T> _roots;

        _roots.set_inf(!(*this)[0] && !(*this)[1] && !(*this)[2]);
        if (_roots.inf())
            return _roots;

        if (!(*this)[0] && !(*this)[1])
            return _roots;

        if (!(*this)[0]) {
            _roots.add_root(-(*this)[2] / (*this)[1]);
            return _roots;

        }

        T Descriminant = (*this)[1] * (*this)[1] - T(4) * (*this)[0] * (*this)[2];
        vector<Complex> _D = Descriminant.sqrt();

        if (!_D.size())
            return _roots;

        _roots.add_root((-_D[0] - (*this)[1]) / (T(2) * (*this)[0]));
        if (!Descriminant)
            return _roots;

        _roots.add_root((_D[0] - (*this)[1]) / (T(2) * (*this)[0]));
        return _roots;
    }
};