import os
import requests
from bs4 import BeautifulSoup
import json

file_whitelist = {'bnn_accuracy.py', 'testing_tool.py', 'unununion_find.py'}
image_src = 'https://github.com/abrahamcalf/programming-languages-logos/blob/master/src/' # hey this a credit!
image_mapper = {
    'py':   'python',
    'c':    'c',
    'cpp':  'cpp',
    'cs':   'csharp',
    'go':   'go',
    'hs':   'haskell',
    'java': 'java',
    'kt':   'kotlin',
    'php':  'php',
    'rb':   'ruby',
    'js':   'javascript'
}

get_image = lambda e,s=24: f'{image_src}{image_mapper[e]}/{image_mapper[e]}_{s}x{s}.png'

def load_cached_difficulties(cache_file='difficulty_cache.json'):
    if os.path.exists(cache_file):
        with open(cache_file, 'r') as f:
            return json.load(f)
    return {}

def save_cached_difficulties(cache, cache_file='difficulty_cache.json'):
    with open(cache_file, 'w') as f:
        json.dump(cache, f, indent=4)

def get_problem_difficulty(pid, cache):
    # If the difficulty is cached, return it
    if pid in cache:
        return cache[pid]
    
    # Otherwise, request the difficulty from the Kattis website
    url = f"https://open.kattis.com/problems/{pid}"
    response = requests.get(url)
    if response.status_code == 200:
        # Parse the page using BeautifulSoup
        soup = BeautifulSoup(response.text, 'html.parser')
        # Find the difficulty number based on the class name
        difficulty_span = soup.find('span', class_='difficulty_number')
        if difficulty_span:
            difficulty = difficulty_span.text.strip()
            # Cache the result before returning it
            cache[pid] = difficulty
            return difficulty
    return "N/A"

# Load the cached difficulties
difficulty_cache = load_cached_difficulties()

contents = []
# Iterate through files in the 'solutions' directory
for file in sorted(os.listdir('solutions')):
    file_path = os.path.join('solutions', file)
    
    # Check if the item is a file and its extension is in image_mapper
    if os.path.isfile(file_path):
        ext = file.split('.')[-1]

        if ext in image_mapper:
            pid = file.split('.')[0]  # Use the filename without extension as the problem ID
            url = f"https://open.kattis.com/problems/{pid}"

            # Get the difficulty from Kattis or from the cache
            difficulty = get_problem_difficulty(pid, difficulty_cache)

            # Generate the display for the file
            image_icon = f"[![{ext}]({get_image(ext)})]({file_path})" if file not in file_whitelist else ""
            
            # Append the formatted line to contents, including difficulty
            contents.append([pid, f"|[{file}]({url})| {pid} | {difficulty} | {image_icon}|\n"])

# Save the updated difficulties cache
save_cached_difficulties(difficulty_cache)

# Read the current content of the README file
lines = open('README.md', 'r', encoding='utf8').readlines()

# Define the start and end markers
start_marker = '<!-- START_SOLVED_STATS -->'
end_marker = '<!-- END_SOLVED_STATS -->'

# Find the start and end markers in the lines
start_index = None
end_index = None
for i, line in enumerate(lines):
    if start_marker in line:
        start_index = i
    if end_marker in line:
        end_index = i
        break

# If both markers are found, replace content between them
if start_index is not None and end_index is not None:
    # Keep the lines outside the markers and prepare new content for inside
    lines = lines[:start_index+1] + [
        f'## Total problems solved: {len(contents)}\n\n',
        'Note that the table below is auto-generated. There might be slight inaccuracies.\n\n',
        '|Problem Name|Problem ID|Languages|\n|:---|:---|:---|\n'
    ] + [content for _, content in sorted(contents)] + lines[end_index:]

# Write the modified content back to the README file
with open('README.md', 'w', encoding='utf8') as f:
    f.writelines(lines)