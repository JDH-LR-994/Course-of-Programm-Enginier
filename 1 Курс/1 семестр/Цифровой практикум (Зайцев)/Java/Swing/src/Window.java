import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

//Класс окно наследуется от JFrame и имплементирует ActionListener
public class Window extends JFrame implements ActionListener {
    //Число, которое потом считаем
    private int number;

    //Создаём ввод текста (размер 10 - ?)
    private final JTextField inputField = new JTextField(10);

    //Создаём область для вывода действий
    private final JTextArea centerArea = new JTextArea();

    //Создаётся окно с заголовком title
    public Window(String title) {
        super(title);
        //Ставим размеры окна
        setSize(600, 500);

        //Выходим, если нажмём на "крестик"
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Размещаем окно по центру
        this.setLocationRelativeTo(null);

        //Смотрим какой Layout изначально стоит
        //System.out.println(this.getLayout());

        //Добавляем панель на экран
        //Создаём панель
        JPanel north = new JPanel();
        this.add(north, BorderLayout.NORTH);

        //Делаем её серой
        north.setBackground(Color.GRAY);


        //Создать надпись и добавить
        JLabel inputLabel = new JLabel("Введите число");
        north.add(inputLabel);

        //Добавляем ввод текста на панель
        north.add(inputField);

        //Добавляем отлов действий
        inputField.addActionListener(this);

        //Добавляем комментарий к вызову
        inputField.setActionCommand("inputField");

        //Добавляем область для вывода ошибок в центр
        this.add(centerArea, BorderLayout.CENTER);

        //Меняем цвет
        centerArea.setBackground(Color.CYAN);

        //Писать мы в нём не можем
        centerArea.setEditable(false);

        //Добавляем кнопку
        JButton startButton = new JButton("Нажми меня");
        north.add(startButton);

        //Добавляем ActionListener на кнопку
        startButton.addActionListener(this);

        //Добавляем комментарий к команде
        startButton.setActionCommand("startButton");

        //Делаем так, чтобы окно было видно
        this.setVisible(true);
    }

    //Реализуем метод для обработки ввода
    @Override
    public void actionPerformed(ActionEvent e) {
        //смотрим на команду
        String command = e.getActionCommand();
        //Берём то, что вписали
        String input = inputField.getText();
        switch (command) {
            //Если просто нажали Enter
            case "inputField":
                //Пробуем перевести в число и вывести
                try {
                    number = Integer.parseInt(input);
                    centerArea.append("Прочитано число: " + number + '\n');
                } catch (NumberFormatException ex) {
                    centerArea.append("Не понял. Ты это за число принял: " + input + "\n");
                }
                break;
            //Если нажали на кнопку
            case "startButton":
                //Проверяем на пустой ввод
                if (number == 0) {
                    centerArea.append("Не, дружок, я не такой глупый. Попробуй ввести число дла начала\n");
                } else {
                    try {
                        number = Integer.parseInt(input);
                        //Решение задач про минимальную сумму чисел с одинаковой суммой цифр
                        HardComputing(number);
                    } catch (NumberFormatException ex) {
                        centerArea.append("Не понял. Ты это за число принял: " + input + "\n");
                    }
                }
        }
    }

    //Сложные вычисления
    void HardComputing(int x) {
        //Списки для ввода больше 10
        ArrayList<Integer> first = new ArrayList<>();
        ArrayList<Integer> second = new ArrayList<>();
        //Проверка на 1 и числа меньше или равные 0
        boolean is_negative = x <= 0;
        boolean isOne = x == 1;
        if (isOne) {
            centerArea.append("1 = 1");
        }
        //Если число меньше десяти
        if (!is_negative && !isOne && x <= 10) {
            int start = x - 1; //Стартуем с (число - 1) и прибавляем по 9 до победного
            int sum = start;
            for (int i = 0; i < x; i++) {
                centerArea.append(Integer.toString(start));
                if (x - 1 != i) {
                    start += 9;
                    sum += start;
                    centerArea.append(" + ");
                } else {
                    centerArea.append(" = " + sum);
                }
            }
        }
        //Если число больше 10
        if (x > 10) {
            //Считаем последовательности начиная с 9 и 19 (Напишите на Python простой перебор и увидите почему старты такие)
            int start_first = 9;
            int start_second = 19;
            //Сумма последовательностей
            long sum_first = 0;
            long sum_sec = 0;
            //Перебираем последовательности (необходимо для оптимального старта)
            for (int i = 10; i < x + 1; i++) {
                //Считаем сумму цифр каждого старта
                int first_sum_dig = calculateSumOfDigits(start_first);
                int second_sum_dig = calculateSumOfDigits(start_second);
                //перебираем все числа, пока не заполним оба списка i количеством элементов
                for (int j = 0; first.size() != i || second.size() != i; j++) {
                    //Если число подходит для первой последовательности и списке меньше i элементов
                    if (calculateSumOfDigits(j) == first_sum_dig && first.size() != i) {
                        first.add(j);
                        sum_first += j;
                    }
                    //Аналогично для второго
                    if (calculateSumOfDigits(j) == second_sum_dig && second.size() != i) {
                        second.add(j);
                        sum_sec += j;
                    }
                }
                //Если второй старт выгоднее
                if (sum_first > sum_sec) {
                    start_first = start_second;
                    start_second += (int) Math.pow(10, (Integer.toString(start_second).length() - 1)); //Потому что можем уйти в 100
                }
                //Если мы ещё не дошли до рассмотрения нужного ввода, то чистим всё
                if (x != i) {
                    first.clear();
                    second.clear();
                    sum_sec = sum_first = 0;
                }
            }
            //Если первая выгоднее, то выводим её
            if (sum_first < sum_sec) {
                for (int i = 0; i < first.size(); i++) {
                    centerArea.append(Integer.toString(first.get(i)));
                    if (i + 1 != first.size()) {
                        centerArea.append(" + ");
                    }
                }
                centerArea.append(" = " + sum_first);
            } else {
                for (int i = 0; i < second.size(); i++) {
                    centerArea.append(Integer.toString(second.get(i)));
                    if (i + 1 != second.size()) {
                        centerArea.append(" + ");
                    }
                }
                centerArea.append(" = " + sum_sec);
            }
        }
        centerArea.append("\n");
    }

    //Считаем сумму цифр
    private static int calculateSumOfDigits(int number) {
        int sum = 0;
        while (number > 0) {
            sum += number % 10;
            number /= 10;
        }
        return sum;
    }
}
