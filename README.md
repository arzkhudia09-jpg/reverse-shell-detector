# 🛡️ Reverse Shell Detector (Linux)

A lightweight **Linux process inspection and rule-based detection engine** written in **C**.

This project analyzes running processes through the Linux **/proc** filesystem and applies multiple heuristic rules to identify suspicious behavior commonly associated with reverse shells and malware.

> ⚠️ This project is intended for learning Linux internals, C programming, and basic detection engineering. It is **not** a replacement for professional EDR or antivirus solutions.

---

# 📖 Table of Contents

- Overview
- Features
- Detection Rules
- Detection Architecture
- Project Structure
- Technologies Used
- Build
- Run
- Example Output
- How It Works
- Current Limitations
- Future Improvements
- Learning Outcomes
- License

---

# 🚀 Overview

Instead of learning C through small console applications, this project explores real Linux internals by building a modular detection engine.

The detector:

- Enumerates running processes
- Reads process metadata
- Applies detection rules
- Calculates a risk score
- Explains why a process is considered suspicious

The project demonstrates:

- Linux `/proc` filesystem
- Multi-file C projects
- Modular software architecture
- Rule engine design
- Process inspection

---

# ✨ Features

## Process Enumeration

- Enumerates all running processes from `/proc`

---

## Process Information Collection

Reads:

- Process Name
- Executable Path
- PID
- Parent PID (PPID)
- Parent Process Name
- UID
- Thread Count
- Process State

---

## Rule-Based Detection

Current rules:

| Rule | Risk |
|------|------:|
| Executable running from `/tmp` | +30 |
| Executable running from `/var/tmp` | +30 |
| Executable running from `/dev/shm` | +30 |
| Executable marked as `(deleted)` | +40 |
| Suspicious parent process | +20 |
| Suspicious executable name | +10 |

---

## Risk Scoring

Each rule contributes to a cumulative risk score.

Example

```
Running from /tmp           +30
Deleted executable          +40
Parent = bash               +20

Total Risk Score = 90
```

---

## Human Readable Detection Reason

Example

```
⚠ Executable is running from a temporary directory.
Confidence: 30%

⚠ Running process points to a deleted executable.
Confidence: 40%

⚠ Suspicious parent process.
Confidence: 20%
```

---

# 🏗 Detection Architecture

```
                     Linux Kernel
                          │
                          ▼
                    /proc Filesystem
                          │
        ┌─────────────────┴─────────────────┐
        │                                   │
        ▼                                   ▼
   Process Enumeration              Process Metadata
        │
        ▼
   load_process_info()
        │
        ▼
     ProcessInfo
        │
        ▼
  ┌─────────────────────────────┐
  │      Detection Engine       │
  │                             │
  │ Rule #1 Temp Directory      │
  │ Rule #2 Deleted Executable  │
  │ Rule #3 Parent Process      │
  │ Rule #4 Suspicious Name     │
  └─────────────────────────────┘
                │
                ▼
        Detection Result
                │
                ▼
     Risk Score + Reasons
                │
                ▼
        Terminal Output
```

---

# 📂 Project Structure

```
Reverse_Shell_Detector/

│
├── build/
│
├── include/
│   ├── detector.h
│   ├── process.h
│   └── rules.h
│
├── src/
│   ├── detector.c
│   ├── process.c
│   ├── rules.c
│   └── main.c
│
├── README.md
│
└── Makefile (optional)
```

---

# ⚙ Technologies Used

- C
- GCC
- Linux
- POSIX APIs
- ProcFS

---

# 🔍 Detection Rules

## Rule #1

Detect executables launched from

```
/tmp/
/var/tmp/
/dev/shm/
```

These directories are frequently abused for temporary payload execution.

Risk Score

```
+30
```

---

## Rule #2

Detect executables marked

```
(deleted)
```

A deleted executable may indicate attempts to hide traces after execution.

Risk Score

```
+40
```

---

## Rule #3

Detect suspicious parent processes

Current list

```
bash
sh
python
perl
nc
ncat
socat
```

Risk Score

```
+20
```

---

## Rule #4

Detect suspicious executable names

Examples

```
bash
python
python3
perl
ruby
lua
php
nc
ncat
netcat
curl
wget
busybox
```

Risk Score

```
+10
```

---

# ⚙ Build

```
gcc src/*.c -Iinclude -o build/reverse_shell_detector
```

---

# ▶ Run

```
./build/reverse_shell_detector
```

---

# 📌 Example Output

```
====================================

PID       : 13425
Name      : bash
Parent    : python
State     : Sleeping
Threads   : 1
UID       : 1000

Risk Score : 60

Reasons

• Executable is running from a temporary directory.

• Suspicious parent process.

• Suspicious executable name.

====================================
```

---

# 🔬 How It Works

1. Enumerate `/proc`
2. Identify numeric PID directories
3. Read process metadata

```
/proc/<pid>/comm
/proc/<pid>/status
/proc/<pid>/exe
```

4. Store information inside

```
ProcessInfo
```

5. Apply every detection rule

6. Compute

- Risk Score
- Detection Reasons

7. Display report

---

# ⚠ Current Limitations

Current version does **not** inspect

- Network sockets
- TCP connections
- UDP connections
- File descriptors
- DNS activity
- Memory injection
- Process injection
- Persistence mechanisms
- Shell command history

The detector currently relies on process metadata and heuristic rules.

---

# 🚧 Future Improvements

Potential future enhancements

- Socket inspection
- `/proc/net/tcp` analysis
- Reverse shell IP detection
- Port reputation
- File descriptor analysis
- JSON output
- Logging support
- Configuration file
- Rule configuration
- Colored terminal output
- YARA integration
- Signature-based detection
- Behavioral detection

---

# 📚 Learning Outcomes

This project helped me understand

- C Programming
- Linux Process Management
- ProcFS
- Multi-file C Projects
- Header Files
- Structures
- Pointers
- Modular Software Design
- Rule Engines
- Linux System Programming
- String Handling
- File Handling

---

# 🤝 Contributing

Suggestions, improvements, and pull requests are welcome.

---

# 📄 License

This project is released under the MIT License.

---

# ⭐ Acknowledgements

This project was built as a personal learning exercise to strengthen C programming skills through a practical Linux security project.