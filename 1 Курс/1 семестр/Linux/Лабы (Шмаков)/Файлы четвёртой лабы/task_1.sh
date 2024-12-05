#!/bin/bash

#Создание переменных (без export переменные видны только в скрипт) 
#export - создание глобальной переменной, видимой в текущем скрипте и в запускаемых программах

export var1="Hi!"
export var2="My"
export var3="name is..."
#Пробелы рядом со знаком равно он не поддерживает


#Вывод переменных 
echo "var1: $var1"
echo "var2: $var2"
echo "var3: $var3"

#конкатенация
concat="$var1 $var2 $var3"
echo "concat: $concat"

#Подстрока
#Синтаксис подстрок: ${строка:с какого символа: сколько идти дальше}
substr=${concat:4}
echo "substring: $substr"

#Замена строки на другую 
#Синтаксис замены: ${строка/что заменить/что поставить}
replace=${concat/Hi!/Hello!}
echo "replace: $replace"