#include"TaskTracker.h"
TaskTracker::TaskTracker()
{
     try {
        std::ifstream inFile("Tasks.json");
        if (inFile.good()) {
            tasks = nlohmann::json::parse(inFile);
        } else {
            tasks["Tasks"] = nlohmann::json::array();
        }
        inFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        tasks["Tasks"] = nlohmann::json::array();
    }
}
void TaskTracker::saveTasks()
{
    try
    {
         std::ofstream outFile("Tasks.json");
        if (!outFile.is_open()) {
            throw std::runtime_error("Unable to open file for writing");
        }
        outFile << std::setw(4) << tasks << std::endl;
        outFile.close();
    }
    catch(const std::exception& e)
    {
         std::cerr << "Error saving tasks: " << e.what() << std::endl;
    }
    
}
std::string TaskTracker::getTime()
{
   std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
    return buffer;
}
void TaskTracker::addTask(int id,std::string task)
{
    try{
    nlohmann::json newTask;
    newTask["Added Time"] = TaskTracker::getTime();
    newTask["status"] = "not done";
    newTask["Description"] = task;
    newTask["id"] = id;
    tasks["Tasks"].push_back(newTask);
    saveTasks();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error adding task: " << e.what() << std::endl;
    }
}
void TaskTracker::updateTask( int id,std::string status)
{
    try
    {
        for (auto& task : tasks["Tasks"]) {
            if (task["id"] == id) {
                task["status"] = status;
                task["Updated Time"] = TaskTracker::getTime();
                saveTasks();
                return;
            }
        }
        std::cerr << "Task with id " << id << " not found" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error updating task: " << e.what() << std::endl;
    }
}
void TaskTracker::listall()
{
    try
    {
        for (const auto& task : tasks["Tasks"]) {
            std::cout<<"Task ID: "<<task["id"]<<std::endl;
            std::cout<<"Task Description: "<<task["Description"]<<std::endl;
            std::cout<<"Task Status: "<<task["status"]<<std::endl;
            std::cout<<"Task Added Time: "<<task["Added Time"]<<std::endl;
            if (task["status"] != "not done") {
                std::cout<<"Task Updated Time: "<<task["Updated Time"]<<std::endl;
            }
            std::cout<<std::endl;
            std::cout<<std::endl;

        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error listing all tasks: " << e.what() << std::endl;
    }
}
void TaskTracker::listDone()
{
    try
    {
        for (const auto& task : tasks["Tasks"]) {
            if (task["status"] == "done") {
            std::cout<<"Task ID: "<<task["id"]<<std::endl;
            std::cout<<"Task Description: "<<task["Description"]<<std::endl;
            std::cout<<"Task Status: "<<task["status"]<<std::endl;
            std::cout<<"Task Updated Time: "<<task["Updated Time"]<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error listing done tasks: " << e.what() << std::endl;
    }
}
void TaskTracker::listNotdone()
{
    try
    {
        for (const auto& task : tasks["Tasks"]) {
            if (task["status"] == "not done") {
            std::cout<<"Task ID: "<<task["id"]<<std::endl;
            std::cout<<"Task Description: "<<task["Description"]<<std::endl;
            std::cout<<"Task Status: "<<task["status"]<<std::endl;
            std::cout<<"Task Added Time: "<<task["Added Time"]<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error listing not done tasks: " << e.what() << std::endl;
    }
}
void TaskTracker::listPending()
{
    try
    {
        for (const auto& task : tasks["Tasks"]) {
            if (task["status"] == "pending") {
            std::cout<<"Task ID: "<<task["id"]<<std::endl;
            std::cout<<"Task Description: "<<task["Description"]<<std::endl;
            std::cout<<"Task Status: "<<task["status"]<<std::endl;
            std::cout<<"Task Updated Time: "<<task["Updated Time"]<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error listing pending tasks: " << e.what() << std::endl;
    }
}
void TaskTracker::deleteTask(int id)
{
    try
    {
        for (auto it = tasks["Tasks"].begin(); it != tasks["Tasks"].end(); ++it) {
            if ((*it)["id"] == id) {
                tasks["Tasks"].erase(it);
                saveTasks();
                return;
            }
        }
        std::cerr << "Task with id " << id << " not found" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error deleting task: " << e.what() << std::endl;
    }
}
void TaskTracker::deleteAll()
{
    try
    {
        tasks["Tasks"] = nlohmann::json::array();
        saveTasks();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error deleting all tasks: " << e.what() << std::endl;
    }
}
void TaskTracker::menu()
{
    try
    {
        int choice;
        do {
            std::cout << "1. Add Task" << std::endl;
            std::cout << "2. Update Task" << std::endl;
            std::cout << "3. List all tasks" << std::endl;
            std::cout << "4. List done tasks" << std::endl;
            std::cout << "5. List not done tasks" << std::endl;
            std::cout << "6. List pending tasks" << std::endl;
            std::cout << "7. Delete task" << std::endl;
            std::cout << "8. Delete all tasks" << std::endl;
            std::cout << "9. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            system("clear");
            switch (choice) {
                case 1: {
                    int id;
                    std::string task;
                    std::cout << "Enter task id: ";
                    std::cin >> id;
                    std::cout << "Enter task description: ";
                    std::cin.ignore();
                    std::getline(std::cin, task);
                    addTask(id, task);
                    system("clear");
                    break;
                }
                case 2: {
                    int id;
                    std::string status;
                    std::cout << "Enter task id: ";
                    std::cin >> id;
                    std::cout << "Enter status: ";
                    std::cin.ignore();
                    std::getline(std::cin, status);
                    updateTask(id, status);
                    system("clear");
                    break;
                }
                case 3:
                    listall();
                    
                    break;
                case 4:
                    listDone();
                    
                    break;
                case 5:
                    listNotdone();
                    break;
                case 6:
                    listPending();
                    break;
                case 7: {
                    int id;
                    std::cout << "Enter task id: ";
                    std::cin >> id;
                    deleteTask(id);
                    break;
                }
                case 8:
                    deleteAll();
                    system("clear");
                    break;
                case 9:
                    std::cout << "Exiting..." << std::endl;
                    break;
                default:
                    std::cerr << "Invalid choice" << std::endl;
            }
        } while (choice != 9);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error in menu: " << e.what() << std::endl;
    }
}
