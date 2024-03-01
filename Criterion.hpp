#ifndef CRITERION_HPP
#define CRITERION_HPP
#include <string>

class Criterion {
    private:
        //Fields
        std::string name;      // The name of this criterion
        std::string descr;     // Description of when the criteria should fall
        bool fixedDay;         /*If true, this criterion checks the location of a specific day. If false, it checks the location of a
                               certain occurrence of a day of the week within the month (e.g. second Tuesday in the month)*/
        int month;             // Month to check (1-12)
        int day;               /* IF fixed date, day within the month to check. ELSE occurrence of the day of the week to check. 0 
                               for last ocurrence in the month */
        int dayOfWeek;         // 0-6 = Sunday-Saturday
                               // If fixed date, find the first day of this day of week after the specified date
                               // If set to -1, find the fixed date regardless of day of the week
                               // If day of week occurrence, this is the day of the week to check
        std::string semester;  // Which semester this criterion applies to (Spring, Summer, Fall)
        int targetWeek;        // The week in which this day would ideally fall, within the given semester
        double weight;         // 1 for most criteria, 0.5 for lower priority

    public:
        //Constructor
        Criterion(std::string, std::string, bool, int, int, int, std::string, int, double);

        //Getters
        std::string getName();
        std::string getDescription();
        bool isFixedDay();
        int getMonth();
        int getDay();
        int getOccurrence();
        int getDayOfWeek();
        std::string getSemester();
        int getTargetWeek();
        double getWeight();
};

#endif