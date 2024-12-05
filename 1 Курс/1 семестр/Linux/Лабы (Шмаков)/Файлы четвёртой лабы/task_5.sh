#Проверка на наличие двух аргументов
if [ "$#" -ne 2 ]; then
	echo "Использовано: $0 последовательность файл_результат"
	exit 1
fi

sequence=$1
result_file=$2

> "$result_file"


grep -r -n "$sequence" --include="*.txt" . | awk -F: '{print $1 ": строка " $2 }' >> "$result_file"

echo "Результаты поиска записаны в файл $result_file"


