import psycopg2
import re
import sys
import argparse
import os

# --- Configuration ---
# You can change these defaults to match your local PostgreSQL setup,
# or you can pass them as command-line arguments when running the script.
DB_HOST = "localhost"
DB_NAME = "lab_assignment_db"  # Change to your actual DB name
DB_USER = "postgres"  # Change to your actual username
DB_PASS = "MrigajSuman@2015"  # Change to your actual password
# ---------------------

def escape_latex(text):
    """Escapes special LaTeX characters in strings to prevent compilation errors."""
    if text is None:
        return "NULL"
    text = str(text)
    # Characters that need escaping in standard text mode
    chars = {
        '&': r'\&',
        '%': r'\%',
        '$': r'\$',
        '#': r'\#',
        '_': r'\_',
        '{': r'\{',
        '}': r'\}',
        '~': r'\textasciitilde{}',
        '^': r'\textasciicircum{}',
        '\\': r'\textbackslash{}',
    }
    regex = re.compile('|'.join(re.escape(str(key)) for key in chars.keys()))
    return regex.sub(lambda match: chars[match.group(0)], text)

def parse_sql_file(filepath):
    """Parses the SQL file and extracts query blocks separated by '-- Q...'"""
    queries = []
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    # Split the file by lines starting with '-- Q' (e.g., '-- Q1:', '-- Q2')
    blocks = re.split(r'^(?=-- Q\d+)', content, flags=re.MULTILINE)
    
    for block in blocks:
        block = block.strip()
        if not block:
            continue
            
        lines = block.split('\n')
        title = "Query"
        sql_lines = []
        
        for line in lines:
            if line.startswith('-- Q'):
                title = line.strip('- ').strip()
            elif line.startswith('--'):
                # Include other comments as part of the SQL block for reference
                sql_lines.append(line)
            else:
                # Keep SQL lines and internal blank lines
                if line.strip() or sql_lines: 
                    sql_lines.append(line)
        
        sql = '\n'.join(sql_lines).strip()
        if sql:
            queries.append({'title': title, 'sql': sql})
            
    return queries

def execute_silent_script(filepath, conn):
    """Executes a SQL script silently without formatting output (used for resetting DB state)"""
    if not os.path.exists(filepath):
        return
    with open(filepath, 'r', encoding='utf-8') as f:
        sql = f.read()
    try:
        cursor = conn.cursor()
        cursor.execute(sql)
        conn.commit()
        cursor.close()
    except Exception as e:
        conn.rollback()
        print(f"  -> Error running setup script {filepath}:\n{e}")

def execute_and_format(queries, conn, setup_scripts=None):
    """Executes queries and formats the results into LaTeX strings."""
    cursor = conn.cursor()
    latex_output = []
    
    for q in queries:
        title = q['title']
        full_sql = q['sql']
        
        # Add Title and SQL Code block
        latex_output.append(rf"\subsection*{{{escape_latex(title)}}}")
        latex_output.append(r"\begin{lstlisting}[language=SQL]")
        latex_output.append(full_sql)
        latex_output.append(r"\end{lstlisting}")
        latex_output.append(r"\vspace{0.3cm}")
        
        print(f"    Executing: {title}...")
        
        # Reset DB state before EVERY query block to guarantee perfect isolation
        if setup_scripts:
            for script in setup_scripts:
                execute_silent_script(script, conn)
                
        # Split the block into individual statements by semicolon
        # We only consider statements that actually contain text
        statements = [s.strip() for s in full_sql.split(';') if s.strip()]
        
        for statement in statements:
            try:
                cursor.execute(statement)
                
                try:
                    results = cursor.fetchall()
                    col_names = [desc[0] for desc in cursor.description]
                    
                    if not results:
                        latex_output.append(r"\textit{Statement executed successfully. (0 rows returned)}\vspace{0.2cm}")
                    else:
                        latex_output.append(r"\textbf{Output:}\vspace{0.2cm}")
                        latex_output.append(r"\begin{center}")
                        align_str = "|" + "|".join(["l"] * len(col_names)) + "|"
                        latex_output.append(rf"\begin{{tabular}}{{{align_str}}}")
                        latex_output.append(r"\hline")
                        
                        escaped_headers = [escape_latex(col) for col in col_names]
                        latex_output.append(" & ".join([rf"\textbf{{{h}}}" for h in escaped_headers]) + r" \\ \hline")
                        
                        for row in results:
                            escaped_row = [escape_latex(item) for item in row]
                            latex_output.append(" & ".join(escaped_row) + r" \\ \hline")
                            
                        latex_output.append(r"\end{tabular}")
                        latex_output.append(r"\end{center}")
                        
                except psycopg2.ProgrammingError:
                    rowcount = cursor.rowcount
                    # Avoid showing -1 for DDL statements where rowcount doesn't apply
                    if rowcount >= 0:
                        msg = f"Statement executed successfully. Rows affected: {rowcount}"
                    else:
                        msg = f"Statement executed successfully."
                    latex_output.append(rf"\textit{{{escape_latex(msg)}}}\vspace{{0.2cm}}")
                    
                conn.commit()
                
            except Exception as e:
                conn.rollback()
                error_msg = str(e).strip()
                latex_output.append(rf"\textcolor{{red}}{{\textbf{{Error:}} {escape_latex(error_msg)}}}\vspace{{0.2cm}}")
            
        latex_output.append(r"\newpage")
        
    cursor.close()
    return "\n".join(latex_output)

