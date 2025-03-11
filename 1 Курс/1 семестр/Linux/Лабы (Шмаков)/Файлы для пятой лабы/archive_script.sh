#!/bin/bash

# Проверка количества аргументов
if [ "$#" -ne 3 ]; then
    echo "Использование: $0 <каталог> <архив> <интервал>"
    exit 1
fi

DIR=$1          # Каталог для архивации
ARCHIVE=$2      # Имя архива
INTERVAL=$3     # Интервал архивации в секундах

# Бесконечный цикл архивации
while true; do
    tar -czf "$ARCHIVE-$(date +%Y%m%d%H%M%S).tar.gz" "$DIR"
    echo "Архив создан: $ARCHIVE-$(date +%Y%m%d%H%M%S).tar.gz"
    sleep "$INTERVAL"
done