#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <fstream>
#include <windows.h>


using namespace std;

void border();
// Forward declaration of TaskManager class
class TaskManager;

// Define a structure to represent a note
struct Note {
	
	int id; // Unique identifier for each note
    string title;
    string body;
    string date;
};

// Define a class to represent a task
class Task {
private:
	
	int id;
	int nextNoteId; 
    string description;
    bool completed;
    string category;
    vector<Note> notes;
    string createdDate;
    string completedDate;
   

public:
	
	
	//Parameterized Constructers
	Task(int taskId); 
	Task(const string& desc, const string& cat);
	
     // Member Functions
     
    int getId() const; 
    void markAsCompleted();
    void addNote(const string& title, const string& body);
    bool isCompleted();
    string getDescription();
    string getCategory();
    vector<Note>& getNotes();
    string getCreatedDate();
    string getCompletedDate();
    
};
 
 // Define a class to manage tasks
 
class TaskManager {
private:
	
    vector<Task*> tasks;
    int nextNoteId;

public:
	
	TaskManager();       //constructer
	~TaskManager();     // Deconstructer
	void addMultipleTasks(const string& input);
	void displayTasks();
	void markMultipleTasksAsCompleted(const string& input);
	void removeMultipleTasks(const string& input);
	void clearTasks() ;
	void saveNotesToFile(); 
	void readNotesFromFile();
	
};	
	   
	   
	   // Main function to run the to-do list application