def generate_latex_document(latex_body, output_file, assignment_name):
    """Wraps the body in a complete compilable LaTeX document and writes to file."""
    doc = rf"""\documentclass[11pt, a4paper]{{article}}
\usepackage[utf8]{{inputenc}}
\usepackage[margin=1in]{{geometry}}
\usepackage{{listings}}
\usepackage{{xcolor}}
\usepackage{{tabularx}}

% Configure SQL code block styling
\lstset{{
    basicstyle=\ttfamily\small,
    keywordstyle=\color{{blue}}\bfseries,
    stringstyle=\color{{red!70!black}},
    commentstyle=\color{{green!60!black}}\itshape,
    frame=single,
    backgroundcolor=\color{{gray!5}},
    breaklines=true,
    showstringspaces=false
}}

\title{{{escape_latex(assignment_name)} Lab Report}}
\author{{Student Name}}
\date{{\today}}

\begin{{document}}

\maketitle

{latex_body}

\end{{document}}
"""
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(doc)
    print(f"\nSuccessfully generated {output_file}")

def main():
    parser = argparse.ArgumentParser(description="Generate a complete LaTeX report for an entire Assignment directory.")
    parser.add_argument("assignment_dir", help="Path to the Assignment directory (e.g., Assignment1)")
    parser.add_argument("output_tex", help="Path to the output TEX file (e.g., Assignment1_Report.tex)")
    
    # Optional arguments
    parser.add_argument("--setup-scripts", nargs='*', help="Paths to SQL files to run BEFORE processing each problem folder to reset the DB state (e.g., Assignment1/Problem1/TableCreation.sql Assignment1/Problem1/TableInsertion.sql)")
    parser.add_argument("--dbname", default=DB_NAME, help="Database name")
    parser.add_argument("--user", default=DB_USER, help="Database user")
    parser.add_argument("--password", default=DB_PASS, help="Database password")
    parser.add_argument("--host", default=DB_HOST, help="Database host")
    
    args = parser.parse_args()
    
    if not os.path.isdir(args.assignment_dir):
        print(f"Error: Directory '{args.assignment_dir}' does not exist.")
        sys.exit(1)
        
    print(f"Connecting to database '{args.dbname}' at {args.host}...")
    try:
        conn = psycopg2.connect(
            dbname=args.dbname,
            user=args.user,
            password=args.password,
            host=args.host
        )
    except Exception as e:
        print(f"Failed to connect to database. Did you update the credentials?\nError: {e}")
        sys.exit(1)
        
    # Find all Problem folders inside the assignment directory
    problem_folders = [d for d in os.listdir(args.assignment_dir) if os.path.isdir(os.path.join(args.assignment_dir, d)) and d.lower().startswith('problem')]
    
    # Sort them naturally (Problem1, Problem2, ...)
    def get_num(name):
        match = re.search(r'\d+', name)
        return int(match.group()) if match else 0
    problem_folders.sort(key=get_num)
    
    if not problem_folders:
        print(f"No 'ProblemX' folders found inside '{args.assignment_dir}'.")
        sys.exit(1)
        
    latex_body_parts = []
    assignment_name = os.path.basename(os.path.normpath(args.assignment_dir))
    
    for problem in problem_folders:
        queries_file = os.path.join(args.assignment_dir, problem, "Queries.sql")
        
        if os.path.exists(queries_file):
            print(f"\n=== Processing {problem} ===")
            
            latex_body_parts.append(rf"\section{{{escape_latex(problem)}}}")
            
            queries = parse_sql_file(queries_file)
            print(f"Found {len(queries)} query blocks. Executing against DB with query isolation...")
            
            body = execute_and_format(queries, conn, args.setup_scripts)
            latex_body_parts.append(body)
            
    conn.close()
    
    generate_latex_document("\n".join(latex_body_parts), args.output_tex, assignment_name)

if __name__ == "__main__":
    main()
