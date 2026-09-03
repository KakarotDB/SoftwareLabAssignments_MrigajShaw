/**
 * Student Grade & SGPA Calculator
 * This script contains the logic for calculating SGPA, validating inputs,
 * manipulating the DOM, and storing data using localStorage.
 */

// Grading System Constants (10-point scale typically used in Indian Universities like IIEST)
const GRADE_SCALE = [
    { min: 90, max: 100, letter: 'O', point: 10, label: 'Outstanding' },
    { min: 80, max: 89,  letter: 'E', point: 9,  label: 'Excellent' },
    { min: 70, max: 79,  letter: 'A', point: 8,  label: 'Very Good' },
    { min: 60, max: 69,  letter: 'B', point: 7,  label: 'Good' },
    { min: 50, max: 59,  letter: 'C', point: 6,  label: 'Average' },
    { min: 40, max: 49,  letter: 'D', point: 5,  label: 'Satisfactory' },
    { min: 0,  max: 39,  letter: 'F', point: 0,  label: 'Fail' } // <40 fails.
];

const NUM_SUBJECTS = 5;

/**
 * Initializes the application on DOM load.
 * Sets up the subject input fields dynamically, binds event listeners, 
 * and attempts to load previously saved calculation data from localStorage.
 */
document.addEventListener('DOMContentLoaded', () => {
    generateSubjectFields();
    loadFromStorage();

    // Event listeners attached via DOM manipulation
    document.getElementById('calculateBtn').addEventListener('click', handleCalculate);
    document.getElementById('resetBtn').addEventListener('click', resetForm);
    document.getElementById('printBtn').addEventListener('click', () => window.print());
    document.getElementById('exportBtn').addEventListener('click', exportToText);
});

/**
 * Dynamically creates 5 subject input rows in the DOM using Template Literals.
 */
function generateSubjectFields() {
    const container = document.getElementById('subjectsContainer');
    container.innerHTML = ''; // Clear existing DOM to prevent duplicates

    for (let i = 1; i <= NUM_SUBJECTS; i++) {
        // Template literal to build HTML dynamically and clearly
        const html = `
            <div class="subject-row">
                <div class="form-group">
                    <label>Subject ${i} Name</label>
                    <input type="text" class="sub-name" id="subName${i}" placeholder="e.g. Web Tech">
                </div>
                <div class="form-group">
                    <label>Credits</label>
                    <input type="number" class="sub-credit" id="subCredit${i}" min="1" max="4" placeholder="1-4">
                </div>
                <div class="form-group">
                    <label>Marks (0-100)</label>
                    <input type="number" class="sub-marks" id="subMarks${i}" min="0" max="100" placeholder="0-100" onkeyup="updateLiveGrade(${i})">
                </div>
                <div class="form-group">
                    <label>Grade</label>
                    <div class="live-grade-badge" id="liveGrade${i}">N/A</div>
                </div>
            </div>
        `;
        container.insertAdjacentHTML('beforeend', html);
    }
}

/**
 * Computes the grade details based on the provided marks using the GRADE_SCALE array.
 * @param {number} marks - The marks obtained (0-100).
 * @returns {Object|null} Grade object matching the range or null if invalid.
 */
function getGrade(marks) {
    if (marks < 0 || marks > 100 || isNaN(marks)) return null;
    // Array.find() returns the first element that satisfies the condition
    return GRADE_SCALE.find(g => marks >= g.min && marks <= g.max);
}

/**
 * Updates the live grade badge visually as the user types their marks.
 * Triggered by the onkeyup event inline.
 * @param {number} index - The index of the subject row to update.
 */
function updateLiveGrade(index) {
    const marksInput = document.getElementById(`subMarks${index}`);
    const badge = document.getElementById(`liveGrade${index}`);
    const marks = parseFloat(marksInput.value);

    // Reset old grade classes using classList assignment
    badge.className = 'live-grade-badge'; 

    if (isNaN(marks) || marksInput.value === '') {
        badge.textContent = 'N/A';
        return;
    }

    if (marks < 0 || marks > 100) {
        badge.textContent = 'Invalid';
        badge.style.backgroundColor = 'red';
        return;
    }

    const grade = getGrade(marks);
    if (grade) {
        badge.textContent = `${grade.letter} (${grade.point})`;
        badge.classList.add(`grade-${grade.letter}`);
        badge.style.backgroundColor = ''; // Clear inline red error state
    }
}

/**
 * Main handler for SGPA Calculation logic when Calculate is clicked.
 * Performs deep validation, computes the SGPA, and triggers UI updates.
 */
