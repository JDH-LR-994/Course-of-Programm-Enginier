import java.util.Comparator;

public class Student implements Comparable<Student>{

    String name;
    int gameHoursPerYear;
    Integer studyHoursPerYear;
    short iq;

    public static Comparator<Student> gameHour = (Student o1, Student o2) -> o1.gameHoursPerYear - o2.gameHoursPerYear;
    public static Comparator<Student> iqSort = (Student o1, Student o2) -> o1.iq - o2.iq;


    public Student(String name, Integer studyHoursPerYear, int gameHoursPerYear,  short iq) {
        this.studyHoursPerYear = studyHoursPerYear;
        this.gameHoursPerYear = gameHoursPerYear;
        this.name = name;
        this.iq = iq;
    }


    @Override
    public int compareTo(Student o) {
        return -this.name.compareTo(o.name);
    }

    @Override
    public String toString() {
        return "name: " + name + " gameHoursPerYear: " + gameHoursPerYear + " studyHoursPerYear: " + studyHoursPerYear +" iq: " + iq;
    }
}
