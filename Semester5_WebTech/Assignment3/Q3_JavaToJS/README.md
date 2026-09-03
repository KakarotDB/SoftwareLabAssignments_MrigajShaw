# Bank Account Management System (Java to JS Conversion)

Assignment 3 - Semester 5 Web Technology
Created by: Mrigaj Shaw

This repository contains a Bank Account Management System implemented first in Java (Core OOP) and then converted to JavaScript (ES6) with a beautiful Web UI.

## A. Java vs JavaScript Differences (Viva Reference)

When converting this project from Java to JavaScript, several key differences were observed and applied:

1. **Typing System**: 
   - **Java** is statically typed (`int`, `double`, `String`). Variables must declare their type.
   - **JavaScript** is dynamically typed (`let`, `const`, `var`). Variables infer type at runtime.
2. **Execution**:
   - **Java** is a compiled language (compiled to bytecode, runs on JVM).
   - **JavaScript** is an interpreted language (runs directly in the browser engine like V8).
3. **OOP Paradigm**:
   - **Java** uses traditional class-based OOP.
   - **JavaScript** uses prototype-based OOP. The `class` syntax introduced in ES6 is "syntactic sugar" over prototypes.
4. **Entry Point**:
   - **Java** requires a `public static void main(String[] args)` method to start execution.
   - **JavaScript** has no strict main method; code is executed top-to-bottom as it is loaded by the browser.
5. **Output**:
   - **Java**: `System.out.println()` outputs to the console.
   - **JavaScript**: `console.log()` outputs to browser console, but for UI we use DOM manipulation (e.g. `document.getElementById().innerText`).
6. **Input**:
   - **Java**: Uses `Scanner` class (`Scanner.nextLine()`).
   - **JavaScript**: Uses HTML form inputs (`document.getElementById().value`) or `prompt()`.
7. **Error Handling**:
   - **Java**: Explicit `throws Exception` in method signatures and strict checked exceptions.
   - **JavaScript**: Uses `try-catch` blocks without method signature requirements.

## B. How to Deploy to GitHub Pages

GitHub Pages is an excellent, free hosting service for static websites (HTML/CSS/JS). It serves files directly from a GitHub repository.

**Steps to deploy:**
1. **Create an account:** Go to github.com and sign up.
2. **Create repository:** Click "New" repository, name it `assignment3-q3` (public).
3. **Upload files:** Upload `index.html`, `style.css`, `bank_account.js`, `README.md`, and `COMPARISON.md`. Commit changes.
4. **Enable Pages:** Go to repository **Settings** > **Pages** (on the left sidebar).
5. **Select branch:** Under "Build and deployment", select the `main` branch and `/root` folder. Click Save.
6. **Access site:** After a minute or two, your site will be live at `https://[your-username].github.io/assignment3-q3`.
