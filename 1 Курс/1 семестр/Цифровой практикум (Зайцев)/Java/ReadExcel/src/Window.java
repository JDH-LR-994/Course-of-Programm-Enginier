import org.apache.poi.EncryptedDocumentException;
import org.apache.poi.ss.usermodel.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class Window extends JFrame implements ActionListener {
    int variant = 13;

    //Создание меню бара
    JMenuBar menuBar = new JMenuBar();

    //Создание меню
    JMenu fileMenu = new JMenu("File");
    //Вкладки в меню
    JMenuItem openFile = new JMenuItem("Open file");
    JMenuItem quitItem = new JMenuItem("Quit");
    //Метка
    JLabel statusLabel = new JLabel("Пока всё тихо");

    //Имя приложение
    String name = "Excel Reader";

    //Конструктор
    public Window() {
        initialize();
    }

    //Инициализатор
    private void initialize() {
        this.setSize(600, 500); //Размеры окна
        setTitle(name); //Дали имя приложению
        this.setDefaultCloseOperation(EXIT_ON_CLOSE); //Действие при нажатии на крестик
        this.setLocationRelativeTo(null); //Размещаем по центру

        //Создаём меню и добавляем в него объектов
        setJMenuBar(menuBar);
        //Добавляем вкладки в меню и предметы в него
        menuBar.add(fileMenu);
        fileMenu.add(quitItem);
        fileMenu.add(openFile);

        //Добавляем метку вниз
        this.add(statusLabel, BorderLayout.SOUTH);
        //Добавляем обработчик событий
        quitItem.addActionListener(this);
        openFile.addActionListener(this);
        //Сделать все изменения видимыми
        this.setVisible(true);
    }

    //Обработчик предметов меню
    @Override
    public void actionPerformed(ActionEvent e) {
        statusLabel.setText("Было выбрано меню " + e.getActionCommand()); //Показываем в метке какой предмет выбрали
        int ans = 0; //Переменная для ответа
        //обрабатываем команды
        switch (e.getActionCommand()) {
            case "Quit":
                System.exit(0); //Если выбрали Quit, то выходим из меню
            case "Open file": //Если открыли файл

                JFileChooser fileChooser = new JFileChooser(); //Создаём объект для выбора файла
                //Выводим окно для выбора файла
                switch (fileChooser.showOpenDialog(this)) {
                    //Если файл выбрали
                    case JFileChooser.APPROVE_OPTION: {
                        //Пытаемся его открыть
                        try (Workbook workbook = WorkbookFactory.create(fileChooser.getSelectedFile());) {
                            //В метке выводим имя первого листа (на вход предполагается .xls)
                            statusLabel.setText("Файл открыт, первый лист: " + workbook.getSheetAt(0).getSheetName());

                            //Берём первый лист в файле (предполагается, что на вход поступил *.xls
                            Sheet sh = workbook.getSheetAt(0);
                            int rowNum = 0;
                            //перебираем строки
                            for (Row row : sh) {
                                //Если первая строка, то мы её пропускаем (там написан вариант, который мы не сможем обработать
                                if (rowNum++ == 0) {
                                    continue;
                                }
                                //Превращаем значение ячейки в int
                                int x = (int) row.getCell(variant).getNumericCellValue();
                                int tr = count(x);
                                //Если включено меньше 3, то это число подходит (задание без подвохов)
                                if (tr <= 3) {
                                    ans++;
                                }
                            }
                            statusLabel.setText("Ответ: " + ans);
                        } catch (IOException ex) {
                            statusLabel.setText("Ошибка чтения файла");
                        } catch (EncryptedDocumentException ex) {
                            statusLabel.setText("Проблема с шифрованием файла");
                        }
                        break;
                    }
                    default:
                        statusLabel.setText("Файл не выбран");
                }
        }
    }

    //Функция для подсчёта байтов
    public static int count(int x) {
        int count = 0;
        while (x != 0) {
            count += (x % 2);
            x /= 2;
        }
        return count;
    }
}
