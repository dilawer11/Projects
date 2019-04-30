#include <iostream>
#include <string>

using namespace std;

class Date{
private:   
    int year;
    int month;
    int day;
public:
    Date();
    Date(int,int,int);
    void setDate(int,int,int);
    int getYear();
    int getMonth();
    int getDay();
};
class Time{
private:
    int hour;
    int minute;
public:
    Time();
    Time(int,int);
    void setTime(int _hour, int _minute);
    int getHour();
    int getMinute();
};
class Appointment{
private:
    string description;
    Date * date;
    Time * time;
public:
    Appointment(int,int,int,int,int,string);
    ~Appointment();
    virtual bool occurs_on(int,int,int);
    Date getDate();
    Time getTime();
    string getDescription();
};
class Onetime : public Appointment{
private:
public:
    bool occurs_on(int,int,int);
    Onetime(int,int,int,int,int,string);
};
class Daily : public Appointment{
private:
public:
    bool occurs_on(int,int,int);
    Daily(int,int,int,int,int,string);
};
class Weekly : public Appointment{
private:
public:
    bool occurs_on(int,int,int);
    Weekly(int,int,int,int,int,string);
};
class Monthly : public Appointment{
private:
public:
    bool occurs_on(int,int,int);
    Monthly(int,int,int,int,int,string);
};

Date::Date(){
    year = 0;
    month = 0;
    day = 0;
}
Date::Date(int _year, int _month , int _day){
    this->setDate(_year,_month ,_day);
}
void Date::setDate(int _year, int _month , int _day){
    year = _year;
    month = _month;
    day = _day;
}
int Date::getDay(){
    return day;
}
int Date::getMonth(){
    return month;
}
int Date::getYear(){
    return year;
}
Time::Time(){
    hour = 0;
    minute = 0;
}
Time::Time(int _hour, int _minute){
    this->setTime(_hour, _minute);
}
void Time::setTime(int _hour, int _minute){
    hour = _hour;
    minute = _minute;
}
int Time::getHour(){
    return hour;
}
int Time::getMinute(){
    return minute;
}
Appointment::Appointment(int day, int month, int year, int minute, int hour, string _description){
    date = new Date(year, month, day);
    time = new Time(hour,minute);
    description = _description;
}
Appointment::~Appointment(){
    delete date;
    delete time;
    description = "";
}
Date Appointment::getDate(){
    return *date;
}
Time Appointment::getTime(){
    return *time;
}
string Appointment::getDescription(){
    return description;
}
Onetime::Onetime(int day, int month, int year, int minute, int hour, string _description) : Appointment(day,month,year,minute,hour,_description){}
Monthly::Monthly(int day, int month, int year, int minute, int hour, string _description) : Appointment(day,month,year,minute,hour,_description){}
Weekly::Weekly(int day, int month, int year, int minute, int hour, string _description) : Appointment(day,month,year,minute,hour,_description){}
Daily::Daily(int day, int month, int year, int minute, int hour, string _description) : Appointment(day,month,year,minute,hour,_description){}
bool Appointment::occurs_on(int,int,int){
    return false;
}
bool Onetime::occurs_on(int year, int month, int day){
    Date date = this->getDate();
    if(date.getDay() == day && date.getMonth() == month && date.getYear() == year){
        return true;
    } else {
        return false;
    }
}
bool Daily::occurs_on(int year, int month, int day){
    return true;
}
bool Monthly::occurs_on(int year, int month, int day){
    Date date = this->getDate();
    if(date.getDay()==day){
        return true;
    } else{
        return false;
    }
}
bool Weekly::occurs_on(int year, int month, int day){
    Date date  = this->getDate();
    int yearDiff = year - date.getYear();
    int monthDiff = month - date.getMonth();
    int dayDiff = day - date.getDay();
    if(yearDiff < 0 || monthDiff < 0 || dayDiff < 0){
        return false;
    } else{
        return true;
    }
}
void testFunction(){
    int manualType = 1;
    Appointment ** apps;
    int n;
    if(manualType){
        cout << "Input the number of appointments : " ;
        cin >> n;
        apps = new  Appointment*[n];
        for(int i = 0; i < n ; i++){
            int day, month, year,hour,minute;
            string description, type;
            cout << endl << "Input Day: ";
            cin >> day;
            cout << endl << "Input Month: ";
            cin >> month;
            cout << endl << "Input Year: ";
            cin >> year;
            cout << endl <<"input Hour: ";
            cin >> hour;
            cout << endl <<"Input Minute: ";
            cin >> minute;
            cout << endl << "Input Description: ";
            cin >> description;
            cout << endl << "Input Type: ";
            cin >> type;
            if(type == "daily"){
                apps[i] = new Daily(day,month,year,minute,hour,description);
            } else if(type == "monthly"){
                apps[i] = new Monthly(day,month,year,minute,hour,description);
            } else if(type == "onetime"){
                apps[i] = new Onetime(day,month,year,minute,hour,description);
            } else if(type == "weekly"){
                apps[i] = new Weekly(day,month,year,minute,hour,description);
            }
            else{
                apps[i] = new Appointment(day,month,year,minute,hour,description);
            }
        }
    } else{
        apps = new Appointment*[10]; //Make this
        n=10;
    }
    int day, month, year;
    cout << "Input Date to check" <<endl;
    cout << "Input Day: ";
    cin >> day;
    cout << endl << "Input Month: ";
    cin >> month;
    cout << endl << "Input Year: ";
    cin >> year;
    cout << endl;
    bool none = true;
    for(int i = 0 ; i < n ; i++ ){
        if(apps[i]->occurs_on(year,month,day)){
            cout << apps[i]->getDescription() << endl;
            none = false;
        }
    }
    if(none){
        cout << "No Appoinments Found" << endl;
    }

}
int main(){
    testFunction();
    return 0;
}