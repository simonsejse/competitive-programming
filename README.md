# 🌟 Competitive Programming Repository

## 🔗 [Kattis Profile](https://open.kattis.com/users/simon-winther-albertsen)

- **Repository Purpose**: This repository contains solutions to competitive programming problems, primarily from Kattis.
- **Language Used**: C++ and Python (could add this to CI/CD later)
- **Auto-updated Statistics**:

<!-- START_SOLVED_STATS -->
#### 📊 Problem Solving Statistics

| Language | Files Solved |
|----------|--------------|
| C++ | 50 |
| Python | 1 |
| **Total** | **49** |

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
   - Ensure you have a valid `.kattisrc` file in your home directory with your credentials. You can get it from [here](https://open.kattis.com/info/submit).

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
         "args": ["${workspaceFolder}/scripts/submit_and_move.py", "${file}"],
         "presentation": {
           "echo": true,
           "reveal": "always",
           "focus": true,
           "panel": "shared",
           "showReuseMessage": false,
           "clear": false,
           "close": true
         },
         "problemMatcher": []
       }
     ]
   }
   ```

4. **Setup Keybinding**:
   Add to `keybindings.json`:

   ```json
   [
     {
       "key": "f12",
       "command": "workbench.action.tasks.runTask",
       "args": "Submit to Kattis",
       "when": "editorTextFocus"
     }
   ]
   ```

5. **Create `solutions` Folder**:
   Manually create the folder or the script will create it automatically.

6. **Submit Solution**:
   - Keep unfinished solutions in the root directory. Open the solution file (e.g., `kattisexercise.cpp`), press `F7`, and it will automatically upload the solution to Kattis. If accepted, the script moves the file to the `solutions` folder.

### 📚 Resources

- **Kattis CLI Documentation:** [Kattis CLI GitHub](https://github.com/kattis/kattis-cli)

## 🔧 Setup: Auto Create Problem Set

Automate the creation of problem sets with specified language templates:

### 🛠️ Steps

1. **Add `create_problem_set.py`**:

   - Ensure your script is in the `scripts` folder and can handle language options.

Remember to change the `VSCODE_PATH` variable in the script to your own path:

```python
VSCODE_PATH = r"C:\Users\simon\AppData\Local\Programs\Microsoft VS Code\Code.exe" #Remember to change this to your own path
```

2. **Configure VSCode Tasks**:
   Add the following to your `.vscode/tasks.json`:

   ```json
   {
     "version": "2.0.0",
     "tasks": [
       {
         "label": "Create New Problem Set (py)",
         "type": "shell",
         "command": "python",
         "presentation": {
           "echo": true,
           "reveal": "always",
           "focus": true,
           "panel": "shared",
           "showReuseMessage": false,
           "clear": false,
           "close": true
         },
         "args": [
           "${workspaceFolder}/scripts/create_problem_set.py",
           "-l",
           "py"
         ]
       },
       {
         "label": "Create New Problem Set (cpp)",
         "type": "shell",
         "command": "python",
         "presentation": {
           "echo": true,
           "reveal": "always",
           "focus": true,
           "panel": "shared",
           "showReuseMessage": false,
           "clear": false,
           "close": true
         },
         "args": [
           "${workspaceFolder}/scripts/create_problem_set.py",
           "-l",
           "cpp"
         ]
       }
     ]
   }
   ```

3. Setup Keybindings: Add to keybindings.json:

```json
[
  {
    "key": "f9", // For C++
    "command": "workbench.action.tasks.runTask",
    "args": "Create New Problem Set (cpp)",
    "when": "true"
  },
  {
    "key": "f10", // For Python
    "command": "workbench.action.tasks.runTask",
    "args": "Create New Problem Set (py)",
    "when": "true"
  }
]
```

4. Use the Tasks:

- Press `F9` to create a new Python problem set.
- Press `F10` to create a new C++ problem set.

### 📂 Template Files

Ensure you have template.py and template.cpp in your root directory to serve as templates for new problem sets.
