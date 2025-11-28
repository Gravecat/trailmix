// sys/process.hpp -- Ugly Windows-specific code for determining if more than one copy of the binary is running at once.
// I think I found this on Stack Overflow or something and modified it a bit. Here be monsters.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once
#ifdef TRAILMIX_TARGET_WINDOWS

#include <string>
#include <windows.h>

namespace trailmix::sys {

class Process
{
public:
    static BOOL CALLBACK btf_callback(HWND window_handle, LPARAM pid);  // Used internally with bring_to_foreground()
                // Checks if lom.exe is already running; if so, brings that window to the foreground then exits quietly.
    static void check_if_already_running(const std::string &mutex = "TRAILMIX");

private:
    // DO NOT ADJUST THESE VALUES. Just leave them alone.
    static constexpr int    WINX_FP_MAX_PROCESSES = 1024;
    static constexpr int    WINX_P2N_BUFFER_SIZE =  1024;

    static void         bring_to_foreground(DWORD pid);         // Brings the lom.exe window to the foreground if possible.
    static DWORD        find_process_id(std::string filename);  // Finds a given process ID, given a specified executable filename.
    static std::string  pid_to_name(DWORD pid);                 // Takes a Windows process ID and returns the name of the process.
};

}       // namespace trailmix::sys
#endif  // TRAILMIX_TARGET_WINDOWS
