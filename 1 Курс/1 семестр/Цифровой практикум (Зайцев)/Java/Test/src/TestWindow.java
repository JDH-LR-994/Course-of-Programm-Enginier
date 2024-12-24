import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;


public class TestWindow extends JFrame implements ActionListener {
    private JLabel label_cat = new JLabel("Каталог с данными:");
    private JLabel label_group = new JLabel("Шаблон групп:");
    private JLabel label_par = new JLabel("Параметры:");
    private JPanel north = new JPanel();
    private JPanel north_north = new JPanel();
    private JPanel north_center = new JPanel();
    private JPanel north_south = new JPanel();
    private JPanel east = new JPanel();
    private JPanel south = new JPanel();
    private JPanel west = new JPanel();
    private JPanel center = new JPanel();
    private JScrollPane jsp = new JScrollPane(center);
    private JTextField tf1 = new JTextField();
    private JTextField tf2 = new JTextField();
    private JTextField tf3 = new JTextField();
    private JTextArea ta1 = new JTextArea(20, 30);

    private JButton chooseFileButton = new JButton("Выбрать...");
    private JButton help = new JButton("Помощь");
    private JButton grade = new JButton("Пересчитать оценки");
    private JButton exit = new JButton("Выход");

    private JLabel pathLabel = new JLabel();


    public TestWindow(String title) {
        super(title);
        Toolkit theKit = this.getToolkit();
        Dimension winSize = theKit.getScreenSize();
        this.setBounds(winSize.width / 4, winSize.height / 4, winSize.width / 2, winSize.height / 2);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


        // раскладываем панели

        //
        south.add(tf1);
        center.setLayout(new BorderLayout());
        center.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.white, 3),
                BorderFactory.createEmptyBorder(10, 10, 10, 10)));

        center.add(ta1, BorderLayout.CENTER);
        west.setLayout(new GridLayout(12, 1));

        north.setLayout(new BorderLayout());
        north.add(north_north, BorderLayout.NORTH);
        north.add(north_center, BorderLayout.CENTER);
        north.add(north_south, BorderLayout.SOUTH);
        north_center.setLayout(new BorderLayout());
        north_north.setLayout(new BorderLayout());
        north_south.setLayout(new BorderLayout());
        north_north.add(pathLabel);
        north_north.add(chooseFileButton, BorderLayout.EAST);
        north_north.add(tf1);
        north_north.add(label_cat, BorderLayout.WEST);
        north_center.add(label_group, BorderLayout.WEST);
        north_center.add(tf2);
        north_south.add(label_par, BorderLayout.WEST);
        north_south.add(tf3);


        chooseFileButton.addActionListener(this);
        this.add(north, BorderLayout.NORTH);
        this.add(south, BorderLayout.SOUTH);
        this.add(east, BorderLayout.EAST);
        this.add(west, BorderLayout.WEST);
        this.add(center, BorderLayout.CENTER);

        this.setVisible(true);
        south.setLayout(new BorderLayout());
        south.add(help, BorderLayout.WEST);
        south.add(grade, BorderLayout.CENTER);
        south.add(exit, BorderLayout.EAST);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        JFileChooser fch = new JFileChooser();
        switch (fch.showOpenDialog(this)) {
            case JFileChooser.APPROVE_OPTION:
                try (BufferedReader br = new BufferedReader(
                        new FileReader(fch.getSelectedFile()))) {
                    String s;
                    while ((s = br.readLine()) != null) {
                        ta1.setText(ta1.getText() + "\n" + s);
                    }

                } catch (IOException ex) {
                    Logger.getLogger(TestWindow.class.getName()).log(Level.SEVERE, null, ex);
                }
                break;
            default:
                ;
        }
    }
}
