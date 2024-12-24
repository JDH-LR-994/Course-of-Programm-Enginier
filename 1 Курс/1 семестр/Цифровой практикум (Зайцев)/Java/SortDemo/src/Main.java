import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

import org.apache.poi.EncryptedDocumentException;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.ss.usermodel.WorkbookFactory;

public class Main {

    public static void main(String[] args) {
//        ArrayList<Integer> intList = new ArrayList<>();
//        intList.add(5); // автоупаковка int -> Integer
//        intList.add(3); intList.add(1); // 5,3,1
//        Collections.sort(intList);
//        for(Integer x: intList) {
//            System.out.print(x + "\t");
//        }
        ArrayList<Student> stl = new ArrayList<>();
        stl.add(new Student("Вася", 500, 1000, (short) 150));
        stl.add(new Student("Никита", 700, 2100, (short) 170));
        stl.add(new Student("Алиса", 250, 2000, (short) 172));
        stl.add(new Student("Костик", 800, 2200, (short) 171));

        System.out.println(stl.get(1).compareTo(stl.get(2)));
        Collections.sort(stl, Student.iqSort);
        for (Student s : stl) {
            System.out.println(s);
        }
        // =============
        ArrayList<Integer> intList = new ArrayList<>();
        try (Workbook wb = WorkbookFactory.create(new File("numdata.xls"));) {
            Sheet sh = wb.getSheet("Sheet3");
            int lineCounter = 0;
            for (Row row : sh) {
                if (lineCounter++ < 1) {
                    continue;
                }
                for (Cell cell : row) {
                    int x = (int) cell.getNumericCellValue();
                    intList.add(x); // автоупаковка int -> Integer
                }
            }
            System.out.println("Длина списка чисел = " + intList.size());
            for (int i = 0; i < 10; i++) {
                System.out.println("\t" + intList.get(i));
            }
            long time1 = System.currentTimeMillis();
            Collections.sort(intList);
            long time2 = System.currentTimeMillis();
            System.out.println("Время сортировки: " + (time2 - time1));
        } catch (IOException | EncryptedDocumentException ex) {
            System.out.println("Косяк при чтении файла " + ex.getMessage());
        }

    }

}