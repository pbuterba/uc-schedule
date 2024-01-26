#include <iostream>
#include <string>
#include "Day.hpp"
#include "Criterion.hpp"

std::string SEMESTER = "Spring";
int WEEK = 1;

Day next(Day previousDay) {
    if(previousDay.getDayOfWeek() == 0) {
        if(SEMESTER.compare("Spring") == 0 && WEEK == 16) {
            SEMESTER = "Spring-Summer break";
            WEEK = 1;
        } else if(SEMESTER.compare("Spring-Summer break") == 0) {
            SEMESTER = "Summer";
            WEEK = 1;
        } else if(SEMESTER.compare("Summer") == 0 && WEEK == 13) {
            SEMESTER = "Summer-Fall break";
            WEEK = 1;
        } else if(SEMESTER.compare("Summer-Fall break") == 0 && WEEK == 2) {
            SEMESTER = "Fall";
            WEEK = 1;
        } else if(SEMESTER.compare("Fall") == 0 && WEEK == 16) {
            std::cout << "End of Year!" << std::endl;
            SEMESTER = "Christmas break";
            WEEK = 1;
        } else {
            WEEK = WEEK + 1;
        }
    }
    return previousDay.next();
}

Day prev(Day followingDay) {
    if(followingDay.getDayOfWeek() == 1) {
        if(SEMESTER.compare("Spring") == 0 && WEEK == 1) {
            std::cout << "Beginning of Year!" << std::endl;
            SEMESTER = "New Years";
            WEEK = -1;
        } else if(SEMESTER.compare("Spring-Summer break") == 0) {
            SEMESTER = "Spring";
            WEEK = 16;
        } else if(SEMESTER.compare("Summer") == 0 && WEEK == 1) {
            SEMESTER = "Spring-Summer break";
            WEEK = 1;
        } else if(SEMESTER.compare("Summer-Fall break") == 0 && WEEK == 1) {
            SEMESTER = "Summer";
            WEEK = 13;
        } else if(SEMESTER.compare("Fall") == 0 && WEEK == 1) {
            SEMESTER = "Summer-Fall break";
            WEEK = 2;
        } else {
            WEEK = WEEK - 1;
        }
    }
    return followingDay.previous();
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
    int criteriaScores[9];

    for(Criterion definingCriterion : criteria) {
        //Print defining criteria
        std::cout << "Defining schedule by " << definingCriterion.getName() << std::endl;
        
        //Loop once for non-leap year and once for leap year
        for(int leap = 0; leap < 2; leap++) {
            if(leap) {
                std::cout << "Leap Year" << std::endl;
            } else {
                std::cout << "Non-leap year" << std::endl;
            }

            //Set the starting variables
            Day currDay;
            if(definingCriterion.isFixedDay()) {
                currDay = Day(definingCriterion.getMonth(), definingCriterion.getDayOfWeek(), definingCriterion.getOccurrence(), leap);
                if(definingCriterion.getDayOfWeek() > -1) {
                    //Defining day should be the first occurrence of the day of the week after the given date
                    while(currDay.getDayOfWeek() != definingCriterion.getDayOfWeek()) {
                        currDay = next(currDay);
                    }
                }
            } else if(definingCriterion.getOccurrence() > 0) {
                //Todo, implement
            }
            SEMESTER = definingCriterion.getSemester();
            WEEK = definingCriterion.getTargetWeek();
        }

    }
    return 0;
}