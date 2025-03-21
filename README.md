# System Utility Tool

## Overview
The **System Utility Tool** is a command-line program for Windows that provides various system management functions. It allows users to shutdown, restart, clean temporary files, hide/unhide files and folders, modify system passwords, and more—all with simple commands.

## Features
- **Shutdown & Restart**: Schedule a shutdown or restart with a specified delay.
- **BIOS Restart**: Restart your system into BIOS mode.
- **File & Folder Management**:
  - Hide or unhide files and folders.
  - Bulk hide/unhide using a `data.dat` file.
- **System Cleanup**: Remove temporary and prefetch files to free up space.
- **Password Management**: Change the system user password directly from the command line.

## Usage
Run the program from the command prompt with the following syntax:

```
sys [command] [arguments]
```

### Commands
| Command        | Description |
|---------------|-------------|
| `shutdown [seconds]` | Shutdown the system after the specified time (default: immediate). |
| `restart [seconds]` | Restart the system after the specified time (default: immediate). |
| `bios [seconds]` | Restart the system into BIOS mode after the specified time. |
| `clean` | Clean all temporary files. |
| `hide [path]` | Hide a file or folder. |
| `uhide [path]` | Unhide a file or folder. |
| `h_ps` | Hide all paths listed in `data.dat`. |
| `uh_ps` | Unhide all paths listed in `data.dat`. |
| `password` | Change the system password for a user. |

## Example Usage
- To hide a folder:
  ```
  sys hide "C:\Users\User\Documents\SecretFolder"
  ```
- To schedule a restart after 30 seconds:
  ```
  sys restart 30
  ```
- To clean temporary files:
  ```
  sys clean
  ```

## Installation
1. Clone the repository or download the source code.
   ```
   git clone https://github.com/your-repository/sys-tool.git
   ```
2. Compile the program using a C++ compiler (MinGW/GCC/MSVC):
   ```
   g++ main.cpp -o sys.exe
   ```
3. Run the executable in the command prompt:
   ```
   sys.exe
   ```

## Notes
- The tool is intended for **Windows** only.
- Run the program as **Administrator** for full functionality.

## License
This project is licensed under the **MIT License**.

## Author
Developed by **Satish oraon**. Feel free to contribute or report issues!

