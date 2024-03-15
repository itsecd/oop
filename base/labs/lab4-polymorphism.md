
# Лабораторная работа № 4 <!-- omit in toc -->
# Полиморфные классы <!-- omit in toc -->

## ⚠ Данный документ находится в разработке и не предназначен (пока) для обучающихся <!-- omit in toc -->

- [1 Теоретические сведения](#1-теоретические-сведения)
  - [1.1 Наследование](#11-наследование)
  - [1.2 Умные указатели и приведение типов](#12-умные-указатели-и-приведение-типов)
  - [1.3 Перекрытие методов и раннее связывание](#13-перекрытие-методов-и-раннее-связывание)
  - [1.4 Переопределение методов и позднее связывание](#14-переопределение-методов-и-позднее-связывание)
  - [1.5 Абстрактные классы и интерфейсы](#15-абстрактные-классы-и-интерфейсы)
- [2 Обязательное задание](#2-обязательное-задание)
  - [2.1 Общее задание](#21-общее-задание)
  - [2.2 Варианты](#22-варианты)
  - [2.3 Нормы](#23-нормы)
- [3 Факультативное задание](#3-факультативное-задание)

# 1 Теоретические сведения

## 1.1 Наследование

Наследование позволяет определять новый тип, расширяя уже существующий.

Предположим, есть класс `Person`, позволяющий хранить имя, фамилию и дату рождения:

```cpp
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

class Person {
  string _first_name;
  string _last_name;
  year_month_day _birthdate;

public:
  Person(const string& first_name, const string& last_name, const year_month_day& birthdate) :
    _first_name(first_name), _last_name(last_name), _birthdate(birthdate) { }

  const string& first_name() const {
    return _first_name;
  }

  const string& last_name() const {
    return _last_name;
  }

  const year_month_day& birthdate() const {
    return _birthdate;
  }

  Person(const Person&) = delete;            // Объяснения см. в лекции и нормах
  Person& operator=(const Person&) = delete; // Объяснения см. в лекции и нормах
  virtual ~Person() = default;               // Объяснения см. в лекции и нормах
};
```

Предположим, необходимо определить класс студента `Student`.
При этом студент определяется не только теми атрибутами, которые есть у любого человека
(т. е. именем, фамилией, датой рождения - всем тем, что есть у `Person`),
но и некоторыми специфичными данными - например, номером зачётной книжки `student_id`.
Тогда новый класс `Student` можно определить как **наследник** класса `Person`:

```cpp
class Student : public Person {
  string _student_id;

public:
  Student(
    const string& first_name,
    const string& last_name,
    const year_month_day& birthdate,
    const string& student_id
  ) :
    Person(first_name, last_name, birthdate),
    _student_id(student_id)
  { }

  const string& student_id() const {
    return _student_id;
  }
};
```

При этом класс `Student` получит все то, что есть у класса `Person`,
в частности, публичные методы `first_name`, `last_name`, `birthdate`.
Приватные поля тоже унаследуется, но прямого доступа к ним не будет.

Здесь возникает смысл в третьем модификаторе доступа `protected`:
- `private` - доступ есть только у самого класса;
- `protected` - доступ есть только у самого класса и его наследников;
- `public` - доступ есть у всех.

Обратим внимание, что при наследовании тоже указывается модификатор:
```cpp
class Student : public Person {
  // ...
};
```

В данном контексте `public` означает вид наследования.
Если кратко, то этот модификатор задаёт максимально допустимую область видимости унаследованных членов для внешнего кода.
- `public` оставляет область видимости неизменной;
- `private`, например, сделал бы все унаследованные `protected` и `public`-члены закрытыми.

В рамках нашего курса всегда будет использоваться только открытое (`public`) наследование,
как самое распространённое и основное.
Остальные виды наследования имеют достаточно узкий круг применения и выходят за рамки нашего курса.

При создании объекта порядок вызова конструкторов - сверху вниз (от базового класса к дочернему).
Если для инициализации базового класса необходимо использовать конструктор с параметрами,
то необходимый конструктор должен вызываться в списке инициализации (см. конструктор `Student`).
При уничтожении объекта порядок вызова деструкторов обратен порядку вызова конструкторов,
то есть деструктора вызываются снизу вверх (от дочернего класса к базовому).

**Обратим внимание, что основной причиной применения наследования является не избежание дублирования кода
(полей и методов класса), а моделирование отношения "является" (студент является человеком).
Устранение дублирования здесь является лишь побочным эффектом.**

Это позволяет писать абстрактный код, работающий на уровне базового класса,
и ничего не знающий о реальном типе объекта:

```cpp
// ...

void print(const Person& p) {
  cout << p.birthdate() << ' ' << p.last_name() << ' ' << p.first_name() << ' ' << '\n';
}

int main() {
  Person p("Gina", "Rayo", year_month_day(1957y, June, 15d));
  Student s("Alfred ", "Parker", year_month_day(1980y, December, 13d), "123-456-789");
    
  print(p);
  print(s);
}
```

Обратите внимание, что `print` принимает параметр типа `Person`.
Но так как `Student` является наследником `Person`, 
то в качестве аргумента функции `print` можно указать студента (объект типа `Student`).
При этом сама функция `print` оперирует с объектом на уровне базового класса (`Person`),
ничего не зная о реальном типе (`Person` или `Student`).

Таким образом, функции `print` можно в качестве аргумента передать объект любого типа,
являющегося наследником от типа `Person`.

Отметим, что наследование позволяет реализовать динамический полиморфизм
(полиморфизм времени выполнения), когда один и тот же код (в примере выше - тело функции `print`)
**во время выполнения программы** (а не во время компиляции, как в случае с шаблонами)
может работать с различными типами данных (в примере выше - `Person` и `Student`).

**⚠ Обратим внимание, что при работе с иерархией классов принципиально важно
передавать базовый класс по ссылке или через указатель, но не по значению.**
В противном случае может произойти так называемая
[срезка](https://www.geeksforgeeks.org/object-slicing-in-c/)
объекта, которая является одной из ошибок программирования на C++.

Нормы:
- [C.133: Avoid protected data](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c133-avoid-protected-data)
- [C.145: Access polymorphic objects through pointers and references](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c145-access-polymorphic-objects-through-pointers-and-references)
- [C.152: Never assign a pointer to an array of derived class objects to a pointer to its base](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c152-never-assign-a-pointer-to-an-array-of-derived-class-objects-to-a-pointer-to-its-base)



## 1.2 Умные указатели и приведение типов

Вы уже знаете, что при необходимости работы со статическим/динамическим массивом
используется шаблонные классы `std::array`/`std::vector`.

Но что, если необходимо завести указатель на **один** объект?

Для этого используются **умные указатели** - шаблонные классы
[`std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr) (разделяемое владение)
и
[`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr) (исключительное владение)
из заголовочного файла `<memory>`.
Данные шаблонные классы автоматически (за счёт деструктора) освобождают память, когда объект становится никому не нужным.
Данные классы перегружают операторы разыменовки `*`, `->` и операторы сравнения с `nullptr` -
таким образом, с объектами этих классов можно работать так, как будто бы это обычные указатели.

```cpp
#include <iostream>
#include <memory>

using namespace std;

struct T {
  T(int a, int b) { }
};

int main() {
  // Пример использования shared_ptr (разделяемое владение со счётчиком)
  {
    shared_ptr<T> sp1 = make_shared<T>(1, 2);

    // shared_ptr является копируемым:
    shared_ptr<T> sp2(sp1);

    // Здесь sp1 и sp2 указывают на один и тот же объект,
    // при этом оба указателя являются полноправными владельцами.
    // Внутри используется счётчик ссылок,
    // текущее значение счётчика можно получить с помощью use_count.
    // Оператор delete для объекта вызовется, когда счётчик достигнет 0.
    cout << sp1.use_count() << '\n'; // Выведет 2
  } // Деструкторы sp1 и sp2 уменьшают счетчик до 0
    // и объект T удаляется из кучи последним отработавшим деструктором

  // Пример использования unique_ptr (исключительное владение)
  {
    unique_ptr<T> up1 = make_unique<T>(1, 2);

    cout << up1 << '\n';

    // unique_ptr скопировать нельзя, но владение можно "передать" с помощью std::move:
    unique_ptr<T> up2(move(up1));

    // Здесь up1 == nullptr, так как он передал ресурс, которым владеет, другому владельцу (up2).
    // Владельцем созданного объекта теперь является up2.

    cout << up1 << ' ' << up2 << '\n';
  } // Деструктор up2 удалит объект из кучи
}
```

При создании умных указателей желательно пользоваться не их конструкторами напрямую,
а использовать вспомогательные шаблонные функции `make_unique` и `make_shared` из заголовочного файла `<memory>`.
В качестве шаблонного аргумента указывается тип создаваемого объекта (в примере выше - `T`),
а в качестве аргументов вызова функций - параметры нужного конструктора (в примере выше - два числа).

Приведение типа от дочернего класса к базовому (**upcasting**, "повышающее приведение", "абстрагирование") всегда выполняется автоматически и
является безопасным (т. к. дочерний класс всегда можно привести к базовому).

Обратная операция (**downcasting**, "понижающее приведение", "уточнение типа") является небезопасной
(базовый тип не всегда можно привести к указанному дочернему, ведь реальный тип может отличаться от указанного дочернего).
Для приведения базового типа к дочернему используется:
- для сырых указателей - синтаксическая конструкция `dynamic_cast`;
- для умных указателей - `std::dynamic_pointer_cast` из заголовочного файла `<memory>`.

**⚠ В грамотно спроектированном коде downcast использоваться не должен.**
- Необходимость в downcast-е говорит о плохо продуманном дизайне.
- В некоторых языках (OCaml) downcast запрещён в принципе.

Пример:

```cpp
#include <memory>

using namespace std;

struct A {
  A(const A&) = delete;            // Объяснения см. в лекции и нормах
  A& operator=(const A&) = delete; // Объяснения см. в лекции и нормах
  virtual ~A() = default;          // Объяснения см. в лекции и нормах
};

struct B : public A {
};

int main() {
  // Приведение типов для сырых указателей
  {
    // ok (auto-upcast)
    A* ptr_a = new B();

    // bad (downcast): в случае неудачи вернёт nullptr
    B* ptr_b = dynamic_cast<B*>(ptr_a);

    // bad (downcast): в случае неудачи будет исключение типа std::bad_cast
    B& ref_b = dynamic_cast<B&>(*ptr_a);

    delete ptr_a;
  }

  // Приведение типов для умных указателей
  {
    // ok (auto-upcast)
    shared_ptr<A> ptr_a = make_unique<B>();

    // bad (downcast): в случае неудачи вернёт nullptr
    shared_ptr<B> ptr_b = dynamic_pointer_cast<B>(ptr_a);
  }
}
```

Нормы:
- [C.146: Use dynamic_cast where class hierarchy navigation is unavoidable](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c146-use-dynamic_cast-where-class-hierarchy-navigation-is-unavoidable)
- [C.147: Use dynamic_cast to a reference type when failure to find the required class is considered an error](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c147-use-dynamic_cast-to-a-reference-type-when-failure-to-find-the-required-class-is-considered-an-error)
- [C.148: Use dynamic_cast to a pointer type when failure to find the required class is considered a valid alternative](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c148-use-dynamic_cast-to-a-pointer-type-when-failure-to-find-the-required-class-is-considered-a-valid-alternative)
- [C.149: Use unique_ptr or shared_ptr to avoid forgetting to delete objects created using new](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c149-use-unique_ptr-or-shared_ptr-to-avoid-forgetting-to-delete-objects-created-using-new)
- [R.22: Use make_shared() to make shared_ptrs](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r22-use-make_shared-to-make-shared_ptrs)
- [R.23: Use make_unique() to make unique_ptrs](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r23-use-make_unique-to-make-unique_ptrs)
- [* R.24: Use std::weak_ptr to break cycles of shared_ptrs](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r24-use-stdweak_ptr-to-break-cycles-of-shared_ptrs)



## 1.3 Перекрытие методов и раннее связывание

TODO



## 1.4 Переопределение методов и позднее связывание

TODO

Нормы:
- [C.67: A polymorphic class should suppress public copy/move](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c67-a-polymorphic-class-should-suppress-public-copymove)
- [C.127: A class with a virtual function should have a virtual or protected destructor](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c127-a-class-with-a-virtual-function-should-have-a-virtual-or-protected-destructor)
- [C.128: Virtual functions should specify exactly one of virtual, override, or final](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c128-virtual-functions-should-specify-exactly-one-of-virtual-override-or-final)
- [C.130: For making deep copies of polymorphic classes prefer a virtual clone function instead of public copy construction/assignment](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c130-for-making-deep-copies-of-polymorphic-classes-prefer-a-virtual-clone-function-instead-of-public-copy-constructionassignment)
- [C.140: Do not provide different default arguments for a virtual function and an overrider](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c140-do-not-provide-different-default-arguments-for-a-virtual-function-and-an-overrider)
- [C.153: Prefer virtual function to casting](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c153-prefer-virtual-function-to-casting)



## 1.5 Абстрактные классы и интерфейсы

TODO

Нормы:
- [C.120: Use class hierarchies to represent concepts with inherent hierarchical structure (only)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c120-use-class-hierarchies-to-represent-concepts-with-inherent-hierarchical-structure-only)
- [C.121: If a base class is used as an interface, make it a pure abstract class](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c121-if-a-base-class-is-used-as-an-interface-make-it-a-pure-abstract-class)
- [C.126: An abstract class typically doesn’t need a user-written constructor](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c126-an-abstract-class-typically-doesnt-need-a-user-written-constructor)
- [I.25: Prefer empty abstract classes as interfaces to class hierarchies](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i25-prefer-empty-abstract-classes-as-interfaces-to-class-hierarchies)



# 2 Обязательное задание

## 2.1 Общее задание

1. Реализовать иерархию классов согласно варианту.
   - Реализовать базовый класс (абстрактный класс или интерфейс) и несколько наследников.
   - Описание варианта содержит только базовый минимум.
     При реализации предусмотреть методы чтения (методы записи - на своё усмотрение).
     По своему усмотрению можно добавить дополнительные поля и методы, если в них есть смысл.
1. Написать функцию над контейнером согласно варианту
   (в зависимости от варианта, таких функций может быть несколько):
   - функция должна принимать контейнер (`std::vector`) объектов типа базового класса и,
     может быть, какие-либо дополнительные параметры;
   - если функция ищет объект согласно предикату, то функция должна вернуть:
     - указатель на первый объект, удовлетворяющий предикату;
     - `nullptr`, если контейнер пустой или такого объекта нет.
1. Если в варианте явно не указано другое, то в `main` реализовать консольный интерфейс
   в виде меню со следующими пунктами:
   - вставка нового элемента в контейнер (запрашивается индекс вставки,
     тип создаваемого объекта и необходимые данные для создания объекта выбранного типа);
   - удаление элемента из контейнера (запрашивается индекс удаляемого элемента);
   - распечатка текущего содержимого контейнера;
   - вызов функции над контейнером согласно варианту (если таких функций несколько,
     каждая функция оформляется в виде отдельного пункта меню) и распечатка найденного объекта
     (или вывод сообщения об его отсутствии).



## 2.2 Варианты

Относительно усложнённые варианты помечены (*).
Такие пометки стоят только для удобства выбора варианта.
Дополнительные баллы за усложнённый вариант не начисляются.

1. Банковские счета `Account`.
   - Классы-наследники:
     - расчётный;
     - вкладовый;
     - кредитный.
   - Состояние:
     - ФИО владельца счета;
     - текущий баланс;
     - только для вкладового и кредитного счетов: % годовой ставки.
   - Переопределяемый метод:
     - начисление/списывание процентов за расчётный месяц:
       - для расчётного счёта - ничего не происходит;
       - для вкладового счёта - увеличение текущего баланса на величину
         `текущий баланс * %_годовой_ставки / 12`;
       - для кредитного счёта - уменьшение текущего баланса на величину
         `текущий_баланс * %_годовой_ставки / 12`, но только если `текущий_баланс < 0`.
   - Функции над контейнером:
     - начислить/списать проценты по всем счетам;
     - найти счёт с минимальным текущим балансом;
     - найти счёт с максимальным текущим балансом.

2. TODO

3. TODO

4. TODO

5. TODO

6. TODO

7. TODO

8. TODO

9. TODO

10. TODO

11. TODO

12. TODO

13. TODO

14. TODO

15. (*) Персонажи компьютерной игры `Character`.
   - Классы-наследники:
     - рыцарь;
     - ассасин;
     - берсерк.
   - Состояние:
     - количество очков жизни;
     - количество очков брони;
     - количество наносимого урона;
     - только для рыцаря: вероятность снизить урон вдвое;
     - только для ассасина: вероятность повторной атаки в тот же ход;
     - только для берсерка: вероятность утроенного урона.
   - Переопределяемые методы:
     - рассчитать наносимый урон;
     - принять урон;
     - применить "особое умение":
       - для рыцаря: увеличить собственную броню, но ослабить наносимый урон;
       - для ассасина: уворот от атаки;
       - для берсерка: увеличить урон и вероятность утроенного удара, но уменьшить броню.
   - В `main` создать двух персонажей указанного пользователем типа и смоделировать бой двух персонажей:
     за один раунд случайно выбирается либо атака, либо использование особого умения.

16. (*) TODO

17. (*) TODO

18. (*) TODO

19. (*) TODO

20. (*) TODO



## 2.3 Нормы

- [C.67: A polymorphic class should suppress public copy/move](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c67-a-polymorphic-class-should-suppress-public-copymove)
- [C.120: Use class hierarchies to represent concepts with inherent hierarchical structure (only)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c120-use-class-hierarchies-to-represent-concepts-with-inherent-hierarchical-structure-only)
- [C.121: If a base class is used as an interface, make it a pure abstract class](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c121-if-a-base-class-is-used-as-an-interface-make-it-a-pure-abstract-class)
- [C.126: An abstract class typically doesn’t need a user-written constructor](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c126-an-abstract-class-typically-doesnt-need-a-user-written-constructor)
- [C.127: A class with a virtual function should have a virtual or protected destructor](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c127-a-class-with-a-virtual-function-should-have-a-virtual-or-protected-destructor)
- [C.128: Virtual functions should specify exactly one of virtual, override, or final](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c128-virtual-functions-should-specify-exactly-one-of-virtual-override-or-final)
- [C.130: For making deep copies of polymorphic classes prefer a virtual clone function instead of public copy construction/assignment](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c130-for-making-deep-copies-of-polymorphic-classes-prefer-a-virtual-clone-function-instead-of-public-copy-constructionassignment)
- [C.133: Avoid protected data](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c133-avoid-protected-data)
- [C.140: Do not provide different default arguments for a virtual function and an overrider](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c140-do-not-provide-different-default-arguments-for-a-virtual-function-and-an-overrider)
- [C.145: Access polymorphic objects through pointers and references](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c145-access-polymorphic-objects-through-pointers-and-references)
- [C.146: Use dynamic_cast where class hierarchy navigation is unavoidable](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c146-use-dynamic_cast-where-class-hierarchy-navigation-is-unavoidable)
- [C.147: Use dynamic_cast to a reference type when failure to find the required class is considered an error](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c147-use-dynamic_cast-to-a-reference-type-when-failure-to-find-the-required-class-is-considered-an-error)
- [C.148: Use dynamic_cast to a pointer type when failure to find the required class is considered a valid alternative](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c148-use-dynamic_cast-to-a-pointer-type-when-failure-to-find-the-required-class-is-considered-a-valid-alternative)
- [C.149: Use unique_ptr or shared_ptr to avoid forgetting to delete objects created using new](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c149-use-unique_ptr-or-shared_ptr-to-avoid-forgetting-to-delete-objects-created-using-new)
- [C.152: Never assign a pointer to an array of derived class objects to a pointer to its base](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c152-never-assign-a-pointer-to-an-array-of-derived-class-objects-to-a-pointer-to-its-base)
- [C.153: Prefer virtual function to casting](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c153-prefer-virtual-function-to-casting)
- [I.25: Prefer empty abstract classes as interfaces to class hierarchies](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i25-prefer-empty-abstract-classes-as-interfaces-to-class-hierarchies)
- [R.22: Use make_shared() to make shared_ptrs](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r22-use-make_shared-to-make-shared_ptrs)
- [R.23: Use make_unique() to make unique_ptrs](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r23-use-make_unique-to-make-unique_ptrs)
- [* R.24: Use std::weak_ptr to break cycles of shared_ptrs](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r24-use-stdweak_ptr-to-break-cycles-of-shared_ptrs)



# 3 Факультативное задание

1. Продемонстрировать работоспособность вашего проекта под операционной системой семейства Linux.
1. TODO
