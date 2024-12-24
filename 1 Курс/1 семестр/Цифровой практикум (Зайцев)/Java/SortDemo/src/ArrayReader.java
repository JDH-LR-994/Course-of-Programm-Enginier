import org.apache.poi.EncryptedDocumentException;
import org.apache.poi.ss.usermodel.*;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class ArrayReader {
    ArrayReader() {
        ArrayList<Integer> intList = new ArrayList<>();
        try (
                Workbook wb = WorkbookFactory.create(new File("numdata.xls"));) {
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

        } catch (IOException |
                 EncryptedDocumentException ex) {
            System.out.println("Косяк при чтении файла " + ex.getMessage());
        }
    };
}
