import os

# Language definitions and their respective file extensions
LANGUAGES = [
    ('C++', '.cpp'),
    ('Python', '.py'),
]

class FileCounter:
    """Counts files based on language and extension."""
    def __init__(self, languages):
        self.languages = languages

    def count_files(self, directory):
        """Count files by extension for the given directory."""
        language_counts = {lang: 0 for lang, _ in self.languages}
        for root, _, files in os.walk(directory):
            for file in files:
                for lang, ext in self.languages:
                    if file.endswith(ext):
                        language_counts[lang] += 1
        return language_counts
class HTMLFormatter:
    """Formats the language statistics into a styled HTML table."""
    def format(self, language_counts):
        """Generate a styled HTML card for displaying results without extra spaces or newlines."""
        total_count = sum(language_counts.values())

        # Create a single-line HTML block to prevent Markdown formatting issues
        html = (
            '<div style="font-family: Arial, sans-serif; margin: 20px; width: 400px;">'
            '<div style="background-color: #007bff; color: white; padding: 15px; font-size: 20px; text-align: center; border-radius: 5px 5px 0 0;">'
            'Problem Solving Statistics'
            '</div>'
            '<div style="background-color: #f3f4f7; padding: 20px; border: 1px solid #ddd; border-top: none; border-radius: 0 0 5px 5px;">'
            '<table style="width: 100%; border-collapse: collapse; margin-top: 10px;">'
            '<thead style="background-color: #007bff; color: #ffffff;">'
            '<tr><th style="padding: 8px; border: 1px solid #ddd;">Language</th>'
            '<th style="padding: 8px; border: 1px solid #ddd;">Files Solved</th></tr>'
            '</thead><tbody>'
        )

        # Add each language count to the table
        for language, count in language_counts.items():
            html += (
                f'<tr>'
                f'<td style="padding: 8px; border: 1px solid #ddd; background-color: #e9ecef;">{language}</td>'
                f'<td style="padding: 8px; border: 1px solid #ddd; background-color: #ffffff;">{count}</td>'
                f'</tr>'
            )

        # Add total count row
        html += (
            '</tbody><tfoot>'
            f'<tr><th style="padding: 8px; border: 1px solid #ddd; background-color: #e9ecef;">Total</th>'
            f'<th style="padding: 8px; border: 1px solid #ddd; background-color: #ffffff;">{total_count}</th>'
            '</tr></tfoot></table></div></div>'
        )

        return html

class MarkdownFormatter:
    """Formats the language statistics into a Markdown table."""
    def format(self, language_counts):
        """Generate a Markdown table for displaying results."""
        total_count = sum(language_counts.values())

        # Use Markdown formatting with emoji
        markdown = "## 📊 Problem Solving Statistics\n\n"
        markdown += "| Language | Files Solved |\n"
        markdown += "|----------|--------------|\n"

        # Add each language count to the table
        for language, count in language_counts.items():
            markdown += f"| {language} | {count} |\n"

        # Add total count row
        markdown += f"| **Total** | **{total_count}** |\n"

        return markdown


class ReadmeUpdater:
    """Updates the README.md file with new language statistics."""
    def __init__(self, readme_path, formatter, counter):
        self.readme_path = readme_path
        self.formatter = formatter
        self.counter = counter

    def update_readme(self, directory):
        """Reads, updates, and writes back to the README file."""
        language_counts = self.counter.count_files(directory)

        html_card = self.formatter.format(language_counts)

        with open(self.readme_path, 'r') as file:
            readme_content = file.read()

        start_marker = "<!-- START_SOLVED_STATS -->"
        end_marker = "<!-- END_SOLVED_STATS -->"

        if start_marker in readme_content and end_marker in readme_content:
            before = readme_content.split(start_marker)[0]
            after = readme_content.split(end_marker)[1]
            updated_content = f"{before}{start_marker}\n{html_card}\n{end_marker}{after}"
            
            with open(self.readme_path, 'w') as file:
                file.write(updated_content)

            print("README.md updated successfully!")
        else:
            print("Markers not found in README.md")


if __name__ == "__main__":
    readme_path = os.path.join(os.getenv('GITHUB_WORKSPACE', ''), 'README.md')

    repo_directory = os.path.abspath(os.path.join(os.getcwd(), "../.."))
    file_counter = FileCounter(LANGUAGES)
    md_formatter = MarkdownFormatter()
    readme_updater = ReadmeUpdater(readme_path, md_formatter, file_counter)

    readme_updater.update_readme(repo_directory)
