# 🌟 Competitive Programming Repository

## 🔗 [Kattis Profile](https://open.kattis.com/users/simon-winther-albertsen)

- **Repository Purpose**: This repository contains solutions to competitive programming problems, primarily from Kattis.
- **Language Used**: C++ and Python (could add this to CI/CD later)
- **Auto-updated Statistics**:

<!-- START_SOLVED_STATS -->
#### 📊 Problem Solving Statistics

| Language | Files Solved |
|----------|--------------|
| C++ | 8 |
| Python | 1 |
| **Total** | **7** |

<!-- END_SOLVED_STATS -->

## 📂 Directory Structure

- **`.github/workflows/`**: Contains automation scripts for CI/CD.
- **`README.md`**: Contains project description and auto-generated stats.


## 🔧 Setup: Auto Submit and Move

To automate Kattis submissions and organize accepted files:

### 🛠️ Steps

1. **Install Prerequisites**:
    - Python: [Download Python](https://www.python.org/downloads/)
    - Kattis CLI: [Kattis CLI](https://github.com/kattis/kattis-cli)
    - Python Packages: `pip install requests beautifulsoup4`

2. **Add `submit_and_move.py`**:
   - The script is in [`scripts/submit_and_move.py`](https://github.com/simonsejse/competitive_programming/blob/main/scripts/submit_and_move.py).

3. **Configure VSCode Task**:
    Add this to `.vscode/tasks.json`:
    
    ```json
    {
        "version": "2.0.0",
        "tasks": [
            {
                "label": "Submit to Kattis",
                "type": "shell",
                "command": "python",
                "args": [
                    "${workspaceFolder}/scripts/submit_and_move.py",
                    "${file}"
                ]
            }
        ]
    }
    ```

4. **Setup Keybinding**:
    Add to `keybindings.json`:

    ```json
    [
        {
            "key": "f7",
            "command": "workbench.action.tasks.runTask",
            "args": "Submit to Kattis",
            "when": "editorTextFocus"
        }
    ]
    ```

5. **Create `solutions` Folder**:
    Manually create the folder or the script will create it automatically.

6. **Submit Solution**:
    - Open the solution file, e.g., `kattisexercise.cpp`, press `F7`, and it will automatically upload the solution to Kattis and if accepted move the task into the solutions folder. 

### 📚 Resources

- **Kattis CLI Documentation:** [Kattis CLI GitHub](https://github.com/kattis/kattis-cli)
