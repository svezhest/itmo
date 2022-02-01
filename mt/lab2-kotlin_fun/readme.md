### Вариант 9. Описание заголовка функции в Kotlin

Заголовок функции в Kotlin. Заголовок начинается ключевым сло-
вом “fun”, далее идет имя функции, скобка, несколько описаний аргумен-
тов через запятую, затем может идти двоеточие и имя возвращаемого
типа.
Используйте один терминал для всех имен переменных. Используйте
один терминал для ключевых слов fun и т. п. (не несколько ‘f’, ‘u’, ‘n’).

Пример: `fun printSum(a: Int, b: Int): Unit`

Используем следующие правила для переменных:

    Names can contain letters, digits, and underscores
    Names should start with a letter
    Names can also begin with _ (but we will not use it in this tutorial)
    Names are case sensitive ("myVar" and "myvar" are different variables)
    Names should start with a lowercase letter and it cannot contain whitespace
    Reserved words (like Kotlin keywords, such as var or String) cannot be used as names

Для типов считаем что имя типа обязано начинаться с заглавной буквы

В задании говорится использовать 1 терминал для имен переменных.

````
S  -> fun N ( V ) : G
V  -> eps
V  -> N : G V'
V' -> , N : G V'
V' -> eps
G -> T C
C -> eps
C -> < L >
L -> eps
L -> G
L -> G, L
N  is terminal for word
T  is terminal for type
````

First / Follow

````
       First                             Follow
S   |  fun                           |   $
V   |  n eps                         |   )
V'  |  , eps                         |   ) 
G   |  T                             |   eps , > $ 
C   |  < eps                         |   eps , > $
L   |  T eps                         |   > 
````

Описание

````
S   |   Стартовый нетерминал
N   |   Имя переменной (терминал)
V   |   Пара имя + тип (начало)
V'  |   Пара имя + тип (продолжение)
T   |   Тип (терминал)
````

