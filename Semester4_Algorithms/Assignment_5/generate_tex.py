import os
import re

# ==========================================
#   USER CONFIGURATION
# ==========================================
ASSIGNMENT_TITLE = "Assignment 5"
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
    base = os.path.dirname(os.path.abspath(__file__))
    all_items = os.listdir(base)
    problem_dirs = [d for d in all_items if os.path.isdir(os.path.join(base, d)) and d.lower().startswith("problem")]
    
    problem_dirs.sort(key=natural_sort_key)

    if not problem_dirs:
        print("No 'ProblemX' directories found!")
        return

    latex_content = LATEX_HEADER
    problem_blocks = [] # Added list to hold problem content

    for p_dir in problem_dirs:
        try:
            p_num = re.search(r'\d+', p_dir).group()
        except AttributeError:
            p_num = "?"

        block = f"% --- {p_dir} ---\n"
        block += f"\\section*{{Problem {p_num}}}\n"
        block += f"\\textbf{{Problem Statement:}} [See code below]\n"

        files = sorted(os.listdir(os.path.join(base, p_dir)))
        code_files = [f for f in files if f.endswith(('.c', '.cpp', '.py', '.java', '.h'))]
        
        if code_files:
            block += f"\\subsection*{{Code}}\n"
            for code_file in code_files:
                # FIX 1: Construct a relative path directly
                rel_path = f"{p_dir}/{code_file}"
                block += f"\\lstinputlisting[language=C]{{{rel_path}}}\n"

        image_files = [f for f in files if f.endswith(('.png', '.jpg', '.jpeg'))]
        
        if image_files:
            block += f"\\subsection*{{Output}}\n"
            for img_file in image_files:
                # FIX 1: Construct a relative path directly
                rel_path = f"{p_dir}/{img_file}"
                block += "\\begin{figure}[H]\n"
                block += "    \\centering\n"
                block += f"    \\includegraphics[width=0.9\\textwidth]{{{rel_path}}}\n"
                block += "\\end{figure}\n"

        problem_blocks.append(block)

    # FIX 2: Join blocks with a page break, avoiding a trailing blank page
    latex_content += "\n\\newpage\n\n".join(problem_blocks)
    
    latex_content += "\n" + LATEX_FOOTER

    output_path = os.path.join(base, OUTPUT_FILENAME)
    # Added utf-8 encoding just to be safe with LaTeX special characters
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(latex_content)
    
    print(f"Success! Scanned {len(problem_dirs)} problem folders.")
    print(f"Generated: {output_path}")

if __name__ == "__main__":
    generate_latex()