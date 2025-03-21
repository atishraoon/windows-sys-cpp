#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

void usage() {
    system("cls");
    cout << "\n    sys [shutdown sh|re [seconds] ][bios][..]\n";
    cout << "    re       : restart\n";
    cout << "    clean    : clean all temp files\n";
    cout << "    hide     : hide file or folder. hide [path | h_ps]\n";
    cout << "    uhide    : unhide the file and folder. uhide [path | uh_ps]\n";
    cout << "    password : to change the sys password \n";
    exit(0);
}

void hide(const string &path) {
    if (GetFileAttributes(path.c_str()) == INVALID_FILE_ATTRIBUTES) {
        cout << "Path " << path << " does not exist." << endl;
        return;
    }
    string command = "attrib +h +r +s \"" + path + "\"";
    system(command.c_str());
    cout << "Successfully hidden: " << path << endl;
}

void uhide(const string &path) {
    if (GetFileAttributes(path.c_str()) == INVALID_FILE_ATTRIBUTES) {
        cout << "Path " << path << " does not exist." << endl;
        return;
    }
    string command = "attrib -h -r -s \"" + path + "\"";
    system(command.c_str());
    cout << "Successfully unhidden: " << path << endl;
}

void shutdown(int time = 0) {
    cout << "Shutdown in " << time << "s" << endl;
    string command = "shutdown -s -t " + to_string(time);
    system(command.c_str());
}

void restart(int time = 0) {
    cout << "Restart in " << time << "s" << endl;
    string command = "shutdown -r -t " + to_string(time);
    system(command.c_str());
}

void bios(int time = 0) {
    cout << "Ready for BIOS restart in " << time << "s" << endl;
    string command = "shutdown -r -fw -t " + to_string(time);
    system(command.c_str());
}

void h_ps() {
    ifstream file("data.dat");
    if (!file) {
        cout << "data.dat file not found." << endl;
        return;
    }
    string path;
    while (getline(file, path)) {
        hide(path);
    }
}

void uh_ps() {
    ifstream file("data.dat");
    if (!file) {
        cout << "data.dat file not found." << endl;
        return;
    }
    string path;
    while (getline(file, path)) {
        uhide(path);
    }
}

void clean() {
    string temp = "C:\\Windows\\Temp\\*";
    string prefetch = "C:\\Windows\\Prefetch\\*";
    string local_temp = "C:\\Users\\Dell\\AppData\\Local\\Temp\\*";

    system(("del /q /f /s " + temp).c_str());
    system(("del /q /f /s " + prefetch).c_str());
    system(("del /q /f /s " + local_temp).c_str());
    cout << "Cleaned successfully" << endl;

    Sleep(1000);
    system("cls"); 
}

void change_password() {
    system("net user");
    string user;
    cout << "Enter user to modify password: ";
    getline(cin, user);
    
    if (!user.empty()) {
        string command = "net user " + user + " *";
        system(command.c_str());
        cout << "Password changed successfully" << endl;
    } else {
        cout << "User not found" << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
    }

    string command = argv[1];

    if (command == "hide" && argc > 2) {
        hide(argv[2]);
    } else if (command == "uhide" && argc > 2) {
        uhide(argv[2]);
    } else if (command == "h_ps") {
        h_ps();
    } else if (command == "uh_ps") {
        uh_ps();
    } else if (command == "shutdown" || command == "sh") {
        shutdown(argc > 2 ? stoi(argv[2]) : 0);
    } else if (command == "restart" || command == "re") {
        restart(argc > 2 ? stoi(argv[2]) : 0);
    } else if (command == "bios") {
        bios(argc > 2 ? stoi(argv[2]) : 0);
    } else if (command == "clean") {
        clean();
    } else if (command == "password") {
        change_password();
    } else {
        cout << "Unexpected argument" << endl;
    }
    return 0;
}

