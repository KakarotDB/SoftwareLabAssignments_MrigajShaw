# Assignment 4 (Bonus) - Interactive Student Grade & SGPA Calculator

This project is an interactive, beautiful, and fully functional SGPA calculator tailored for a typical Indian University / IIEST Shibpur grading system. 

## VIVA EXPLANATIONS

### 1. What is SGPA vs CGPA
- **SGPA (Semester Grade Point Average):** It represents a student's performance in a single semester. It is the weighted average of grade points obtained in all subjects registered by the student during that specific semester.
- **CGPA (Cumulative Grade Point Average):** It represents the overall performance up to a particular semester. It is calculated by taking the weighted average of all subjects across all semesters completed so far.

### 2. The Grading System Used
The application uses a standard 10-point grading scale commonly used in Indian institutions (like IIEST):
- **O (Outstanding):** 90-100 marks = 10 Grade Points
- **E (Excellent):** 80-89 marks = 9 Grade Points
- **A (Very Good):** 70-79 marks = 8 Grade Points
- **B (Good):** 60-69 marks = 7 Grade Points
- **C (Average):** 50-59 marks = 6 Grade Points
- **D (Satisfactory):** 40-49 marks = 5 Grade Points
- **F (Fail):** <40 marks = 0 Grade Points (Failing grade)

### 3. How the SGPA Formula Works
The SGPA is calculated using the formula:
`SGPA = Σ(Credits × Grade Points) / Σ(Credits)`

**Step-by-step Execution in the code:**
1. We loop through each valid subject row.
2. For each subject, we multiply the **Credits** by the respective **Grade Point** (obtained from the marks).
3. We keep a running sum of `Total Credits` and `Total Grade Points`.
4. Finally, we divide `Total Grade Points` by `Total Credits` to get the SGPA.

### 4. JavaScript Concepts Used
- **DOM Manipulation:** Used `document.getElementById` and `document.querySelectorAll` to read user inputs and update result tables, backgrounds, and badges.
- **Event Listeners:** `addEventListener` for button clicks (Calculate, Reset, Print, Export) and inline `onkeyup` to instantly show live grades as the user types.
- **Form Validation Techniques:** Checking `isNaN()`, bounds checking (`< 0` or `> 100`), empty string checks. Used CSS classes (`.error`) to visually flag problematic inputs.
- **CSS Class Manipulation:** Used `element.classList.add()` and `remove()` to dynamically change the webpage's theme (e.g., green for Distinction, red for Fail).
- **localStorage API:** Used `localStorage.setItem()` to persist the student details and results after calculation, and `localStorage.getItem()` to prompt the user to restore data upon reload.
- **Template Literals:** Backticks (\`) used extensively to generate dynamic HTML rows for the results table and subject inputs.
- **Array Methods:** `Array.find()` is used in `getGrade()` to locate the correct grade boundary. `Array.map().join('')` is used to efficiently render the table rows from an array of result objects.
- **CSS Transitions & Animations:** Manipulated body class to trigger smooth CSS background gradients and created a JS-driven animation loop using `requestAnimationFrame` for the SGPA counter.

### 5. How to Validate Forms in JavaScript
Form validation ensures data integrity before processing. In this project:
1. **Selection:** We retrieve the raw string value of an input field.
2. **Parsing & Trim:** We use `.trim()` for text fields to remove whitespace, and `parseFloat()` for numbers.
3. **Logic Checks:** We apply `if` conditions (e.g., `marks < 0 || marks > 100`).
4. **User Feedback:** If a check fails, we prevent the calculation (`return`), show an error message, and add a specific CSS class (like a red border) to the offending input to guide the user visually.
