#pragma once

#define _USE_MATH_DEFINES

// Файл для хранения классов числовых полей в которых можно решать наше уравнение

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


class Complex { // Класс комплексного числа
protected:
    double real;       // Вещественная часть
    double imaginary;  // Мнимая часть

public:
    Complex(double real = 0.0, double imaginary = 0.0) : real(real), imaginary(imaginary) {}

    // Геттеры
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    // Сеттеры
    void setReal(const double real) { this->real = real; }
    virtual void setImaginary(const double imaginary) { this->imaginary = imaginary; }


    // Перегрузка оператора +
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    // Перегрузка оператора -
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    // Перегрузка оператора - (унарного)
    Complex operator-() const {
        return Complex(-real, -imaginary);
    }

    // Перегрузка оператора *
    Complex operator*(const Complex& other) const {
        double newReal = real * other.real - imaginary * other.imaginary;
        double newImaginary = real * other.imaginary + imaginary * other.real;

        return Complex(newReal, newImaginary);
    }

    // Перегрузка оператора /
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double newReal = (real * other.real + imaginary * other.imaginary) / denominator;
        double newImaginary = (imaginary * other.real - real * other.imaginary) / denominator;

        return Complex(newReal, newImaginary);
    }

    // Перегрузка оператора +=
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imaginary += other.imaginary;

        return *this;
    }

    // Перегрузка оператора ==
    bool operator==(const Complex& other) {
        return (real == other.real && imaginary == other.imaginary);
    }

    // Перегрузка оператора !
    bool operator!() const {
        return (fabs(magnitude()) < 1e-14);
    }

    // Получение модуля комплексного числа
    double magnitude() const {
        return std::sqrt(real * real + imaginary * imaginary);
    }

    // Получание агрумента комплексного числа
    double argument() const {
        return atan2(imaginary, real);
    }

    // Получение n-ого корня комплексного числа
    virtual vector<Complex> sqrt(const int n = 2) {
        double r = pow(this->magnitude(), 1.0 / n);;
        double f = this->argument();

        vector<Complex> answer;

        for (int k = 0;k < n;k++)
            answer.push_back(Complex(r * cos((f + 2 * M_PI * k) / n), r * sin((f + 2 * M_PI * k) / n)));

        return answer;
    }

    // Перегрузка опрератора <<
    friend ostream& operator<<(ostream& os, const Complex& complex) {
        os << "(" << complex.real;
        if (complex.imaginary >= 0) {
            os << " + " << complex.imaginary << "i)";
        }
        else {
            os << " - " << -complex.imaginary << "i)";
        }
        return os;
    }

    // Перегрузка оператора >>
    friend istream& operator>>(istream& is, Complex& complex) {
        is >> complex.real >> complex.imaginary;

        return is;
    }

    virtual ~Complex() {};
};



class Real : public Complex { // Класс вещественного числа
public:
    Real(double real = 0.0) : Complex(real, 0.0) {}
    Real(Complex c) : Real(c.getReal()) {}

    // Переопределение метода для установки мнимой части 
    void setImaginary(double imaginary) override {}

    // Перегрузка оператора <<
    friend ostream& operator<<(ostream& os, const Real& real) {
        os << real.getReal();

        return os;
    }

    // Перегрузка оператора >>
    friend istream& operator>>(istream& is, Real& real) {
        is >> real.real;

        return is;
    }

    // Получение n-ого корня числа
    vector<Complex> sqrt(const int n = 2) override {
        if (this->getReal() < 0) return vector<Complex>({});

        double root = pow(this->getReal(), 1.0 / n);

        vector<Complex> answer;
        answer.push_back(root);
        if (n % 2 == 0)
            answer.push_back(-root);

        return answer;
    }

    ~Real() {};
};