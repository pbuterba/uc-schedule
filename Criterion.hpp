#include <string>

class Criterion {
    private:
        //Member variables
        std::string name;      // The name of this criterion
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
        Criterion(std::string name, bool fixedDay, int month, int day, int dayOfWeek, std::string semester, int targetWeek, double weight) {
            this->name = name;
            this->fixedDay = fixedDay;
            this->month = month;
            this->day = day;
            this->dayOfWeek = dayOfWeek;
            this->semester = semester;
            this->targetWeek = targetWeek;
            this->weight = weight;
        }

        //Getters
        std::string getName() {
            return name;
        }
        bool isFixedDay() {
            return fixedDay;
        }
        int getMonth() {
            return month;
        }
        int getDay() {
            return day;
        }
        int getOccurrence() {
            return day;
        }
        int getDayOfWeek() {
            return dayOfWeek;
        }
        std::string getSemester() {
            return semester;
        }
        int getTargetWeek() {
            return targetWeek;
        }
        double getWeight() {
            return weight;
        }

};