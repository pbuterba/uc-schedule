#include <string>

class Criterion {
    private:
        //Member variables
        std::string name;      // The name of this criterion
        bool fixedDay;         /*If true, this criterion checks the location of a specific day. If false, it checks the location of a
                               certain occurrence of a day of the week within the month (e.g. second Tuesday in the month)*/
        int month;             // Month to check (1-12)
        int day;               // IF fixed date, day within the month to check. ELSE occurrence of the day of the week to check
        int dayOfWeek;         // 0-6 = Sunday-Saturday: Day of week to check in month. -1 if fixed date
        std::string semester;  // Which semester this criterion applies to (Spring, Summer, Fall)
        double weight;         // 1 for most criteria, 0.5 for lower priority

    public:
        //Fixed day constructor
        Criterion(std::string name, int month, int day, std::string semester, double weight) {
            this->name = name;
            fixedDay = true;
            this->month = month;
            this->day = day;
            dayOfWeek = -1;
            this->semester = semester;
            this->weight = weight;
        }

        //Day of week occurrence constructor
        Criterion(std::string name, int occurrence, int dayOfWeek, int month, std::string semester, double weight) {
            this->name = name;
            fixedDay = false;
            this->month = month;
            day = occurrence;
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
        double getWeight() {
            return weight;
        }

};