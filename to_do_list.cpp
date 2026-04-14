#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct task {
    int id;
    string name;
    bool completeness;
};


int save(const vector<task>& vec);
int add_task(vector<task>& vec);
int delete_task(vector<task>& vec);
int display_tasks(const vector<task>& vec);
int display_completed(const vector<task>& vec);
int display_incomplete(const vector<task>& vec);
int mark_complete(vector<task>& vec);


int main() {
    ifstream in("to-do_list.txt");
    if(!in.is_open()) {
        cout << "Error opening file.\n";
        return 1;
    }

    vector<task> tasks;
    task t;
    while(in >> t.id >> t.name >> t.completeness) {
        tasks.push_back(t);
    }

    cout << "Welcome to To-Do List\n";
    cout << "1) Add a new task.\n";
    cout << "2) Mark a task as complete.\n";
    cout << "3) Delete a task.\n";
    cout << "4) Display all tasks.\n";
    cout << "5) Display completed tasks.\n";
    cout << "6) Display incomplete tasks.\n";
    cout << "7) Exit.\n";
    while(true) {
        cout << "Choose Operation: ";
        int n; cin >> n;
        cin.ignore();

        switch (n)
        {
        case 1:
            add_task(tasks);
            break;
        case 2:
            mark_complete(tasks);
            break;
        case 3:
            delete_task(tasks);
            break;
        case 4:
            display_tasks(tasks);
            break;
        case 5:
            display_completed(tasks);
            break;
        case 6:
            display_incomplete(tasks);
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid Operation.\n";
            break;
        }
        cout << "==========================\n";
    }
}


int add_task(vector<task>& vec) {
    task t;
    cout << "New Task: ";
    getline(cin, t.name);

    for(auto v : vec) {
        if(v.name == t.name) {
            cout << "Task already exist.\n";
            return 1;
        }
    }

    if(vec.empty()) t.id = 1;
    else t.id = vec[vec.size()-1].id + 1;

    t.completeness = false;

    vec.push_back(t);

    return save(vec);
}


int display_tasks(const vector<task>& vec) {
    if(vec.empty()) {
        cout << "No task to display.\n";
        return 1;
    }

    for(auto v : vec) {
        cout << v.id << ' ' << v.name << ' ';
        if(v.completeness) cout << "complete\n";
        else cout << "not complete\n";
    }

    return 0;
}


int delete_task(vector<task>& vec) {
    cout << "Task ID: ";
    int target; cin >> target;
  
    auto it = find_if(vec.begin(), vec.end(), 
        [target](const task& t) {
            return t.id == target;
        }
    );

    if(it != vec.end()) {
        vec.erase(it);
        return save(vec);
    }
    else {
        cout << "Task is not exist.\n";
        return 1;
    }
}


int mark_complete(vector<task>& vec) {
    cout << "Task ID: ";
    int target; cin >> target;

    for(auto& v : vec) {
        if(v.id == target) {
            v.completeness = true;
            return save(vec);
        }
    }

    cout << "Task not exist.\n";
    return 1;
}


int display_completed(const vector<task>& vec) {
    if(vec.empty()) {
        cout << "No tasks to display\n";
        return 1;
    }

    bool non = true;
    for(auto v : vec) {
        if(v.completeness) {
            cout << v.id << ' ' << v.name << endl;
            non = false;
        }
    }

    if(non) {
        cout << "Non is complete.\n";
        return 1;
    }
    else return 0;
}


int display_incomplete(const vector<task>& vec) {
    if(vec.empty()) {
        cout << "No tasks to display\n";
        return 1;
    }

    bool all = true;
    for(auto v : vec) {
        if(!v.completeness) {
            cout << v.id << ' ' << v.name << endl;
            all = false;
        }
    }

    if(all) {
        cout << "All is complete.\n";
        return 1;
    }
    else return 0;
}


int save(const vector<task>& vec) {
    ofstream out("to-do_list.txt");
    if(!out.is_open()) {
        cout << "Error opening file.\n";
        return 1;
    }

    for(auto v : vec) {
        out << v.id << ' ' << v.name << ' ' << v.completeness << endl;
    }

    return 0;
}