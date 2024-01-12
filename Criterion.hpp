#include <string>

class Criterion {
    private:
        //Member variables
        std::string name;      // The name of this criterion
        bool fixedDay;         /*If true, this criterion checks the location of a specific day. If false, it checks the location of a
                               certain occurrence of a day of the week within the month (e.g. second Tuesday in the month)*/
        int month;             // Month to check (1-12)
        int day;               // IF fixed date, day within the month to check. ELSE occurrence of the day of the week to check
        int dayOfWeek;         // 0-6 = Sunday-Saturday
                               // If fixed date, find the first day of this day of week after the specified date
                               // If day of week occurrence, this is the day of the week to check
        std::string semester;  // Which semester this criterion applies to (Spring, Summer, Fall)
        double weight;         // 1 for most criteria, 0.5 for lower priority

    public:
        //Constructor
        Criterion(std::string name, bool fixedDay, int month, int day, int dayOfWeek, std::string semester, double weight) {
            this->name = name;
            this->fixedDay = fixedDay;
            this->month = month;
            this->day = day;
            this->dayOfWeek = dayOfWeek;
            this->semester = semester;
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
        double getWeight() {
            return weight;
        }

};