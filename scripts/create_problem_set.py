import os
import shutil
import argparse
import subprocess

LANGUAGES_EXTENSIONS = ["py", "cpp"]
VSCODE_PATH = r"C:\Users\simon\AppData\Local\Programs\Microsoft VS Code\Code.exe" 

def main():
    # Set up argument parsing
    parser = argparse.ArgumentParser(description="Create a new problem set from a template.")
    parser.add_argument("-l", "--language", choices=LANGUAGES_EXTENSIONS, required=True, help="Language for the new problem set")

    args = parser.parse_args()

    problem_name = input("Enter the name of the new problem set: ")
    template_file = f"template.{args.language}"  # Use the specified language extension
    destination_file = f"{problem_name}.{args.language}"  # Create the new file with the correct extension

    if os.path.exists(destination_file):
        print(f"Error: {destination_file} already exists.")
        return

    # Check if the template file exists
    if not os.path.exists(template_file):
        print(f"Error: Template file {template_file} does not exist.")
        return

    shutil.copy(template_file, destination_file)
    print(f"Created {destination_file} from {template_file}")
    full_path = os.path.abspath(destination_file)
    
    subprocess.run([VSCODE_PATH, full_path], check=True)

if __name__ == "__main__":
    main()
