![](https://img.shields.io/badge/9randeza-%F000000.svg?style=for-the-badge&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) 

# Оболочка 
Решение задачи из Contest №6 k-значной логики.
>Во входном файле задана функция от 2-х переменных вектором своих значений. Найти все одноместные функции, которые она порождает с помощью операций суперпозиции, переименования переменных,
>и добавления/удаления несущественных переменных (селекторные функции порождаются любой функцией по определению).
> Каждую функцию записать в выходной файл отдельной строкой, предварительно упорядочить строки лексикографически. Количество функций не печатать. 
 ___

## Разъеснение кода
Всё основано на предыдущей программе решающую  [задачу №7](https://github.com/9randeza/TaskFromContest/tree/main) с некоторыми изменениями для работы с k-значной логикой.
1. К примеру создание селекторов на основе начальных данных.
```cpp
vector<int> generateVariable(int k, int size) {
    vector<int> variable;
    for (int i = 0; i < size; ++i) {
        variable.push_back(i % k);
    }
    return variable;
}
```
2. Или работа с индексами на основе параметра *k* нежели простой побитовый сдвиг
```cpp
        ...
        int index = x1 * k + x2;
        ch.push_back(func[index]);
    }

```
### Логика
Алгоритм ничем не отличается от предыдущей задачи и лишь слегка изменен под условия новой.
