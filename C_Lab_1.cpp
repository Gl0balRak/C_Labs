#include "number_fields.h"
#include "math_functions.h"

#include <Windows.h>

#define K Complex // Real // Над каким полем решаем уравнение (доступные поля ииклюдятся из number_fields.h)



int main() {
    SetConsoleOutputCP(1251); // Что бы были руские букавы

    Polynom2<K> p({ 0, 0, 0 }); // Создаем пустой полином 2 степени

    // Получаем из консоли коэфиценты квадратного уравнения
    for (int i = 0;i < 3;i++) {
        K n;

        cout << "Введите коэфицент " << i + 1
            << ((is_same<K, Real>::value) ? " (вещественное число): " : " (вещественная и мнимая части через пробел): ");
        cin >> n;

        p[i] = n;
    }
    cout << "\nБыло введено уравнение: \n" << p << " = 0\n";


    Roots<K> r = p.roots(); // Находим корни

    cout << "\nРешение:\n";

    if (r.inf()) {
        cout << "Infinity roots!\n";
        return 0;
    }
    
    if (!r.size())
        cout << "No roots!\n";

    for (int i = 0;i < r.size();i++) // Вывод корней
        cout << "x" << i+1 << " = " << r[i] << endl;
    cout << endl;


    return 0;
}
