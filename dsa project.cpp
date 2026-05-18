import java.util.*;

class Student {
    String name;
    double grade;
    double attendance;
    double studyHours;
    double score;
    String category;

    public Student(String name, double grade, double attendance, double studyHours) {
        this.name = name;
        this.grade = grade;
        this.attendance = attendance;
        this.studyHours = studyHours;
    }
}

class StudentPredictor {
    private ArrayList<Student> students = new ArrayList<>();

    private final double gradeWeight = 0.5;
    private final double attendanceWeight = 0.3;
    private final double studyHoursWeight = 0.2;

    // Calculate performance score
    private double calculateScore(Student s) {
        return (s.grade * gradeWeight)
                + (s.attendance * attendanceWeight)
                + (s.studyHours * studyHoursWeight);
    }

    // Predict category
    private String predictCategory(double score) {
        if (score >= 85)
            return "Excellent";
        else if (score >= 70)
            return "Good";
        else if (score >= 50)
            return "Average";
        else
            return "Poor";
    }

    // Add student
    public void addStudent(String name, double grade, double attendance, double studyHours) {
        Student s = new Student(name, grade, attendance, studyHours);

        s.score = calculateScore(s);
        s.category = predictCategory(s.score);

        students.add(s);

        System.out.println("\nStudent Added Successfully!");
        System.out.println("Performance Score: " + String.format("%.2f", s.score));
        System.out.println("Prediction: " + s.category);
    }

    // Display all students
    public void displayStudents() {
        if (students.isEmpty()) {
            System.out.println("\nNo student records found.");
            return;
        }

        System.out.println("\n----- Student Records -----");
        System.out.printf("%-15s %-10s %-12s %-12s %-10s %-12s\n",
                "Name", "Grade", "Attendance", "StudyHours", "Score", "Category");

        for (Student s : students) {
            System.out.printf("%-15s %-10.2f %-12.2f %-12.2f %-10.2f %-12s\n",
                    s.name, s.grade, s.attendance, s.studyHours, s.score, s.category);
        }
    }

    // Sort students by score
    public void sortByScore() {
        students.sort((a, b) -> Double.compare(b.score, a.score));
        System.out.println("\nStudents sorted by score.");
    }

    // Search student by name
    public void searchStudent(String name) {
        for (Student s : students) {
            if (s.name.equalsIgnoreCase(name)) {
                System.out.println("\nStudent Found:");
                System.out.println("Name: " + s.name);
                System.out.println("Grade: " + s.grade);
                System.out.println("Attendance: " + s.attendance);
                System.out.println("Study Hours: " + s.studyHours);
                System.out.println("Performance Score: " + String.format("%.2f", s.score));
                System.out.println("Prediction: " + s.category);
                return;
            }
        }
        System.out.println("\nStudent not found.");
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StudentPredictor predictor = new StudentPredictor();

        while (true) {
            System.out.println("\n===== Student Performance Predictor =====");
            System.out.println("1. Add Student");
            System.out.println("2. Display Students");
            System.out.println("3. Sort by Score");
            System.out.println("4. Search Student");
            System.out.println("5. Exit");
            System.out.print("Enter choice: ");

            int choice = sc.nextInt();
            sc.nextLine();

            switch (choice) {
                case 1:
                    System.out.print("Enter Name: ");
                    String name = sc.nextLine();

                    System.out.print("Enter Grade: ");
                    double grade = sc.nextDouble();

                    System.out.print("Enter Attendance: ");
                    double attendance = sc.nextDouble();

                    System.out.print("Enter Study Hours: ");
                    double studyHours = sc.nextDouble();

                    predictor.addStudent(name, grade, attendance, studyHours);
                    break;

                case 2:
                    predictor.displayStudents();
                    break;

                case 3:
                    predictor.sortByScore();
                    break;

                case 4:
                    System.out.print("Enter name to search: ");
                    String searchName = sc.nextLine();
                    predictor.searchStudent(searchName);
                    break;

                case 5:
                    System.out.println("Exiting program...");
                    sc.close();
                    return;

                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        }
    }
}
