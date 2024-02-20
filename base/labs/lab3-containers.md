
# Лабораторная работа № 3 <!-- omit in toc -->
# Контейнеры <!-- omit in toc -->

## ⚠ Данный документ находится в разработке и не предназначен (пока) для обучающихся <!-- omit in toc -->

- [1 Теоретические сведения](#1-теоретические-сведения)
  - [1.1 Обработка ошибок: механизм исключений](#11-обработка-ошибок-механизм-исключений)
  - [1.2 Работа с динамической памятью](#12-работа-с-динамической-памятью)
  - [1.3 Деструктор и идиома RAII](#13-деструктор-и-идиома-raii)
  - [1.4 Правило трёх](#14-правило-трёх)
- [2 Обязательное задание](#2-обязательное-задание)
  - [2.1 Общее задание](#21-общее-задание)
  - [2.2 Варианты](#22-варианты)
  - [2.3 Нормы](#23-нормы)
- [3 Факультативное задание](#3-факультативное-задание)

# 1 Теоретические сведения

## 1.1 Обработка ошибок: механизм исключений

TODO

Нормы:
- [E.2: Throw an exception to signal that a function can’t perform its assigned task](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e2-throw-an-exception-to-signal-that-a-function-cant-perform-its-assigned-task)
- [E.3: Use exceptions for error handling only](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e3-use-exceptions-for-error-handling-only)
- [E.12: Use noexcept when exiting a function because of a throw is impossible or unacceptable](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e12-use-noexcept-when-exiting-a-function-because-of-a-throw-is-impossible-or-unacceptable)
- [E.15: Throw by value, catch exceptions from a hierarchy by reference](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e15-throw-by-value-catch-exceptions-from-a-hierarchy-by-reference)
- [E.17: Don’t try to catch every exception in every function](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e17-dont-try-to-catch-every-exception-in-every-function)
- [E.18: Minimize the use of explicit try/catch](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e18-minimize-the-use-of-explicit-trycatch)



## 1.2 Работа с динамической памятью

Выделение/освобождение динамической памяти осуществляется с помощью операторов `new` и `delete`.

- Выделение и освобождение памяти памяти под один элемент - операторы `new` и `delete`:
```cpp
// Примитивный тип без инициализации (нерекомендуемый вариант)
float* fp1 = new float; // ⚠ Выделенная память не инициализируется
*fp1 = 0;

// Примитивный тип с инициализацией (рекомендуемый вариант)
float* fp2 = new float(); // Можно указать своё значение в скобках

// Объект класса T
T* tp1 = new T();     // Инициализация конструктором по умолчанию
T* tp2 = new T(3, 4); // Можно использовать нужную перегрузку конструктора

// Освобождение памяти
delete tp2;
delete tp1;
delete fp2;
delete fp1;
```

- Выделение и освобождение памяти под массив - операторы `new[]` и `delete[]`:
```cpp
const int n = 10;

// Примитивный тип без инициализации
float* fp1 = new float[n]; // ⚠ Выделенная память не инициализируется
std::fill_n(fp1, n, 1);    // Заполнить все элементы единичками (#include <algorithm>)

// Примитивный тип с инициализацией
// ⚠ Своё значение в скобках указать нельзя: если нужны ненулевые значения - см. предыдущий вариант
float* fp2 = new float[n](); 

// Объект класса T
T* tp1 = new T[n](); // В скобках ничего указывать нельзя, всегда используется конструктор по умолчанию

// Освобождение памяти
delete[] tp1;
delete[] fp2;
delete[] fp1;
```

- В отличие от функций `malloc`/`free`, операторы занимаются не только выделением/освобождением памяти,
  но и инициализацией/деинициализиацией (с помощью конструкторов/деструкторов).

- В C++ для указания нулевого указателя используется ключевое слово `nullptr`.
  Макрос `NULL` лучше не использовать.

  Пример с сюрпризом на компиляторе `cl` версии 19.39 (Visual Studio 2022):
  ```cpp
  #include <iostream>

  using namespace std;

  void f(int) {
    cout << "int overload\n";
  }

  void f(void*) {
    cout << "ptr overload\n";
  }

  int main() {
    f(0);       // int overload
    f(NULL);    // Угадайте, что будет здесь?
    f(nullptr); // ptr overload
  }
  ```

- Если оператор `new`/`new[]` не может выделить память, он сгенерирует исключение типа
  [`std::bad_alloc`](https://en.cppreference.com/w/cpp/memory/new/bad_alloc).
  - Можно подавить генерацию исключения с помощью [std::nothrow](https://en.cppreference.com/w/cpp/memory/new/nothrow).
    В этом случае оператор в случае неудачи вернёт `nullptr`.
- Любая выделенная с помощью `new` память должна быть освобождена.
  Бремя освобождения лежит на программисте.
- В общем случае использование операторов `new`/`delete` не рекомендуется,
  так как накладывает обязательство по ручному освобождению памяти.
  Вместо этого используют [`std::vector`](https://en.cppreference.com/w/cpp/container/vector).
  Однако в текущей лабораторной работе вы пишите свой грубый аналог `std::vector` и поэтому в данной
  (и только в данной!) работе вместо `std::vector` используется ручное управление памятью.
- \* Факультативная информация: так как `new`/`delete` являются операторами, то их можно...
  [перегрузить](https://en.cppreference.com/w/cpp/memory/new/operator_new)!

Нормы:
- [E.13: Never throw while being the direct owner of an object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e13-never-throw-while-being-the-direct-owner-of-an-object)



## 1.3 Деструктор и идиома RAII

TODO

См. также [C++ Idioms: Resource Acquisition Is Initialization](https://en.wikibooks.org/w/index.php?title=More_C%2B%2B_Idioms/Resource_Acquisition_Is_Initialization&stable=1).

Нормы:
- [E.16: Destructors, deallocation, swap, and exception type copy/move construction must never fail](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e16-destructors-deallocation-swap-and-exception-type-copymove-construction-must-never-fail)



## 1.4 Правило трёх

TODO

См. также [C++ Idioms: Copy-and-swap](https://en.wikibooks.org/w/index.php?title=More_C%2B%2B_Idioms/Copy-and-swap&stable=1).

Нормы:
- [E.16: Destructors, deallocation, swap, and exception type copy/move construction must never fail](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e16-destructors-deallocation-swap-and-exception-type-copymove-construction-must-never-fail)



# 2 Обязательное задание

## 2.1 Общее задание

**⚠ Примечание.**
В данной лабораторной работе вас просят написать **свой класс-контейнер**,
в котором вы **сами управляете динамической памятью**.
Это сделано исключительно с учебной целью - чтобы лучше понять как устроено управление памятью в C++.
- **В данной лабораторной работе** запрещено использовать любые контейнеры
  или умные указатели из стандартной библиотеки.
  Управлять памятью вы должны самостоятельно (использовать операторы `new` и `delete`).
  Это и не соответствует реальной практике (*изобретаем велосипед*), но позволяет лучше разобраться в теме.
- **Во всех последующих лабораторных работах**, наоборот, в соответствии с реальной практикой,
  любое ручное управление памятью становится табу.
  Для управления памятью будем по максимуму использовать специально предназначенные для этого
  классы стандартной библиотеки - контейнеры и умные указатели (*не изобретаем велосипед*).

Номер вашего варианта совпадает с номером варианта в предыдущей лабораторной работе.

1. Реализовать класс-контейнер для хранения объектов типа `T`,
   где `T` - ваш класс из прошлой лабораторной работы.

   В классе-контейнере внутри для хранения объектов типа `T` должен использоваться динамический массив.
   Если ваш тип `T` не содержит конструктор по умолчанию - добавьте его.

   В классе-контейнере предоставить:
   - конструктор по умолчанию, создающий пустой контейнер;
   - метод получения количества элементов в контейнере;
   - метод получения элемента из контейнера по указанному индексу;
     - на ваше усмотрение вместо этого метода может быть предоставлена перегрузка оператора `[]`.
   - метод вставки элемента в контейнер по указанному индексу;
   - метод удаления элемента из контейнера по указанному индексу;
   - другие необходимые члены для обеспечения копируемости и корректного управления памятью (правило трёх).

   При указании некорректного индекса должно генерироваться исключение.

1. Написать функцию согласно варианту, которая:
   - принимает контейнер (и, может быть, некоторые другие параметры в зависимости от варианта);
   - возвращает **индекс элемента**, удовлетворяющего некоторому критерию (см. вариант):
     - если такого элемента нет или контейнер пустой - вернуть -1;
     - если есть несколько элементов, удовлетворяющих критерию - вернуть индекс самого первого из них.

1. Продемонстрировать работоспособность написанного класса, в том числе его копируемость,
   одним из следующих способов:
   - классически с использованием `main` и ввода данных пользователем с консоли;
   - с использованием модульного тестирования (см. факультативную часть предыдущей лабораторной работы).
   
   В плане оценки оба способа эквиваленты (за модульное тестирование какие-либо дополнительные баллы не ставятся).

   При использовании модульного тестирования:
   - не нужно писать свой `main` и объявлять отдельное исполняемое приложение:
     - в лучшем случае у вас будет две цели сборки: библиотека с классами и исполняемое приложение с тестами;
     - в худшем случае можно обойтись одной целью сборки: исполняемым приложением с тестами.
   - тестами должны быть покрыты:
     - метод вставки;
     - метод удаления;
     - оператор присваивания;
     - функция согласно варианту.
   - тесты должны проверять в том числе и генерацию исключения при указании некорректного индекса
     (см. [GoogleTest: Exception Assertions](https://google.github.io/googletest/reference/assertions.html#exceptions)).



## 2.2 Варианты

- Слово *заданный* означает необходимость в дополнительном параметре функции.
- Если идут приближённые вычисления, то $\epsilon$ - это тоже дополнительный параметр функции.

1. Дробь, значение которой равно *заданному* вещественному числу (приближённо с некоторой погрешностью $\epsilon$).
1. Интервал, который содержит в себе значение 0.
1. Матрица, которая является единичной (приближённо с некоторой погрешностью $\epsilon$).
1. Вектор, который перпендикулярен *заданному* вектору (приближённо с некоторой погрешностью $\epsilon$).
1. Вектор, который коллинеарен *заданному* вектору (приближённо с некоторой погрешностью $\epsilon$).
1. Прямоугольник, который содержит *заданную* точку (точка находится внутри прямоугольника).
1. Окружность, которая содержит *заданную* точку (точка находится внутри окружности).
1. Треугольник с периметром, равным заданному вещественному числу
   (приближённо с некоторой погрешностью $\epsilon$).
1. Квадратичная функция, значение которой в точке $x=0$ превосходит *заданное* значение.
1. Цилиндр, который содержит *заданную* точку (точка находится внутри цилиндра).
1. Отрезок, который содержит *заданную* точку (приближённо с некоторой погрешностью $\epsilon$).
1. Прямая, которая содержит *заданную* точку (приближённо с некоторой погрешностью $\epsilon$).
1. Денежная сумма, которая превышает *заданную* денежную сумму.
1. Длительность по времени, которая превышает *заданную* длительность по времени.
1. Угол, который превышает *заданный* угол.



## 2.3 Нормы

- [E.2: Throw an exception to signal that a function can’t perform its assigned task](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e2-throw-an-exception-to-signal-that-a-function-cant-perform-its-assigned-task)
- [E.3: Use exceptions for error handling only](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e3-use-exceptions-for-error-handling-only)
- [E.12: Use noexcept when exiting a function because of a throw is impossible or unacceptable](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e12-use-noexcept-when-exiting-a-function-because-of-a-throw-is-impossible-or-unacceptable)
- [E.13: Never throw while being the direct owner of an object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e13-never-throw-while-being-the-direct-owner-of-an-object)
- [E.15: Throw by value, catch exceptions from a hierarchy by reference](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e15-throw-by-value-catch-exceptions-from-a-hierarchy-by-reference)
- [E.16: Destructors, deallocation, swap, and exception type copy/move construction must never fail](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e16-destructors-deallocation-swap-and-exception-type-copymove-construction-must-never-fail)
- [E.17: Don’t try to catch every exception in every function](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e17-dont-try-to-catch-every-exception-in-every-function)
- [E.18: Minimize the use of explicit try/catch](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e18-minimize-the-use-of-explicit-trycatch)



# 3 Факультативное задание

1. Продемонстрировать работоспособность вашего проекта под операционной системой семейства Linux.
1. Оптимизируйте класс контейнера так, чтобы он не занимался перераспределением
   (выделением/освобождением) памяти при каждой операции вставки/удаления.
   Помимо размера `size` (количество фактических элементов в массиве),
   понадобится также хранить ёмкость `capacity` (количество возможных элементов в массиве).
   - Измените реализацию метода вставки.
     - Если при вставке `size` меньше `capacity`, то память не перераспределяется.
     - Если `size` равен `capacity`, то при перераспределении памяти она выделяется сразу с запасом
       (например, `capacity` удваивается).
   - Измените реализацию метода удаления.
     - При удалении происходит только сдвиг элементов, память никогда не перераспределяется.
   - Предоставьте дополнительный метод `shrink_to_fit` для принудительного перераспределения памяти
     (уменьшения размера буфера `capacity` до фактического размера массива `size`).
   - См. также:
     - [Wikipedia. Dynamic array. Geometric expansion and amortized cost](https://en.wikipedia.org/wiki/Dynamic_array#Geometric_expansion_and_amortized_cost)
     - [Difference between size and capacity of a vector in C++ STL](https://www.geeksforgeeks.org/difference-between-size-and-capacity-of-a-vector-in-cpp-stl/)
     - `std::vector`:
       - [size](https://en.cppreference.com/w/cpp/container/vector/size);
       - [capacity](https://en.cppreference.com/w/cpp/container/vector/capacity);
       - [shrink_to_fit](https://en.cppreference.com/w/cpp/container/vector/shrink_to_fit).
1. Задокументируйте класс, все открытые члены класса, все глобальные функции
   (всё это делается в заголовочном файле) и
   сгенерируйте веб-документацию в формате HTML.
   - Документация пишется в самом коде в виде специальных комментариев.
     Для методов (функций) задокументирован должен быть не только сам метод (функция),
     но и возвращаемое значение и все параметры.
     См. [Doxygen: Documenting the code](https://www.doxygen.nl/manual/docblocks.html).
   - Для генерации веб-документации:
     - Установите Doxygen.
        - Linux (`apt`): `sudo apt install doxygen`.
        - MacOS/Windows: используйте установщик с [официального сайта](https://www.doxygen.nl/download.html).
     - Сгенерируйте HTML-документацию. См. [Doxygen: Getting started](https://www.doxygen.nl/manual/starting.html).
     - Результатом работы генератора должна быть директория (`html`), в которой находится HTML-документация.
        Если в этой директории открыть файл `index.html`, то документация должна открыться в браузере.
        Сгенерированная документация должна выглядеть (по крайней мере, шапка) примерно [вот так](https://docs.opencv.org/4.x/index.html).
   - Для зачёта факультативного пункта откройте преподавателю сгенерированную HTML-документацию в браузере.
     - При необходимости (по требованию преподавателя) покажите
       каким образом документируется код и/или генерируется HTML-документация.
