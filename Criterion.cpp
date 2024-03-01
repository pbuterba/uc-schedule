#include "Criterion.hpp"

//Constructor
Criterion::Criterion(std::string name, std::string descr, bool fixedDay, int month, int day, int dayOfWeek, std::string semester, int targetWeek, double weight) {
   this->name = name;
   this->descr = descr;
   this->fixedDay = fixedDay;
   this->month = month;
   this->day = day;
   this->dayOfWeek = dayOfWeek;
   this->semester = semester;
   this->targetWeek = targetWeek;
   this->weight = weight;
}

//Getters
std::string Criterion::getName() {
   return name;
}
std::string Criterion::getDescription() {
   return descr;
}
bool Criterion::isFixedDay() {
   return fixedDay;
}
int Criterion::getMonth() {
   return month;
}
int Criterion::getDay() {
   return day;
}
int Criterion::getOccurrence() {
   return day;
}
int Criterion::getDayOfWeek() {
   return dayOfWeek;
}
std::string Criterion::getSemester() {
   return semester;
}
int Criterion::getTargetWeek() {
   return targetWeek;
}
double Criterion::getWeight() {
   return weight;
}