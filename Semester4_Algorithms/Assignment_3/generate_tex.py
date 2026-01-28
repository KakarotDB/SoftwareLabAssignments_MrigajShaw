import os
import re

# ==========================================
#   USER CONFIGURATION
# ==========================================
ASSIGNMENT_TITLE = "Assignment 4"
AUTHOR_NAME = "Mrigaj Shaw"      # Leave blank "" if handwriting
ROLL_NO = "2024CSB041"         # Leave blank "" if handwriting
OUTPUT_FILENAME = "main.tex"

# ==========================================
#   LATEX HEADER
# ==========================================
LATEX_HEADER = r"""\documentclass[a4paper,12pt]{article}
\usepackage[utf8]{inputenc}
\usepackage{geometry}
\usepackage{fancyhdr}
\usepackage{listings}
\usepackage{xcolor}
\usepackage{graphicx}
\usepackage{float}

% Margins
\geometry{left=15mm, right=15mm, top=25mm, bottom=15mm}

% Header/Footer
\pagestyle{fancy}
\fancyhf{}
\renewcommand{\headrulewidth}{0pt}
\rfoot{Page \thepage}

\fancypagestyle{firstpage}{
    \fancyhf{}
    \lhead{
        \small \textbf{Name:} """ + AUTHOR_NAME + r""" \\ 
        \small \textbf{Roll No:} """ + ROLL_NO + r"""
    }
    \chead{\LARGE \textbf{""" + ASSIGNMENT_TITLE + r"""}} 
    \rfoot{Page \thepage}
    \renewcommand{\headrulewidth}{1pt}
}

% Code Style
\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{backcolour}{rgb}{0.95,0.95,0.92}

\lstdefinestyle{MyCodeStyle}{
    backgroundcolor=\color{backcolour},   
    commentstyle=\color{codegreen},
    keywordstyle=\color{magenta},
    numberstyle=\tiny\color{codegray},
    stringstyle=\color{codepurple},
    basicstyle=\ttfamily\footnotesize,
    breakatwhitespace=false,         
    breaklines=true,                 
    keepspaces=true,                 
    numbers=left,                    
    numbersep=5pt,                  
    showspaces=false,                
    showstringspaces=false,
    showtabs=false,                  
    tabsize=4
}
\lstset{style=MyCodeStyle}

\begin{document}
\thispagestyle{firstpage}
"""

LATEX_FOOTER = r"""
\end{document}
"""

def natural_sort_key(s):
    """Sorts strings with numbers naturally (Problem1, Problem2, Problem10)."""
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def generate_latex():
    # 1. Find all directories starting with "Problem"
    all_items = os.listdir('.')
    problem_dirs = [d for d in all_items if os.path.isdir(d) and d.lower().startswith("problem")]
    
    # 2. Sort them naturally (so Problem10 comes after Problem9)
    problem_dirs.sort(key=natural_sort_key)

    if not problem_dirs:
        print("No 'ProblemX' directories found!")
        return

    latex_content = LATEX_HEADER

    for p_dir in problem_dirs:
        # Extract the number from the folder name for the title
        # e.g., "Problem1" -> "1"
        try:
            p_num = re.search(r'\d+', p_dir).group()
        except AttributeError:
            p_num = "?"

        latex_content += f"\n% --- {p_dir} ---\n"
        latex_content += f"\\section*{{Problem {p_num}}}\n"
        latex_content += f"\\textbf{{Problem Statement:}} [See code below]\n"

        # --- PROCESS CODE FILES ---
        files = sorted(os.listdir(p_dir))
        code_files = [f for f in files if f.endswith(('.c', '.cpp', '.py', '.java', '.h'))]
        
        if code_files:
            latex_content += f"\\subsection*{{Code}}\n"
            for code_file in code_files:
                # LaTeX requires forward slashes for paths
                file_path = f"{p_dir}/{code_file}"
                
                # Escape underscores in filenames for the caption label
                caption_name = code_file.replace('_', '\\_')
                
                # latex_content += f"\\textbf{{File: {caption_name}}}\n"
                latex_content += f"\\lstinputlisting[language=C]{{{file_path}}}\n"

        # --- PROCESS IMAGE FILES ---
        image_files = [f for f in files if f.endswith(('.png', '.jpg', '.jpeg'))]
        
        if image_files:
            latex_content += f"\\subsection*{{Output}}\n"
            for img_file in image_files:
                file_path = f"{p_dir}/{img_file}"
                latex_content += "\\begin{figure}[H]\n"
                latex_content += "    \\centering\n"
                latex_content += f"    \\includegraphics[width=0.9\\textwidth]{{{file_path}}}\n"
                latex_content += "\\end{figure}\n"

        latex_content += "\\newpage\n"

    latex_content += LATEX_FOOTER

    # Write output
    with open(OUTPUT_FILENAME, "w") as f:
        f.write(latex_content)
    
    print(f"Success! Scanned {len(problem_dirs)} problem folders.")
    print(f"Generated: {OUTPUT_FILENAME}")

if __name__ == "__main__":
    generate_latex()
