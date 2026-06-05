import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

// =====================================================
// TEACHER CLASS
// =====================================================

class Teacher {

    private String name;
    private String subject;

    public Teacher(
            String name,
            String subject) {

        this.name = name;
        this.subject = subject;
    }

    public String getName() {

        return name;
    }

    public String getSubject() {

        return subject;
    }
}

// =====================================================
// ROOM CLASS
// =====================================================

class Room {

    private int roomNo;

    public Room(int roomNo) {

        this.roomNo = roomNo;
    }

    public int getRoomNo() {

        return roomNo;
    }
}

// =====================================================
// SCHEDULE CLASS
// =====================================================

class Schedule {

    private String type;
    private String department;
    private String day;
    private String time;

    private Teacher teacher;
    private Room room;

    public Schedule(
            String type,
            String department,
            String day,
            String time,
            Teacher teacher,
            Room room) {

        this.type = type;
        this.department = department;
        this.day = day;
        this.time = time;

        this.teacher = teacher;
        this.room = room;
    }

    public String getType() {

        return type;
    }

    public String getDepartment() {

        return department;
    }

    public String getDay() {

        return day;
    }

    public String getTime() {

        return time;
    }

    public Teacher getTeacher() {

        return teacher;
    }

    public Room getRoom() {

        return room;
    }
}

// =====================================================
// SCHEDULE MANAGER
// =====================================================

class ScheduleManager {

    ArrayList<Schedule> schedules;

    public ScheduleManager() {

        schedules = new ArrayList<>();
    }

    // =====================================================
    // CHECK CLASS CLASH
    // =====================================================

    public boolean hasClash(
            Schedule newSchedule) {

        for (Schedule s : schedules) {

            // ===== SAME DAY + SAME TIME =====
            if (s.getDay().equals(
                    newSchedule.getDay())
                    &&
                    s.getTime().equals(
                            newSchedule.getTime())) {

                // ===== TEACHER CLASH =====
                if (s.getTeacher()
                        .getName()
                        .equalsIgnoreCase(
                                newSchedule
                                        .getTeacher()
                                        .getName())) {

                    JOptionPane.showMessageDialog(
                            null,
                            "Teacher Clash Detected!");

                    return true;
                }

                // ===== CLASS CLASH =====
                if (s.getDepartment()
                        .equals(
                                newSchedule
                                        .getDepartment())
                        &&
                        s.getType()
                                .equals(
                                        newSchedule
                                                .getType())) {

                    JOptionPane.showMessageDialog(
                            null,
                            "Class Clash Detected!\n"
                                    +
                                    "Department already has a class/exam at this time.");

                    return true;
                }

                // ===== ROOM CLASH =====
                if (s.getRoom()
                        .getRoomNo()
                        ==
                        newSchedule
                                .getRoom()
                                .getRoomNo()) {

                    JOptionPane.showMessageDialog(
                            null,
                            "Room Clash Detected!");

                    return true;
                }
            }
        }

        return false;
    }

    // =====================================================
    // AUTO ROOM ALLOCATION
    // =====================================================

    public int allocateRoom(
            String day,
            String time) {

        int room = 201;

        while (true) {

            boolean used = false;

            for (Schedule s : schedules) {

                if (s.getDay().equals(day)
                        &&
                        s.getTime().equals(time)
                        &&
                        s.getRoom().getRoomNo()
                                == room) {

                    used = true;
                    break;
                }
            }

            if (!used) {

                return room;
            }

            room++;
        }
    }

    // =====================================================
    // ADD SCHEDULE
    // =====================================================

    public boolean addSchedule(
            Schedule s) {

        if (!hasClash(s)) {

            schedules.add(s);

            return true;
        }

        return false;
    }

    public ArrayList<Schedule> getSchedules() {

        return schedules;
    }
}

// =====================================================
// DISPLAY WINDOW
// =====================================================

class DisplayWindow extends JFrame {

    public DisplayWindow(
            ArrayList<Schedule> schedules,
            String department,
            String type) {

        setTitle(
                department + " " + type);

        setSize(850, 500);

        setLocationRelativeTo(null);

        String columns[] = {

                "Department",
                "Type",
                "Teacher",
                "Subject",
                "Room",
                "Day",
                "Time"
        };

        String data[][] =
                new String[schedules.size()][7];

        int index = 0;

        for (Schedule s : schedules) {

            if (s.getDepartment()
                    .equals(department)
                    &&
                    s.getType()
                            .equals(type)) {

                data[index][0] =
                        s.getDepartment();

                data[index][1] =
                        s.getType();

                data[index][2] =
                        s.getTeacher()
                                .getName();

                data[index][3] =
                        s.getTeacher()
                                .getSubject();

                data[index][4] =
                        String.valueOf(
                                s.getRoom()
                                        .getRoomNo());

                data[index][5] =
                        s.getDay();

                data[index][6] =
                        s.getTime();

                index++;
            }
        }

        JTable table =
                new JTable(data, columns);

        table.setRowHeight(30);

        table.setFont(
                new Font(
                        "Segoe UI",
                        Font.PLAIN,
                        15));

        table.getTableHeader().setFont(
                new Font(
                        "Segoe UI",
                        Font.BOLD,
                        16));

        JScrollPane pane =
                new JScrollPane(table);

        add(pane);

        setVisible(true);
    }
}

