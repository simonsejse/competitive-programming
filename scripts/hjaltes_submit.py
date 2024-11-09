import subprocess
import requests
import configparser
import re
import os
import time
import sys
import os
import shutil
from git import Repo, GitCommandError
import json
from datetime import date
import subprocess
import shutil 
import pickle
import json
import yaml
from datetime import date


# Constants
POLL_INTERVAL = 5 
MAX_ATTEMPTS = 5 
KATTIS_RC_PATH = os.path.expanduser("~/.kattis/.kattisrc") 
KATTIS_CLI_PATH = os.path.expanduser("~/.kattis")
SOLUTIONS_FOLDER = 'solutions' 


# Status map with direct values
STATUS_MAP = {
    0: 'New',
    1: 'New',
    2: 'Waiting for compile',
    3: 'Compiling',
    4: 'Waiting for run',
    5: 'Running',
    6: 'Judge Error',
    8: 'Compile Error',
    9: 'Run Time Error',
    10: 'Memory Limit Exceeded',
    11: 'Output Limit Exceeded',
    12: 'Time Limit Exceeded',
    13: 'Illegal Function',
    14: 'Wrong Answer',
    16: 'Accepted'
}

def read_kattis_credentials(kattisrc_path):
    """Reads Kattis credentials from the .kattisrc file."""
    config = configparser.ConfigParser()
    config.read(kattisrc_path)
    username = config.get('user', 'username')
    token = config.get('user', 'token')
    login_url = config.get('kattis', 'loginurl')
    hostname = config.get('kattis', 'hostname')
    return {
        'username': username,
        'token': token,
        'login_url': login_url,
        'hostname': hostname
    }


def login_with_config(credentials):
    """Login to Kattis using the provided credentials."""
    cookies_file = 'cookies.pkl'
    
    # Check if cookies file exists
    if os.path.exists(cookies_file):
        with open(cookies_file, 'rb') as f:
            return pickle.load(f)

    login_args = {'user': credentials['username'], 'token': credentials['token'], 'script': 'true'}
    headers = {'User-Agent': 'kattis-cli-submit'}
    response = requests.post(credentials['login_url'], data=login_args, headers=headers)

    if response.status_code == 200:
        print("Login successful.")
        # Save cookies to file using pickle
        with open(cookies_file, 'wb') as f:
            pickle.dump(response.cookies, f)
        return response.cookies  # Return session cookies after successful login
    else:
        print(f"Login failed with status code: {response.status_code}")
        sys.exit(1)

def get_submission_id_from_output(command):
    """Runs the kattis-cli command and captures the submission ID."""
    # Open the process with universal_newlines=True for real-time output streaming
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, bufsize=1)

    submission_id = None

    # Read stdout line by line as it is produced
    for line in process.stdout:
        # Print each line in real-time
        print(line, end='')

        # Check if the line contains the submission ID
        match = re.search(r'Submission ID: (\d+)', line)
        if match:
            submission_id = match.group(1)
            print(f"Captured Submission ID: {submission_id}")

    # Wait for the process to complete and capture stderr
    _, stderr = process.communicate()

    if process.returncode != 0:
        print(f"Error running kattis-cli command: {stderr}")
        sys.exit(1)

    if submission_id is None:
        print("Failed to capture submission ID from kattis-cli output.")
        sys.exit(1)

    return submission_id

def check_submission_status(submission_id, credentials):
    """Checks the status of a submission on Kattis."""
    cookies = login_with_config(credentials)
    status_url = f"https://{credentials['hostname']}/submissions/{submission_id}?json"
    headers = {'User-Agent': 'kattis-cli-submit'}

    attempt = 0
    while attempt < MAX_ATTEMPTS:
        try:
            response = requests.get(status_url, headers=headers, cookies=cookies)
            print(f"Attempt {attempt + 1} of {MAX_ATTEMPTS}: HTTP Status Code = {response.status_code}")

            if response.status_code == 200:
                status_json = response.json()
                status_id = status_json.get('status_id')
                status_text = STATUS_MAP.get(status_id, f"Unknown status {status_id}")
                print(f"Submission {submission_id} status: {status_text}")
                return status_text
            else:
                print(f"Failed to retrieve submission status, HTTP {response.status_code}")
        except requests.exceptions.RequestException as e:
            print(f"Request error: {e}")
        except Exception as e:
            print(f"Unexpected error: {e}")

        attempt += 1
        if attempt < MAX_ATTEMPTS:
            print(f"Retrying in {POLL_INTERVAL} seconds...\n")
            time.sleep(POLL_INTERVAL)

    print(f"Unable to retrieve status for submission {submission_id} after {MAX_ATTEMPTS} attempts.")
    return "Unknown"


