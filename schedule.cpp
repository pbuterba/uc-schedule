#include <iostream>
#include <string>
#include "Day.hpp"
#include "Criterion.hpp"

std::string semester = "Spring";
int week = 1;

Day next(Day previousDay) {
    if(previousDay.getDayOfWeek() == 0) {
        if(semester.compare("Spring") == 0 && week == 16) {
            semester = "Spring-Summer break";
            week = 1;
        } else if(semester.compare("Spring-Summer break") == 0) {
            semester = "Summer";
            week = 1;
        } else if(semester.compare("Summer") == 0 && week == 13) {
            semester = "Summer-Fall break";
            week = 1;
        } else if(semester.compare("Summer-Fall break") == 0 && week == 2) {
            semester = "Fall";
            week = 1;
        } else if(semester.compare("Fall") == 0 && week == 16) {
            std::cout << "End of Year!" << std::endl;
            semester = "Christmas break";
            week = 1;
        } else {
            week = week + 1;
        }
    }
    return previousDay.next();
}

int main() {
    Criterion criteria[] = {
        Criterion("Spring Semester starts on first Monday on or after 1/6", true, 1, 6, 1, "Spring", 1, 1),
        Criterion("MLK Day in Spring Semester Week 2", true, 1, 15, 1, "Spring", 2, 1),
        Criterion("Memorial Day in Summer Semester Week 4", false, 5, 0, 1, "Summer", 4, 0.5),
        Criterion("Independence Day in Summer Semester Week 9", true, 7, 4, -1, "Summer", 9, 0.5),
        Criterion("Fall Semester Week 1 ends on last Friday in August", false, 8, 0, 5, "Fall", 1, 1),
        Criterion("Labor Day in Fall Semester Week 3", false, 9, 1, 1, "Fall", 3, 1),
        Criterion("Columbus Day in Fall Semester Week 8", false, 10, 2, 1, "Fall", 8, 1),
        Criterion("Thanksgiving in Fall Semester Week 14", false, 11, 4, 4, "Fall", 14, 1),
        Criterion("Fall Semester Exams start on first Monday of December", false, 12, 1, 1, "Fall", 16, 1)
    };
    return 0;
}