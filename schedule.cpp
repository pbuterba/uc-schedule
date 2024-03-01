#include <iostream>
#include <string>
#include <fstream>
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
int DAYS_BEFORE_SPRING_SEMESTER = 0;
int DAYS_AFTER_FALL_SEMESTER = 0;

std::ofstream output("output.txt");

Day next(Day previousDay) {
    if(DAYS_BEFORE_SPRING_SEMESTER > 0) {
        DAYS_BEFORE_SPRING_SEMESTER--;
    } else if(DAYS_AFTER_FALL_SEMESTER > 0) {
        DAYS_AFTER_FALL_SEMESTER++;
    } else if(previousDay.getDayOfWeek() == 0) {
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
            DAYS_AFTER_FALL_SEMESTER++;
        } else {
            WEEK = WEEK + 1;
        }
    }
    return previousDay.next();
}

Day prev(Day followingDay) {
    if(DAYS_AFTER_FALL_SEMESTER > 0) {
        DAYS_AFTER_FALL_SEMESTER--;
    } else if(DAYS_BEFORE_SPRING_SEMESTER > 0) {
        DAYS_BEFORE_SPRING_SEMESTER++;
    } else if(followingDay.getDayOfWeek() == 1) {
        if(SEMESTER.compare("Spring") == 0 && WEEK == 1) {
            DAYS_BEFORE_SPRING_SEMESTER++;
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
    std::string outputText = criterion.getName() + " " + day.toString() + " (";
    if(DAYS_BEFORE_SPRING_SEMESTER > 0) {
        outputText = outputText + std::to_string(DAYS_BEFORE_SPRING_SEMESTER) + " days before spring semester)";
    } else if(DAYS_AFTER_FALL_SEMESTER > 0) {
        outputText = outputText + std::to_string(DAYS_AFTER_FALL_SEMESTER) + " days after fall semester)";
    } else {
        outputText = outputText + SEMESTER + " Semester Week " + std::to_string(WEEK) + ")";
    }
    output << outputText;
}

int main() {
    Criterion criteria[] = {
        Criterion("First Monday on or after 1/6 is", "the start of spring semester", true, 1, 6, 1, "Spring", 1, 1),
        Criterion("MLK Day is", "in Spring Semester Week 2", true, 1, 15, 1, "Spring", 2, 1),
        Criterion("Memorial Day is", "in Summer Semester Week 4", false, 5, 0, 1, "Summer", 4, 0.5),
        Criterion("Independence Day is", "in Summer Semester Week 9", true, 7, 4, -1, "Summer", 9, 0.5),
        Criterion("The last Friday in August is", "the end of Fall Semester Week 1", false, 8, 0, 5, "Fall", 1, 1),
        Criterion("Labor Day is", "in Fall Semester Week 3", false, 9, 1, 1, "Fall", 3, 1),
        Criterion("Columbus Day is", "in Fall Semester Week 8 (defines Fall Break)", false, 10, 2, 1, "Fall", 8, 1),
        Criterion("Thanksgiving is", "in Fall Semester Week 14", false, 11, 4, 4, "Fall", 14, 1),
        Criterion("The first Monday in December is", "the start of Fall final exams", false, 12, 1, 1, "Fall", 16, 1)
    };
    int criteriaScores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for(int i = 0; i < NUM_CRITERIA; i++) {
        //Get defining criterion
        Criterion definingCriterion = criteria[i];
        
        //Print defining criteria
        output << "Defining schedule by " << definingCriterion.getName() << " " << definingCriterion.getDescription() << std::endl;
        
        //Loop over each day of the week
        for(int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
            //Print day of week
            output << "Year starts on " << DAY_OF_WEEK_NAMES[dayOfWeek] << ":\n" << std::endl;

            //Loop once for non-leap year and once for leap year
            for(int leap = 0; leap < 2; leap++) {
                if(leap) {
                    output << "Leap Year\n" << std::endl;
                } else {
                    output << "Non-leap year\n" << std::endl;
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
                            output << MONTH_NAMES[definingCriterion.getMonth() - 1] << " does not have "
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
                DAYS_BEFORE_SPRING_SEMESTER = 0;
                DAYS_AFTER_FALL_SEMESTER = 0;
                dateAnnouncement(definingCriterion, currDay);

                //Add starting scores
                double score;
                if(leap) {
                    score = definingCriterion.getWeight();
                } else {
                    score = 3 * definingCriterion.getWeight();
                }
                output << " (+" << score << " ";
                if(score == 1) {
                    output << "pt";
                } else {
                    output << "pts";
                }
                output << ")" << std::endl;
                criteriaScores[i] += score;

                //Check all other criteria
                for(int j = 0; j < NUM_CRITERIA; j++) {
                    if(j != i) {
                        Criterion criterion = criteria[j];

                        //Reverse to the beginning of the year
                        while(currDay.getMonth() != 1 || currDay.getDate() != 1)
                        {
                            currDay = prev(currDay);
                        }

                        //Advance to the criterion day
                        if(criterion.isFixedDay()) {
                            while(currDay.getMonth() != criterion.getMonth() || currDay.getDate() != criterion.getDay()) {
                                currDay = next(currDay);
                            }
                            if(criterion.getDayOfWeek() > -1) {
                                //Defining day should be the first occurrence of the day of the week after the given date
                                while(currDay.getDayOfWeek() != criterion.getDayOfWeek()) {
                                    currDay = next(currDay);
                                }
                            }
                        } else if(criterion.getOccurrence() > 0) {
                            while(currDay.getMonth() != criterion.getMonth()) {
                                currDay = next(currDay);
                            }
                            if(criterion.getOccurrence() != 1 || currDay.getDayOfWeek() != criterion.getDayOfWeek()) {
                                int occurrence = 0;
                                while(occurrence < criterion.getOccurrence() && currDay.getMonth() == criterion.getMonth()) {
                                    currDay = next(currDay);
                                    if(currDay.getDayOfWeek() == criterion.getDayOfWeek()) {
                                        occurrence += 1;
                                    }
                                }
                                if(currDay.getMonth() != criterion.getMonth()) {
                                    output << MONTH_NAMES[criterion.getMonth() - 1] << " does not have "
                                        << criterion.getOccurrence() << DAY_OF_WEEK_NAMES[criterion.getDayOfWeek()] << "s!"
                                        << std::endl;
                                    return 1;
                                }
                            }
                        } else {
                            while(currDay.getMonth() <= criterion.getMonth()) {
                                currDay = next(currDay);
                            }
                            currDay = prev(currDay);
                            while(currDay.getDayOfWeek() != criterion.getDayOfWeek()) {
                                currDay = prev(currDay);
                            }
                        }

                        //Check if criterion is met
                        dateAnnouncement(criterion, currDay);
                        if(SEMESTER == criterion.getSemester() &&
                        WEEK == criterion.getTargetWeek() &&
                            DAYS_BEFORE_SPRING_SEMESTER == 0 &&
                            DAYS_AFTER_FALL_SEMESTER == 0)
                        {
                            //Add scores
                            double score;
                            if(leap) {
                                score = criterion.getWeight();
                            } else {
                                score = 3 * criterion.getWeight();
                            }
                            output << " (+" << score << " ";
                            if(score == 1) {
                                output << "pt";
                            } else {
                                output << "pts";
                            }
                            output << ")" << std::endl;
                            criteriaScores[i] += score;
                        } else {
                            output << ", should be " << criterion.getSemester() << " Semester Week " << criterion.getTargetWeek() << std::endl;
                        }

                    }
                    
                }
                output << std::endl;
            }
            output << std::endl << std::endl;
        }
    }

    output << "Final scores: " << std::endl;
    for(int i = 0; i < NUM_CRITERIA; i++) {
        output << criteria[i].getName() << " " << criteria[i].getDescription() << " - " << criteriaScores[i] << "/224 pts (" << (int)((criteriaScores[i]/224.0)*100) << "%)" << std::endl;
    }
    return 0;
}