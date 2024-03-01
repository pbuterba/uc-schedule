#ifndef DAY_HPP
#define DAY_HPP
#include <string>

class Day {
    private:
        //Member variables
        int month;
        int dayOfWeek;
        int day;
        bool isLeap;

    public:
        //Default constructor
        Day();

        //Full detail constructor
        Day(int, int, int, bool);

        //Year beginning constructor
        Day(int, bool);

        //Methods
        Day next();
        Day previous();
        int getMonth();
        int getDayOfWeek();
        int getDate();
        std::string toString();
};

#endif