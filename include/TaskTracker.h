
#include <string>
#include <vector>
#include<nlohmann/json.hpp>
#include <fstream>
#include<ctime>
#include<iostream>
#include <cstdlib>
class TaskTracker 
{
private:
     nlohmann::json tasks;

public:
    TaskTracker();
    void saveTasks();
    std::string getTime();
    void addTask(int id,std::string task);
    void updateTask( int id,std::string status);
    void listall();
    void listDone();
    void listNotdone();
    void listPending();
    void deleteTask(int id);
    void deleteAll();
    void menu();
};