function handleCalculate() {
    clearErrors(); // DOM Manipulation to clean error states
    document.body.className = ''; // Reset body background class
    const errorDiv = document.getElementById('error-message');

    let totalCredits = 0;
    let totalGradePoints = 0;
    let totalMarks = 0;
    let validSubjectsCount = 0;
    let hasFailed = false;
    let results = []; // Array to store processed subjects

    // Validation & Computation Loop
    for (let i = 1; i <= NUM_SUBJECTS; i++) {
        const nameInput = document.getElementById(`subName${i}`);
        const creditInput = document.getElementById(`subCredit${i}`);
        const marksInput = document.getElementById(`subMarks${i}`);
        
        const name = nameInput.value.trim();
        const credit = parseFloat(creditInput.value);
        const marks = parseFloat(marksInput.value);
        
        // Skip entirely empty rows so user doesn't have to fill all 5 strictly
        if (!name && isNaN(credit) && isNaN(marks)) {
            continue; 
        }

        // Validate individual fields and highlight if error (CSS class manipulation)
        let rowValid = true;
        if (!name) { nameInput.classList.add('error'); rowValid = false; }
        if (isNaN(credit) || credit < 1 || credit > 4) { creditInput.classList.add('error'); rowValid = false; }
        if (isNaN(marks) || marks < 0 || marks > 100) { marksInput.classList.add('error'); rowValid = false; }
        
        if (!rowValid) {
            errorDiv.textContent = 'Please fix the highlighted fields (Credits 1-4, Marks 0-100, Name required).';
            return; // Halt calculation process
        }

        const grade = getGrade(marks);
        const subjectGradePoints = grade.point * credit; // GP * Credits
        
        if (grade.letter === 'F') {
            hasFailed = true; // Overall fail if any subject is <40
        }

        totalCredits += credit;
        totalGradePoints += subjectGradePoints; // Σ(Credits × Grade Points)
        totalMarks += marks;
        validSubjectsCount++;

        results.push({ name, credit, marks, grade });
    }

    if (validSubjectsCount === 0) {
        errorDiv.textContent = 'Please fill out at least one subject to calculate SGPA.';
        return;
    }

    // --- SGPA Formula Execution ---
    // SGPA = Σ(Credits * GP) / Σ(Credits)
    const sgpa = (totalGradePoints / totalCredits).toFixed(2);
    const percentage = ((totalMarks / (validSubjectsCount * 100)) * 100).toFixed(2);

    // Save to local storage for persistence
    saveToStorage({ sgpa, percentage, totalMarks, results, hasFailed, validSubjectsCount });

    // Update Results UI with dynamic states
    displayResults(sgpa, percentage, totalMarks, results, hasFailed, validSubjectsCount);
}

/**
 * Clears all error highlights (.error class) from the form fields.
 */
function clearErrors() {
    document.querySelectorAll('.error').forEach(el => el.classList.remove('error'));
    document.getElementById('error-message').textContent = '';
}

/**
 * Updates the DOM to display the computed results and applies dynamic background styling based on SGPA.
 */
function displayResults(sgpa, percentage, totalMarks, results, hasFailed, subjectsCount) {
    const resultSection = document.getElementById('resultSection');
    const tableBody = document.getElementById('resultTableBody');
    const statusDiv = document.getElementById('resultStatus');
    const sgpaSpan = document.getElementById('sgpaValue');
    const overallStatusDiv = document.getElementById('overallStatus');
    
    // Unhide results (DOM Manipulation)
    resultSection.classList.remove('hidden');

    // Populate Table using Array.map and join for fast bulk DOM injection
    tableBody.innerHTML = results.map(res => `
        <tr>
            <td>${res.name}</td>
            <td>${res.credit}</td>
            <td>${res.marks}</td>
            <td>${res.marks}%</td>
            <td><span class="live-grade-badge grade-${res.grade.letter}">${res.grade.letter}</span></td>
            <td>${res.grade.point}</td>
        </tr>
    `).join('');

    document.getElementById('totalMarksDisplay').textContent = `${totalMarks} / ${subjectsCount * 100}`;
    document.getElementById('totalPercentageDisplay').textContent = percentage;

    // Dynamic Styling logic utilizing DOM classList manipulation
    let statusText = '';
    let letterGradeOverall = '';

    if (hasFailed) {
        document.body.className = 'bg-fail'; // CSS transition turns background Red
        statusText = '❌ FAIL - Contact Advisor';
        statusDiv.style.color = 'var(--grade-f)';
        letterGradeOverall = 'F';
    } else {
        if (sgpa >= 8.5) {
            document.body.className = 'bg-distinction'; // Green
            statusText = '🎉 Distinction!';
            statusDiv.style.color = 'var(--grade-o)';
            letterGradeOverall = 'O/E';
            triggerConfetti(); // Bonus animation
        } else if (sgpa >= 6.0) {
            document.body.className = 'bg-first-class'; // Blue
            statusText = '✅ First Class';
            statusDiv.style.color = 'var(--grade-a)';
            letterGradeOverall = 'A/B';
        } else if (sgpa >= 5.0) {
            document.body.className = 'bg-second-class'; // Yellow
            statusText = '📋 Second Class';
            statusDiv.style.color = 'var(--grade-c)';
            letterGradeOverall = 'C/D';
        } else {
            // Edge cases passing with low SGPA without triggering a fail
            document.body.className = '';
            statusText = 'Passed';
            statusDiv.style.color = 'var(--text-main)';
            letterGradeOverall = 'Pass';
        }
    }

    statusDiv.textContent = statusText;
    overallStatusDiv.textContent = `Overall Grade: ${letterGradeOverall}`;

    // Animate the SGPA text visually instead of instantly snapping
    animateValue(sgpaSpan, 0, parseFloat(sgpa), 1000);
    
    // Smooth scroll down to view results
    resultSection.scrollIntoView({ behavior: 'smooth' });
}

