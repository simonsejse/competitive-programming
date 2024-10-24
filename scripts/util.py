import os
import json
from datetime import datetime
import requests
from bs4 import BeautifulSoup
import re

#Constants
CACHE_EXPIRY_DAYS = 60

# Map extensions to languages
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

# Function to generate the correct image URL
def get_image(ext, size=24):
    return f'https://github.com/abrahamcalf/programming-languages-logos/blob/master/src/{image_mapper[ext]}/{image_mapper[ext]}_{size}x{size}.png'

# Function to get the current date
def get_current_date():
    return datetime.now().strftime('%Y-%m-%d')

# Load cached difficulties from a file
def load_cached_difficulties(cache_file='difficulty_cache.json'):
    if os.path.exists(cache_file):
        with open(cache_file, 'r') as f:
            return json.load(f)
    return {}

# Save cached difficulties to a file
def save_cached_difficulties(cache, cache_file='difficulty_cache.json'):
    with open(cache_file, 'w') as f:
        json.dump(cache, f, indent=4)

# Get problem difficulty either from cache or by scraping Kattis
def get_problem_difficulty(pid, cache):
    if pid in cache:
        last_updated = cache[pid].get('last_updated')
        if last_updated:
            last_updated_date = datetime.strptime(last_updated, '%Y-%m-%d')
            if (datetime.now() - last_updated_date).days <= CACHE_EXPIRY_DAYS:
                return cache[pid]['difficulty']

    # Otherwise, request the difficulty from Kattis
    url = f"https://open.kattis.com/problems/{pid}"
    response = requests.get(url)

    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'html.parser')
        difficulty_span = soup.find('span', class_='difficulty_number')
        if difficulty_span:
            difficulty = difficulty_span.text.strip()
            cache[pid] = {
                'difficulty': difficulty,
                'last_updated': get_current_date()
            }
            return difficulty
    return "N/A"

# Slug generation (useful if you need it for URL paths)
def generate_slug(heading):
    heading = heading.replace('##', '').strip()
    heading = re.sub(r'[^\w\s-]', '', heading)
    return heading.lower().replace(' ', '-')

# Table of contents generator (if needed)
def generate_table_of_contents(lines):
    toc = ["## Table of Contents\n"]
    for line in lines:
        if line.startswith('## ') and not line.startswith('## Table of Contents'):
            heading_text = line.strip().replace('##', '').strip()
            heading_slug = generate_slug(heading_text)
            toc.append(f"- [{heading_text}](#{heading_slug})\n")
    return toc
