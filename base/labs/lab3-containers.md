
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

// Объект некоторого класса T
T* tp1 = new T;       // Инициализация конструктором по умолчанию
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

// Объект некоторого класса T
// ⚠ Скобки указать можно, но вот в скобках ничего указывать нельзя - всегда используется конструктор по умолчанию
T* tp1 = new T[n];

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

Нормы:
- [E.13: Never throw while being the direct owner of an object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e13-never-throw-while-being-the-direct-owner-of-an-object)



## 1.3 Деструктор и идиома RAII

Деструктор - специальный метод, который **автоматически** вызывается перед удалением объекта.

Деструктор всегда вызывается автоматически:
- для объектов, расположенных на стеке - в момент выхода объекта из области видимости;
- для объектов, расположенных в куче - в момент вызова оператора `delete`/`delete[]`.

Деструктор в классе `T` описывается как метод:
- без возвращаемого значения (не указывается даже `void`);
- с названием `~T`;
- без параметров.

Демонстрация автоматического вызова деструктора:
```cpp
#include <iostream>

using namespace std;

struct SomeType {
  ~SomeType() {
    cout << "~SomeType\n";
  }
};

int main() {
  {
    cout << "#1\n";
    SomeType obj;
  }

  {
    cout << "#2\n";  
    SomeType* ptr = new SomeType;
    delete ptr;
  }
  
  {
    cout << "#3\n";  
    SomeType* ptr = new SomeType[5];
    delete[] ptr;
  }

  return 0;
}
```

Вышеприведённый код выведет следующее:
```
#1
~SomeType
#2
~SomeType
#3
~SomeType
~SomeType
~SomeType
~SomeType
~SomeType
```

Если в классе не объявлен деструктор, то компилятор генерирует неявную версию деструктора, которая ничего не делает.

После отработки тела деструктора (неважно, явного или неявного) вызываются деструкторы для всех полей-объектов.

Демонстрация автоматического вызова деструктора для полей-объектов:
```cpp
#include <iostream>

using namespace std;

struct Point {
  ~Point() {
    cout << "~Point\n";
  }
};

struct Circle {
  Point center;

  ~Circle() {
    cout << "~Circle\n";
  }
};

int main() {
  {
    cout << "#1\n";
    Circle c;
  }

  {
    cout << "#2\n";  
    Circle* ptr = new Circle();
    delete ptr;
  }
  
  {
    cout << "#3\n";  
    Circle* ptr = new Circle[2]();
    delete[] ptr;
  }

  return 0;
}
```

Вышеприведённый код выведет следующее:
```
#1
~Circle
~Point
#2
~Circle
~Point
#3
~Circle
~Point
~Circle
~Point
```

Отметим некоторые важные моменты касаемо деструкторов:
- Явный деструктор в классе должен предоставляться только в том случае,
  если объекты этого класса владеют какими-либо ресурсами, которые должны быть освобождены.
- В общем случае необходимости предоставлять собственный деструктор нет.
  Если внутри объекта есть необходимость работы с каким-то ресурсом,
  используется специально предназначенный для этого класс.
  - Например, если необходима работа с динамической памятью, используется `std::vector`.
- ⚠ Деструктор всегда вызывается автоматически. Они никогда не должны вызываться явно.
- ⚠ Исключения ни при каких условиях не должны покидать деструктор.

С помощью деструкторов можно реализовать идиому RAII
(Resource Acquisition Is Initialization - получение ресурса есть инициализация).
Смысл этой идиомы заключается в следующем:
- В конструкторе объект получает доступ к какому-либо ресурсу
  (например, выделяется динамическая память, открывается файл или устанавливается соединение по сети)
  и сохраняет описатель ресурса в закрытый член класса.
- В деструкторе ресурс освобождается
  (например, освобождается динамическая память, закрывается файл или закрывается соединение по сети).
- **Вся соль в том, что в C++ деструктор вызывается автоматически.
  Это означает, что с программиста снимается бремя по ручному освобождению ресурса.**


Приведем пример, где ресурсом является динамическая память, тогда описателем ресурса является указатель.
Отметим, что приводимый ниже класс - это лишь иллюстрация идиомы RAII.
В реальности писать такой класс для динамической памяти не надо (ведь есть `std::vector`).
Однако эта идиома может применяться не только к динамической памяти,
но и к любому ресурсу, который требует освобождения.

```cpp
#include <iostream>

class IntArray {
private:
  int* _ptr;
  size_t _size;
  
public:
  IntArray(size_t size) : _size(size) {
    _ptr = new int[size]();
  }

  IntArray(const IntArray&) = delete;

  IntArray& operator=(const IntArray&) = delete;

  int* ptr() {
    return _ptr;
  }

  size_t size() {
    return _size;
  }

  ~IntArray() {
    delete[] _ptr;
  }
};

int main() {
  IntArray data(5);
  
  // Работа с объектом: data.ptr() / data.size()
  
  // Вручную освобождать ничего не нужно!
  // При завершении функции автоматически вызовется деструктор IntArray,
  // который освободит выделенную в конструкторе динамическую память.

  return 0;
}
```

Обратите внимание на явный запрет операций копирования (конструктора копирования и оператора присваивания).
Если их не запретить, компилятор сгенерирует неявные определения.
Напомним, что неявные реализации операций копирования сводятся к простому копированию всех полей.
- Подумайте, чем чревато наличие таких неявных определений?

См. также:
- [C++ Idioms: Resource Acquisition Is Initialization](https://en.wikibooks.org/w/index.php?title=More_C%2B%2B_Idioms/Resource_Acquisition_Is_Initialization&stable=1).

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
  Хоть это и не соответствует реальной практике (*изобретаем велосипед*), но позволяет лучше разобраться в теме.
- **Во всех последующих лабораторных работах**, наоборот, в соответствии с реальной практикой,
  любое ручное управление памятью становится табу.
  Для управления памятью должны использоваться специально предназначенные для этого
  классы стандартной библиотеки - контейнеры и умные указатели (*не изобретать велосипед*).

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

2. Написать функцию согласно варианту, которая:
   - принимает контейнер (и, может быть, некоторые другие параметры в зависимости от варианта);
   - возвращает **индекс элемента**, удовлетворяющего некоторому критерию (см. вариант):
     - если такого элемента нет или контейнер пустой - вернуть -1;
     - если есть несколько элементов, удовлетворяющих критерию - вернуть индекс самого первого из них.

3. Продемонстрировать работоспособность написанного класса, в том числе его копируемость,
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
        В этой директории должен находиться файл `index.html`, который можно открыть в браузере.
        Сгенерированная документация должна выглядеть (по крайней мере, шапка) примерно вот так:
        [OpenCV Documentation](https://docs.opencv.org/4.x/index.html).
   - Для зачёта факультативного пункта откройте преподавателю сгенерированную HTML-документацию в браузере.
     - При необходимости (по требованию преподавателя) покажите
       каким образом документируется код и/или генерируется HTML-документация.
