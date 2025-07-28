#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>  
#include <regex>   
#include <sstream> 
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// -------------------------------------------- usage command -------------------------

void usage(const string &program_name) {
    system("cls");
    cout << "\nUsage: " << program_name << " <command> [options] [sh][re][-v][-h]" << endl;
    cout << "Commands:" << endl;
    cout << "  sh\t\tshutdown system you can also pass [time_in_seconds]." << endl;
    cout << "  re\t\trestart system you can also pass [time_in_seconds]." << endl;
    cout << "  bios\t\topen bios after restart [time_in_seconds]." << endl;
    cout << "  clean \tremove all junk files from system." << endl;
    cout << "  hide \t\t[folder/file] hide file and folder." << endl;
    cout << "  uhide \t[folder/file] hide file and folder." << endl;
    cout << "  password \tto change the current user passwords" << endl;
    cout << "  h_ps \t\thide file and folder path store in data.dat file." << endl;
    cout << "  uh_ps \thide file and folder path store in data.dat file." << endl;
    cout << "  debloot \tdebloot script will execute" << endl;
    cout << "  performance \ttest your system performance." << endl;
    cout << "\nOptions:" << endl;
    cout << "  -v, --verbose\tversion of this program." << endl;
    cout << "  -h, --help\tShow help for a specific command." << endl;

    exit(0); 
}  

// ------------------------------------- performance test -------------------------------

// Function to execute a PowerShell command and capture its output
string executePowerShellCommand(const string& command) {
    string fullCommand = "powershell -command \"" + command + "\"";
    char buffer[128];
    string result = "";

    // Open pipe to file
    FILE* pipe = _popen(fullCommand.c_str(), "r");
    if (!pipe) {
        return "Error: Unable to open pipe";
    }

    // Read till end of process
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    _pclose(pipe);
    return result;
}

// Function to extract WinSPRLevel from PowerShell output
int extractWinSPRLevel(const string& output) {
    regex pattern("WinSPRLevel\\s*:\\s*(\\d+\\.?\\d*)");
    smatch matches;
    
    if (regex_search(output, matches, pattern)) {
        if (matches.size() > 1) {
            // Convert the matched string to a float
            float score = stof(matches[1].str());
            // Return as integer (we'll multiply by 10 to handle decimal)
            return static_cast<int>(score * 10);
        }
    }
    return -1; // Return -1 if not found
}

// Function to display performance information based on WinSPRLevel
void displayPerformanceInfo(int score) {
    cout << "\nSystem Performance Rating: " << (score / 10.0) << endl;
    cout << "----------------------------------------\n";
    
    if (score >= 10 && score <= 29) {
        cout << "1.0 - 2.9 (Very Low Score)\n\n";
        cout << "* Basic tasks only:\n";
        cout << "  - Web browsing\n";
        cout << "  - Word processing\n";
        cout << "  - Email\n";
        cout << "  - Standard-definition video playback\n\n";
        cout << "Not suitable for:\n";
        cout << "  - Gaming\n";
        cout << "  - Heavy multitasking\n";
        cout << "  - HD media editing\n";
    }
    else if (score >= 30 && score <= 39) {
        cout << "3.0 - 3.9 (Low Mid Range)\n\n";
        cout << "Standard office and home tasks:\n";
        cout << "  - Moderate multitasking\n";
        cout << "  - Video streaming (possibly HD)\n";
        cout << "  - Light photo editing\n\n";
        cout << "* Limited performance in:\n";
        cout << "  - Gaming\n";
        cout << "  - 3D applications\n";
    }
    else if (score >= 40 && score <= 49) {
        cout << "4.0 - 4.9 (MidRange)\n\n";
        cout << "* Good for:\n";
        cout << "  - HD video playback\n";
        cout << "  - Light to moderate gaming\n";
        cout << "  - Multitasking\n";
        cout << "  - Casual content creation\n";
    }
    else if (score >= 50 && score <= 69) {
        cout << "5.0 - 6.9 (High Performance)\n\n";
        cout << "* Well-suited for:\n";
        cout << "  - HD video editing\n";
        cout << "  - Graphic design\n";
        cout << "  - Moderate 3D gaming\n";
        cout << "  - Smooth multitasking with multiple demanding apps\n";
    }
    else if (score >= 70 && score <= 99) {
        cout << "7.0 - 9.9 (Very High Performance)\n\n";
        cout << "* Power users and professionals:\n";
        cout << "  - 3D rendering\n";
        cout << "  - High-end gaming\n";
        cout << "  - 4K video editing\n";
        cout << "  - Virtual machines\n";
        cout << "  - Software development (including compiling large codebases)\n";
    }
    else {
        cout << "Unknown performance level. WinSPRLevel not in expected range (1.0-9.9).\n";
    }
}

//  hide [personal] / uhide [personal] / shutdown / restart / bios / clean / change password.


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


// --------------------------------------- main ---------------------------------------

int main(int argc, char *argv[]) {

    const std::string filename = "data.dat";
    
    if (!fs::exists(filename)) {
        cout << "File not found: " << filename << endl;
        
        std::ofstream newFile(filename);
        if (newFile) {
            cout << "Created new file: " << filename << endl;
        } else {
            cerr << "Error: Failed to create file" << endl;
            return 1;
        }
    } else {
        return 0; 
    }
    
 

    if (argc < 2) {
        usage(argv[0]);
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
    }else if (command == "debloot") {
        system("powershell -Command \"irm 'https://christitus.com/win' | iex\"");
    }else if (command == "performance") {
        cout << "Retrieving Windows System Assessment Tool (WinSAT) results...\n";
        string output = executePowerShellCommand("Get-CimInstance Win32_WinSAT");

        int score = extractWinSPRLevel(output);
        
        if (score == -1) {
            cout << "Error: Could not retrieve WinSPRLevel from WinSAT results.\n";
            cout << "Make sure WinSAT assessment has been run on this system.\n";
            cout << "You can run it manually with: \"winsat formal\" in an elevated command prompt.\n";
            return 1;
        }
  
        displayPerformanceInfo(score);
        
    }else if (command == "-v" || command == "--version") {
        cout << "version 0.1.1" << endl;
    }
    else {
        cerr << "Error: Unknown command '" << command << "'" << endl;
        usage(argv[0]);
        return 1;
    }
    return 0;
}