def move(solution_file):
    # Paths
    BASE_DIR = os.getcwd()  # Get current working directory (assumes it is cp-contest)
    LOCAL_SIMON_REPO = os.path.join(BASE_DIR, ".simon", "competitive_programming")
    SOLUTIONS_DIR_SIMON = os.path.join(LOCAL_SIMON_REPO, "solutions")
    solution_basename = os.path.basename(solution_file)
    destination = os.path.join(BASE_DIR, "done", solution_basename)

    # Variables
    today_date = date.today().strftime('%Y-%m-%d')  # Use ISO format for consistency
    BRANCH_NAME = f"feature-{today_date}"  # Changed to avoid slashes
    MAIN_REPO = "simonsejse/competitive-programming"  # Corrected repository name
    COMMIT_MESSAGE = f"{solution_basename} finished and accepted!"

    # Ensure the local repository exists
    if not os.path.exists(LOCAL_SIMON_REPO):
        print(f"Local repository {LOCAL_SIMON_REPO} does not exist.")
        return

    # Initialize the repository
    repo = Repo(LOCAL_SIMON_REPO)

    # Check for uncommitted changes
    if repo.is_dirty(untracked_files=True):
        print("Uncommitted changes detected. Please commit or stash them before running the script.")
        return

    try:
        # Perform Git operations
        repo.remotes.origin.fetch()

        # Check if 'upstream' remote exists before fetching
        if 'upstream' in repo.remotes:
            repo.remotes.upstream.fetch()
            repo.git.checkout('main')
            repo.git.merge('upstream/main')
        else:
            print("'upstream' remote not found. Skipping merge from upstream.")
            repo.git.checkout('main')
            repo.git.pull('origin', 'main')

        # Checkout or create the feature branch
        branch_names = [head.name for head in repo.heads]
        if BRANCH_NAME in branch_names:
            repo.git.checkout(BRANCH_NAME)
        else:
            repo.git.checkout('-b', BRANCH_NAME)

        # Copy the solution file to the solutions directory
        source_solution_path = os.path.join(BASE_DIR, solution_file)
        destination_solution_path = os.path.join(SOLUTIONS_DIR_SIMON, solution_basename)
        shutil.copy2(source_solution_path, destination_solution_path)
        print(f"Copied {source_solution_path} to {destination_solution_path}")

        # Add, commit, and push changes
        relative_path = os.path.relpath(destination_solution_path, LOCAL_SIMON_REPO)
        repo.index.add([relative_path])
        print(f"Added {relative_path} to the index.")

        repo.index.commit(COMMIT_MESSAGE)
        print(f"Committed changes with message: {COMMIT_MESSAGE}")

        # Push the new branch to origin
        print(f"Pushing branch {BRANCH_NAME} to origin...")
        push_result = repo.git.push('--set-upstream', 'origin', BRANCH_NAME)
        print(push_result)

        # Create a pull request using the GitHub CLI
        # Ensure GitHub CLI is installed and authenticated

        # Prepare the commands
        pr_list_cmd = [
            'gh', 'pr', 'list',
            '--repo', MAIN_REPO,
            '--json', 'title'
        ]
        pr_create_cmd = [
            'gh', 'pr', 'create',
            '--repo', MAIN_REPO,
            '--title', BRANCH_NAME,
            '--body', 'Automatically generated PR',
            '--head', f"{repo.remote().url.split('/')[-2]}:{BRANCH_NAME}",  # Specify the head correctly
            '--base', 'main'
        ]

        # Execute the pr list command
        pr_list_result = subprocess.run(
            pr_list_cmd,
            cwd=LOCAL_SIMON_REPO,
            capture_output=True,
            text=True
        )

        if pr_list_result.returncode != 0:
            print(f"Failed to list pull requests: {pr_list_result.stderr}")
            return

        pr_list_output = pr_list_result.stdout
        prs = json.loads(pr_list_output)
        pr_exists = any(pr['title'] == BRANCH_NAME for pr in prs)

        if not pr_exists:
            # Create the pull request
            pr_create_result = subprocess.run(
                pr_create_cmd,
                cwd=LOCAL_SIMON_REPO,
                capture_output=True,
                text=True
            )
            if pr_create_result.returncode == 0:
                print("Pull request created successfully.")
            else:
                print(f"Failed to create pull request: {pr_create_result.stderr}")
        else:
            print("PR already exists. Pushed new commits to update the PR.")

        # Checkout back to main
        repo.git.checkout('main')
    except GitCommandError as e:
        print(f"Git command failed: {e}")
        repo.git.checkout('main')
        # Clean up the branch if it was created
        if BRANCH_NAME in [head.name for head in repo.heads]:
            repo.git.branch('-D', BRANCH_NAME)

    # Move the solution file to 'done' directory for your friend
    if os.path.exists(solution_file):
        shutil.move(solution_file, destination)
        print(f"Moved {solution_file} to {destination}")
    else:
        print(f"Error: The file {solution_file} was not found during move.")

    today_date = date.today().strftime('%d-%m-%Y')

    def write_to_cache(cache):
        with open(os.path.join('.cache.yml'), 'w') as f:
            yaml.safe_dump(cache, f)

    with open(os.path.join('.cache.yml'), 'r') as f:
        cache = yaml.safe_load(f) or {}

    if cache.get('data') is None:
        cache['data'] = {}  

    if cache.get('data').get(today_date) is None:
        cache['data'][today_date] = 1
        write_to_cache(cache)
        return

    cache['data'][today_date] += 1
    write_to_cache(cache)


def main():
    """Main function to run kattis-cli and check submission status."""
    if len(sys.argv) < 2:
        print("Usage: python script.py <path_to_solution_file>")
        sys.exit(1)

    # Get the solution file path from command-line arguments
    solution_file = sys.argv[1]

    # Check if the file exists
    if not os.path.isfile(solution_file):
        print(f"Error: File {solution_file} does not exist.")
        sys.exit(1)
    print(KATTIS_CLI_PATH)
    # Construct the kattis-cli command
    command = ["python3", f"{KATTIS_CLI_PATH}/submit.py", "-f", solution_file]

    # Read credentials from kattisrc
    credentials = read_kattis_credentials(KATTIS_RC_PATH)

    submission_id = get_submission_id_from_output(command)

    status = check_submission_status(submission_id, credentials)
    print(f"Final Status: {status}")

    if status == "Accepted":
        move(solution_file)
        

# Entry point
if __name__ == "__main__":
    main()