// =====================================================
// MAIN GUI
// =====================================================

class MainGUI extends JFrame
        implements ActionListener {

    JComboBox<String> typeBox;
    JComboBox<String> deptBox;
    JComboBox<String> dayBox;

    JTextField teacherField;
    JTextField subjectField;
    JTextField timeField;

    JButton addButton;
    JButton displayButton;
    JButton clearButton;

    ScheduleManager manager;

    public MainGUI() {

        manager =
                new ScheduleManager();

        // =====================================================
        // FRAME
        // =====================================================

        setTitle(
                "SMART UNIVERSITY SCHEDULER");

        setSize(1200, 750);

        setLocationRelativeTo(null);

        setLayout(new BorderLayout());

        setDefaultCloseOperation(
                EXIT_ON_CLOSE);

        // ===== MAIN PANEL =====
        JPanel mainPanel =
                new JPanel(
                        new BorderLayout());

        mainPanel.setBackground(
                new Color(
                        245,
                        247,
                        252));

        // =====================================================
        // HEADER
        // =====================================================

        JPanel headerPanel =
                new JPanel();

        headerPanel.setPreferredSize(
                new Dimension(
                        1200,
                        90));

        headerPanel.setBackground(
                new Color(
                        20,
                        40,
                        90));

        JLabel heading =
                new JLabel(
                        "SMART UNIVERSITY SCHEDULER");

        heading.setForeground(
                Color.WHITE);

        heading.setFont(
                new Font(
                        "Segoe UI",
                        Font.BOLD,
                        34));

        headerPanel.add(heading);

        mainPanel.add(
                headerPanel,
                BorderLayout.NORTH);

        // =====================================================
        // CENTER PANEL
        // =====================================================

        JPanel centerPanel =
                new JPanel(
                        new GridBagLayout());

        centerPanel.setBackground(
                new Color(
                        245,
                        247,
                        252));

        // =====================================================
        // FORM PANEL
        // =====================================================

        JPanel formPanel =
                new JPanel();

        formPanel.setLayout(
                new GridLayout(
                        8,
                        2,
                        18,
                        18));

        formPanel.setBackground(
                Color.WHITE);

        formPanel.setBorder(
                BorderFactory.createCompoundBorder(

                        BorderFactory.createLineBorder(
                                new Color(
                                        220,
                                        220,
                                        220)),

                        BorderFactory.createEmptyBorder(
                                35,
                                35,
                                35,
                                35)));

        Font labelFont =
                new Font(
                        "Segoe UI",
                        Font.BOLD,
                        18);

        Font fieldFont =
                new Font(
                        "Segoe UI",
                        Font.PLAIN,
                        17);

        // =====================================================
        // LABELS
        // =====================================================

        JLabel typeLabel =
                new JLabel(
                        "Schedule Type");

        JLabel deptLabel =
                new JLabel(
                        "Department");

        JLabel teacherLabel =
                new JLabel(
                        "Teacher Name");

        JLabel subjectLabel =
                new JLabel(
                        "Subject");

        JLabel dayLabel =
                new JLabel(
                        "Day");

        JLabel timeLabel =
                new JLabel(
                        "Time");

        typeLabel.setFont(labelFont);
        deptLabel.setFont(labelFont);
        teacherLabel.setFont(labelFont);
        subjectLabel.setFont(labelFont);
        dayLabel.setFont(labelFont);
        timeLabel.setFont(labelFont);

        // =====================================================
        // COMBO BOXES
        // =====================================================

        String types[] = {

                "Class Schedule",
                "Exam Schedule"
        };

        typeBox =
                new JComboBox<>(types);

        String departments[] = {

                "CS",
                "IT"
        };

        deptBox =
                new JComboBox<>(departments);

        String days[] = {

                "Monday",
                "Tuesday",
                "Wednesday",
                "Thursday",
                "Friday"
        };

        dayBox =
                new JComboBox<>(days);

        typeBox.setFont(fieldFont);
        deptBox.setFont(fieldFont);
        dayBox.setFont(fieldFont);

        // =====================================================
        // TEXTFIELDS
        // =====================================================

        teacherField =
                new JTextField();

        subjectField =
                new JTextField();

        timeField =
                new JTextField();

        teacherField.setFont(fieldFont);
        subjectField.setFont(fieldFont);
        timeField.setFont(fieldFont);

        // =====================================================
        // BUTTONS
        // =====================================================

        addButton =
                new JButton(
                        "ADD SCHEDULE");

        displayButton =
                new JButton(
                        "DISPLAY");

        clearButton =
                new JButton(
                        "CLEAR");

        Font buttonFont =
                new Font(
                        "Segoe UI",
                        Font.BOLD,
                        17);

        addButton.setFont(buttonFont);
        displayButton.setFont(buttonFont);
        clearButton.setFont(buttonFont);

        addButton.setBackground(
                new Color(
                        0,
                        123,
                        255));

        displayButton.setBackground(
                new Color(
                        255,
                        140,
                        0));

        clearButton.setBackground(
                new Color(
                        220,
                        53,
                        69));

        addButton.setForeground(
                Color.WHITE);

        displayButton.setForeground(
                Color.WHITE);

        clearButton.setForeground(
                Color.WHITE);

        // =====================================================
        // ADD COMPONENTS
        // =====================================================

        formPanel.add(typeLabel);
        formPanel.add(typeBox);

        formPanel.add(deptLabel);
        formPanel.add(deptBox);

        formPanel.add(teacherLabel);
        formPanel.add(teacherField);

        formPanel.add(subjectLabel);
        formPanel.add(subjectField);

        formPanel.add(dayLabel);
        formPanel.add(dayBox);

        formPanel.add(timeLabel);
        formPanel.add(timeField);

        formPanel.add(addButton);
        formPanel.add(displayButton);

        formPanel.add(new JLabel(""));
        formPanel.add(clearButton);

        centerPanel.add(formPanel);

        mainPanel.add(
                centerPanel,
                BorderLayout.CENTER);

        add(mainPanel);

        // =====================================================
        // ACTIONS
        // =====================================================

        addButton.addActionListener(this);

        displayButton.addActionListener(this);

        clearButton.addActionListener(this);

        setVisible(true);
    }

    // =====================================================
    // ACTION
    // =====================================================

    public void actionPerformed(
            ActionEvent e) {

        // =====================================================
        // ADD BUTTON
        // =====================================================

        if (e.getSource()
                == addButton) {

            String type =
                    typeBox.getSelectedItem()
                            .toString();

            String department =
                    deptBox.getSelectedItem()
                            .toString();

            String teacherName =
                    teacherField.getText();

            String subject =
                    subjectField.getText();

            String day =
                    dayBox.getSelectedItem()
                            .toString();

            String time =
                    timeField.getText();

            if (teacherName.isEmpty()
                    ||
                    subject.isEmpty()
                    ||
                    time.isEmpty()) {

                JOptionPane.showMessageDialog(
                        null,
                        "Please Fill All Fields");

                return;
            }

            // =====================================================
            // AUTO ROOM
            // =====================================================

            int roomNo =
                    manager.allocateRoom(
                            day,
                            time);

            Teacher teacher =
                    new Teacher(
                            teacherName,
                            subject);

            Room room =
                    new Room(roomNo);

            Schedule schedule =
                    new Schedule(
                            type,
                            department,
                            day,
                            time,
                            teacher,
                            room);

            boolean added =
                    manager.addSchedule(
                            schedule);

            if (added) {

                JOptionPane.showMessageDialog(
                        null,
                        type
                                + " Added Successfully!\n"
                                +
                                "Room Allocated: "
                                + roomNo);

                clearFields();
            }
        }

        // =====================================================
        // DISPLAY BUTTON
        // =====================================================

        if (e.getSource()
                == displayButton) {

            String options[] = {

                    "CS Class Schedule",
                    "IT Class Schedule",
                    "CS Exam Schedule",
                    "IT Exam Schedule"
            };

            String choice =
                    (String)
                            JOptionPane.showInputDialog(
                                    null,
                                    "Select Schedule To Display",
                                    "DISPLAY",
                                    JOptionPane.PLAIN_MESSAGE,
                                    null,
                                    options,
                                    options[0]);

            if (choice != null) {

                if (choice.equals(
                        "CS Class Schedule")) {

                    new DisplayWindow(
                            manager.getSchedules(),
                            "CS",
                            "Class Schedule");
                }

                else if (choice.equals(
                        "IT Class Schedule")) {

                    new DisplayWindow(
                            manager.getSchedules(),
                            "IT",
                            "Class Schedule");
                }

                else if (choice.equals(
                        "CS Exam Schedule")) {

                    new DisplayWindow(
                            manager.getSchedules(),
                            "CS",
                            "Exam Schedule");
                }

                else if (choice.equals(
                        "IT Exam Schedule")) {

                    new DisplayWindow(
                            manager.getSchedules(),
                            "IT",
                            "Exam Schedule");
                }
            }
        }

        // =====================================================
        // CLEAR BUTTON
        // =====================================================

        if (e.getSource()
                == clearButton) {

            clearFields();
        }
    }

    // =====================================================
    // CLEAR
    // =====================================================

    public void clearFields() {

        teacherField.setText("");

        subjectField.setText("");

        timeField.setText("");
    }
}

// =====================================================
// MAIN CLASS
// =====================================================

public class Main {

    public static void main(
            String[] args) {

        new MainGUI();
    }
}