/**
 * JS-driven animation loop to increment a number from 'start' to 'end' over 'duration' ms.
 */
function animateValue(obj, start, end, duration) {
    let startTimestamp = null;
    const step = (timestamp) => {
        if (!startTimestamp) startTimestamp = timestamp;
        const progress = Math.min((timestamp - startTimestamp) / duration, 1);
        obj.innerHTML = (progress * (end - start) + start).toFixed(2);
        if (progress < 1) {
            window.requestAnimationFrame(step);
        }
    };
    window.requestAnimationFrame(step);
}

/**
 * Saves non-DOM pure serialized data to window.localStorage.
 */
function saveToStorage(data) {
    const studentInfo = {
        name: document.getElementById('studentName').value,
        roll: document.getElementById('rollNumber').value,
        sem: document.getElementById('semester').value
    };
    const payload = { studentInfo, data };
    localStorage.setItem('sgpa_last_calculation', JSON.stringify(payload));
}

/**
 * Prompts user and restores previous calculation student metadata from localStorage.
 */
function loadFromStorage() {
    const saved = localStorage.getItem('sgpa_last_calculation');
    if (saved) {
        const parsed = JSON.parse(saved);
        if (confirm('A previous calculation record was found. Do you want to restore the student details?')) {
            document.getElementById('studentName').value = parsed.studentInfo.name || '';
            document.getElementById('rollNumber').value = parsed.studentInfo.roll || '';
            document.getElementById('semester').value = parsed.studentInfo.sem || '';
        } else {
            localStorage.removeItem('sgpa_last_calculation');
        }
    }
}

/**
 * Resets the DOM values back to their defaults, hiding results and clearing errors.
 */
function resetForm() {
    document.querySelectorAll('input').forEach(input => input.value = '');
    document.querySelectorAll('.live-grade-badge').forEach(badge => {
        badge.className = 'live-grade-badge';
        badge.textContent = 'N/A';
        badge.style.backgroundColor = '';
    });
    document.getElementById('resultSection').classList.add('hidden');
    document.body.className = '';
    clearErrors();
}

/**
 * Export results formatting to a downloadable plain text (.txt) file using Blob.
 */
function exportToText() {
    const studentName = document.getElementById('studentName').value || 'Student';
    const roll = document.getElementById('rollNumber').value || 'N/A';
    const sgpa = document.getElementById('sgpaValue').textContent;
    
    let content = `--- IIEST SHIBPUR SGPA RESULT ---\n`;
    content += `Name: ${studentName}\nRoll No: ${roll}\n\n`;
    content += `SGPA: ${sgpa}\n`;
    content += `Status: ${document.getElementById('resultStatus').textContent}\n`;
    
    // Convert text to Blob and trigger DOM download
    const blob = new Blob([content], { type: 'text/plain' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = `${studentName.replace(/\s+/g, '_')}_Result.txt`;
    a.click();
    URL.revokeObjectURL(url); // Memory cleanup
}

/**
 * Injects multiple div elements that fall down the screen via CSS animation.
 */
function triggerConfetti() {
    for (let i = 0; i < 50; i++) {
        const confetti = document.createElement('div');
        confetti.className = 'confetti';
        confetti.style.left = Math.random() * 100 + 'vw';
        confetti.style.backgroundColor = `hsl(${Math.random() * 360}, 100%, 50%)`;
        // Randomized fall speed
        confetti.style.animation = `fall ${Math.random() * 3 + 2}s linear forwards`;
        document.body.appendChild(confetti);
        
        // Remove from DOM when animation finishes
        setTimeout(() => confetti.remove(), 5000);
    }
}