int main() {
    TaskManager taskManager;

    int choice;
    while (true) {
    
    border();
        cout << "\n\t\t\t\t ========  ToDo List  ========\n\n\n";
        cout << "\t\t\t\t________________ Menu  ______________\n\n" << endl;
        cout << "\t\t1. Add multiple tasks\n";
        cout << "\t\t2. View tasks\n";
        cout << "\t\t3. Mark multiple tasks as completed\n";
        cout << "\t\t4. Remove multiple tasks\n";
        cout << "\t\t5. Clear all tasks\n";
        cout << "\t\t6. Save notes to file\n";  
        cout << "\t\t7. Read notes from file\n";  
        cout << "\t\t8. Exit\n\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string input;
            cout<<char(178) << "\t\tEnter multiple tasks (separated by comma): ";
            getline(cin, input);
            taskManager.addMultipleTasks(input);
            break;
        }
        case 2:
            taskManager.displayTasks();
            break;
        case 3: {
            string input;
            cout<<char(178) << "\t\tEnter the indices of tasks to mark as completed (separated by comma): ";
            getline(cin, input);
            taskManager.markMultipleTasksAsCompleted(input);
            break;
        }
        case 4: {
            string input;
            cout <<char(178)<< "\t\tEnter the indices of tasks to remove (separated by comma): ";
            getline(cin, input);
            taskManager.removeMultipleTasks(input);
            break;
        }
        case 5:
            taskManager.clearTasks();
            break;
            
         case 6:
            taskManager.saveNotesToFile();
            break;
            
        case 7:
            taskManager.readNotesFromFile();
            break;
            
        case 8:
            cout << "\t\tExiting the program. Goodbye!\n";
            cout << "\n\t\tPress any key to return to Menu";
            getch();
            system("cls");

            return 0;
        default:
            cout << "\t\tInvalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}

    
     // Constructor implementation
    Task::Task(int taskId) {
     this->id= taskId ;
    
}

    int Task::getId() const {
    return id;
}
    Task ::Task(const string& desc, const string& cat) {  //Constructer
        description = desc;
        completed = false;
        category = cat;
        time_t now = time(0);
        createdDate = ctime(&now);
        nextNoteId = 1; // Initialize nextNoteId to 1
    }

    //Defining Task class Member functions
    void Task :: markAsCompleted() {
        completed = true;
        time_t now = time(0);
        completedDate = ctime(&now);
    }

   void Task :: addNote(const string& title, const string& body) {
	    Note note;
	    note.id = nextNoteId++;                                      // Assign unique identifier to the note
	    note.title = title;
	    note.body = body;
	    time_t now = time(0);
	    note.date = ctime(&now);
	    notes.push_back(note);
	
	     // Call the updated saveNotesToFile function from TaskManager
	    TaskManager taskManager;
	    taskManager.saveNotesToFile();
}
   
    
    bool Task :: isCompleted() {
        return completed;
    }

    string Task :: getDescription() {
        return description;
    }

    string Task :: getCategory() {
        return category;
    }

    vector<Note> & Task :: getNotes() {
        return notes;
    }

    string Task :: getCreatedDate() {
        return createdDate;
    }

    string Task :: getCompletedDate() {
        return completedDate;
    }	
	
	// Defining  TaskManager Class Function members
	
	TaskManager::TaskManager() { // Constructer
        
        nextNoteId = 1;
    }
    
    TaskManager:: ~TaskManager() { 
	// deconstructer
        for (Task* task : tasks) {
            delete task;
        }
        tasks.clear();
    }

    void TaskManager:: addMultipleTasks(const string& input) {
    	
        stringstream ss(input);
        string taskDesc;

        while (getline(ss, taskDesc, ',')) {
            string category;
            cout <<char(178)<< "\t\tEnter task category for \"" << taskDesc << "\": ";
            getline(cin, category);
            Task* newTask = new Task(taskDesc, category);
            tasks.push_back(newTask);
        }

        cout<<char(178) << "\n\t\tTasks added successfully!\n";
        cout<<char(178) << "\n\t\tPress any key to return to Menu" << endl;
        getch();
        system("cls");
    }

    void TaskManager:: displayTasks() {
    	
        if (tasks.empty()) {
            cout<<char(178) << "\tTask list is empty.\n";
            return;
        }

        cout <<char(178)<< "\tTasks:\n";
        for (int i = 0; i < tasks.size(); i++) {
            Task* task = tasks[i];
            cout <<char(178)<< "\t"<<i << ". ";
            if (task->isCompleted()) {
                cout << "\t(\xfb) ";
            }
            else {
                cout << "\t() ";
            }
            cout << task->getDescription() << " (" << task->getCategory() << ")\n";
            if (!task->getNotes().empty()) {
                cout<<char(178) << "  \t Notes:\n";
                for (const Note& note : task->getNotes()) {
                    cout << "    - " << note.title << ": " << note.body << " (" << note.date << ")\n";
                }
            }
            cout <<char(178)<< "  \t Created: " << task->getCreatedDate();
            if (task->isCompleted()) {
                cout<<char(178) << "  \t Completed: " << task->getCompletedDate();
            }
            cout << endl;
        }

	        cout <<char(178)<< "\n\tPress any key to return to the menu...";
	        getch();
	        system("cls");
    }

    void TaskManager:: markMultipleTasksAsCompleted(const string& input) {
    	
        stringstream ss(input);
        string indexStr;

        while (getline(ss, indexStr, ',')) {
            int index = stoi(indexStr);          // stoi stands for string to integer
            if (index >= 0 && index < tasks.size()) {
                Task* task = tasks[index];
                task->markAsCompleted();
            }
        }

        cout<<char(178) << "\n\t\tTasks marked as completed!\n";
        cout <<char(178)<< "\n\t\tPress any key to return to Menu" << endl;
        getch();
        system("cls");
    }

    void TaskManager:: removeMultipleTasks(const string& input) {
    	
        stringstream ss(input);
        string indexStr;

        vector<int> indicesToRemove;
        while (getline(ss, indexStr, ',')) {
            int index = stoi(indexStr);
            if (index >= 0 && index < tasks.size()) {
                indicesToRemove.push_back(index);
            }
        }

        for (int i = indicesToRemove.size() - 1; i >= 0; i--) {
            int index = indicesToRemove[i];
            Task* task = tasks[index];
            tasks.erase(tasks.begin() + index);
            delete task;
        }

        cout <<char(178)<< "\n\t\tTasks removed successfully!\n";
        cout <<char(178)<< "\n\t\tPress any key to return to Menu" << endl;
        getch();
        system("cls");
    }

    void TaskManager:: clearTasks() {
    	
        for (Task* task : tasks) {
            delete task;
        }
        tasks.clear();

        cout<<char(178) << "\n\t\tAll tasks cleared!\n";
        cout<<char(178)<< "\n\t\tPress any key to return to Menu" << endl;
        getch();
        system("cls");
    }
    void TaskManager::saveNotesToFile() {
    	
    ofstream file("notes.txt");
    if (file.is_open()) {
    	
    	
    	  
        for (Task* task : tasks) {
        	file << "\t Task"<<endl;
            file << "\t Description: " << task->getDescription() << "\n";
            file << "\t Category: " << task->getCategory() << "\n";
            file << "\t Created Date: " << task->getCreatedDate() << "\n";
            file << "\t Completion Status: " << (task->isCompleted() ? "Completed" : "Incomplete") << "\n";
            if (task->isCompleted()) {
                file << " \tCompleted Date: " << task->getCompletedDate() << "\n";
               
            }
           
            for (const Note& note : task->getNotes()) {
                file << "\t Note ID: " << note.id << "\n";
                file << "\t Note Title: " << note.title << "\n";
                file << "\t Note Body: " << note.body << "\n";
                file << "\t Note Date: " << note.date << "\n";
            }
            file << "\n";
            
        }
    
        file.close();
        cout << "\n\t\tNotes saved to file successfully!\n";
    }
    else {
        cout << "\t\t Unable to open file to save notes.\n";
    }

    cout << "\n\t\tPress any key to return to Menu" << endl;
    getch();
    system("cls");
}


  void TaskManager::readNotesFromFile() {
    ifstream file("notes.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, title, body, date;
            getline(ss, idStr, ',');
            getline(ss, title, ',');
            getline(ss, body, ',');
            getline(ss, date, ',');

            try {
                int id = stoi(idStr);
                bool noteAdded = false;

                for (Task* task : tasks) {
                    if (task->getId() == id) {
                        task->addNote(title, body);
                        noteAdded = true;
                        break;
                    }
                }

                if (!noteAdded) {
                    cout <<char(178)<< "\t Note with ID " << id << " does not belong to any task." << endl;
                }
            } catch (const std::invalid_argument& e) {
                cout  << line << endl;
            }
        }

        cout <<char(178)<< "\n\t\tNotes read from file successfully!\n";
    }
    else {
        cout <<char(178)<< "\t\tUnable to open file to read notes.\n";
    }

    cout <<char(178)<< "\n\t\tPress any key to return to Menu." << endl;
    getch();
    system("cls");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void border()
{
	
	system("color F6");
    for(int c=0; c<=117; c++)    //for border
    {
    	gotoxy(c,0);
    	cout<<char(178);
    	
    	
	}
	for(int r=0; r<=40; r++)
	{
		gotoxy(117,r);
    	cout<<char(178);

	}
	for (int c = 117; c>=0; c--){
			gotoxy(c,40);
    	    cout<<char(178);

	}
		for(int r=40; r>=0; r--)
	{
		gotoxy(0,r);
    	cout<<char(178);
//    	Sleep(100);
}
   gotoxy(117,0); 
   
}