#include <string>

//Static variables
static std::string dayOfWeekNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
static std::string monthNames[] = {
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

//Static functions
static std::string dateSuffix(int date) {
    if(date == 1 || date == 21 || date == 31) {
        return "st";
    } else if(date == 2 || date == 22) {
        return "nd";
    } else if(date == 3 || date == 23) {
        return "rd";
    } else {
        return "th";
    }
}

class Day {
    private:
        //Member variables
        int month;
        int dayOfWeek;
        int day;
        bool isLeap;

    public:
        //Default constructor
        Day() {}

        //Full detail constructor
        Day(int month, int dayOfWeek, int day, bool isLeap) : month(month), dayOfWeek(dayOfWeek), day(day), isLeap(isLeap) {}

        //Year beginning constructor
        Day(int dayOfWeek, bool isLeap) : month(1), dayOfWeek(dayOfWeek), day(1), isLeap(isLeap) {}

        //Methods
        Day next() {
            if(month == 12 && day == 31) {
                return Day(0, 0, 0, false);
            }
            int newMonth;
            int newDayOfWeek;
            int newDay;

            //Get month and day
            if(day < 28 || (day < 29 && isLeap) || (day < 30 && month != 2) || (day < 31 && month != 2 && month != 4 && month != 6 && month != 9 && month != 11)) {
                newMonth = month;
                newDay = day + 1;
            } else {
                newMonth = month + 1;
                newDay = 1;
            }

            //Get day of week
            if(dayOfWeek == 6) {
                newDayOfWeek = 0;
            } else {
                newDayOfWeek = dayOfWeek + 1;
            }

            return Day(newMonth, newDayOfWeek, newDay, isLeap);
        }

        Day previous() {
            if(month == 1 && day == 1) {
                return Day(0, 0, 0, false);
            }

            int newMonth;
            int newDayOfWeek;
            int newDay;

            //Get new day and month
            if(day == 1) {
                newMonth = month - 1;
                if(newMonth == 2) {
                    if(isLeap) {
                        newDay = 29;
                    } else {
                        newDay = 28;
                    }
                } else if(newMonth == 4 || newMonth == 6 || newMonth == 9 || newMonth == 11) {
                    newDay = 30;
                } else {
                    newDay = 31;
                }
            } else {
                newMonth = month;
                newDay = day - 1;
            }

            //Get new day of week
            if(dayOfWeek == 0) {
                newDayOfWeek = 6;
            } else {
                newDayOfWeek = dayOfWeek - 1;
            }
            return Day(newMonth, newDayOfWeek, newDay, isLeap);
        }

        int getMonth() {
            return month;
        }

        int getDayOfWeek() {
            return dayOfWeek;
        }

        std::string toString() {
            return dayOfWeekNames[dayOfWeek] + " " + monthNames[month - 1] + " " + std::to_string(day) + dateSuffix(day);
        }

};