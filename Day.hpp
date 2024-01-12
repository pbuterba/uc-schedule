#include <string>

class Day {
    private:
        //Static variables
        static std::string dayOfWeekNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        static std::string monthnames[12] = {
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
        
        //Member variables
        int month;
        int dayOfWeek;
        int day;
        bool isLeap;

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

    public:
        //Full detail constructor
        Day(int month, int dayOfWeek, int day, bool isLeap) : month(month), dayOfWeek(dayOfWeek), day(day), year(isLeap) {}

        //Year beginning constructor
        Day(int dayOfWeek, bool isLeap) : month(1), dayOfWeek(dayOfWeek), day(1), isLeap(isLeap) {}

        //Methods
        Day next() {
            if(month == 12 && day == 31) {
                return NULL;
            } else if(day == 31
                    || (day == 30 && (month == 4 || month == 6 || month == 9 || month == 11))
                    || (day == 29 && month == 2)
                    || (day == 28 && month == 2 && !isLeap)) {
                if(dayOfWeek == 6) {
                    return new Day(month + 1, 0, 1, isLeap);
                } else {
                    return new Day(month + 1, dayOfWeek + 1, 1, isLeap);
                }
            } else if(dayOfWeek == 6) {
                return new Day(month, 0, day + 1, isLeap);
            } else {
                return new Day(month, dayOfWeek + 1, day + 1, isLeap);
            }
        }

        std::string toString() {
            return dayOfWeekNames[dayOfWeek] + " " + monthNames[month - 1] + " " + day + dateSuffix(day);
        }

};