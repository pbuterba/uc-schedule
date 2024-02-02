#include <iostream>
#include <string>
#include "Day.hpp"
#include "Criterion.hpp"

std::string SEMESTER = "Spring";
int WEEK = 1;
int NUM_CRITERIA = 9;
std::string DAY_OF_WEEK_NAMES[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
std::string MONTH_NAMES[] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

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

void dateAnnouncement(Criterion criterion, Day day) {
    std::string output = criterion.getName() + " " + day.toString() + " (" + SEMESTER + " Semester Week " + std::to_string(WEEK) + ")";
    std::cout << output;
}

int main() {
    Criterion criteria[] = {
        Criterion("Spring Semester starts on", "the first Monday on or after 1/6", true, 1, 6, 1, "Spring", 1, 1),
        Criterion("MLK Day is", "in Spring Semester Week 2", true, 1, 15, 1, "Spring", 2, 1),
        Criterion("Memorial Day is", "in Summer Semester Week 4", false, 5, 0, 1, "Summer", 4, 0.5),
        Criterion("Independence Day is", "in Summer Semester Week 9", true, 7, 4, -1, "Summer", 9, 0.5),
        Criterion("Fall Semester Week 1 ends on", "the last Friday in August", false, 8, 0, 5, "Fall", 1, 1),
        Criterion("Labor Day is", "in Fall Semester Week 3", false, 9, 1, 1, "Fall", 3, 1),
        Criterion("Columbus Day is", "in Fall Semester Week 8 (defines Fall Break)", false, 10, 2, 1, "Fall", 8, 1),
        Criterion("Thanksgiving is", "in Fall Semester Week 14", false, 11, 4, 4, "Fall", 14, 1),
        Criterion("Fall Semester Exams start on", "the first Monday in December", false, 12, 1, 1, "Fall", 16, 1)
    };
    int criteriaScores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for(int i = 0; i < NUM_CRITERIA; i++) {
        //Get defining criterion
        Criterion definingCriterion = criteria[i];
        
        //Print defining criteria
        std::cout << "Defining schedule by " << definingCriterion.getName() << " " << definingCriterion.getDescription() << std::endl;
        
        //Loop over each day of the week
        for(int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
            //Print day of week
            std::cout << "Year starts on " << DAY_OF_WEEK_NAMES[dayOfWeek] << ":\n" << std::endl;

            //Loop once for non-leap year and once for leap year
            for(int leap = 0; leap < 2; leap++) {
                if(leap) {
                    std::cout << "Leap Year\n" << std::endl;
                } else {
                    std::cout << "Non-leap year\n" << std::endl;
                }

                //Set the starting variables
                Day currDay = Day(dayOfWeek, leap);
                if(definingCriterion.isFixedDay()) {
                    while(currDay.getMonth() != definingCriterion.getMonth() || currDay.getDate() != definingCriterion.getDay()) {
                        currDay = currDay.next();
                    }
                    if(definingCriterion.getDayOfWeek() > -1) {
                        //Defining day should be the first occurrence of the day of the week after the given date
                        while(currDay.getDayOfWeek() != definingCriterion.getDayOfWeek()) {
                            currDay = currDay.next();
                        }
                    }
                } else if(definingCriterion.getOccurrence() > 0) {
                    while(currDay.getMonth() != definingCriterion.getMonth()) {
                        currDay = currDay.next();
                    }
                    if(definingCriterion.getOccurrence() != 1 || currDay.getDayOfWeek() != definingCriterion.getDayOfWeek()) {
                        int occurrence = 0;
                        while(occurrence < definingCriterion.getOccurrence() && currDay.getMonth() == definingCriterion.getMonth()) {
                            currDay = currDay.next();
                            if(currDay.getDayOfWeek() == definingCriterion.getDayOfWeek()) {
                                occurrence += 1;
                            }
                        }
                        if(currDay.getMonth() != definingCriterion.getMonth()) {
                            std::cout << MONTH_NAMES[definingCriterion.getMonth() - 1] << " does not have "
                                << definingCriterion.getOccurrence() << DAY_OF_WEEK_NAMES[definingCriterion.getDayOfWeek()] << "s!"
                                << std::endl;
                            return 1;
                        }
                    }
                } else {
                    while(currDay.getMonth() <= definingCriterion.getMonth()) {
                        currDay = currDay.next();
                    }
                    currDay = currDay.previous();
                    while(currDay.getDayOfWeek() != definingCriterion.getDayOfWeek()) {
                        currDay = currDay.previous();
                    }
                }
                SEMESTER = definingCriterion.getSemester();
                WEEK = definingCriterion.getTargetWeek();
                dateAnnouncement(definingCriterion, currDay);

                //Add starting scores
                double score;
                if(leap) {
                    score = definingCriterion.getWeight();
                } else {
                    score = 3 * definingCriterion.getWeight();
                }
                std::cout << " (+" << score << " ";
                if(score <= 1) {
                    std::cout << "pt";
                } else {
                    std::cout << "pts";
                }
                std::cout << ")" << std::endl;
                criteriaScores[i] += score;
                
                std::cout << std::endl;
            }
            std::cout << std::endl << std::endl;
        }
    }

    std::cout << "Final scores: " << std::endl;
    for(int i = 0; i < NUM_CRITERIA; i++) {
        std::cout << criteria[i].getName() << " " << criteria[i].getDescription() << " - " << criteriaScores[i] << " pts" << std::endl;
    }
    return 0;
}