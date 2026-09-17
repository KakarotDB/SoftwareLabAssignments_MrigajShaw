async function fetchHello() {
    const res = await fetch('api/process.php?action=hello');
    const data = await res.json();
    document.getElementById('q1-output').innerText = data.data;
}

async function fetchGrade() {
    const marks = document.getElementById('q2-marks').value;
    const body = new URLSearchParams({ action: 'grade', marks });
    const res = await fetch('api/process.php', { method: 'POST', body });
    const data = await res.json();
    document.getElementById('q2-output').innerText = data.data;
}

async function fetchOddNumbers() {
    const n = document.getElementById('q3-n').value;
    const body = new URLSearchParams({ action: 'odd_numbers', n });
    const res = await fetch('api/process.php', { method: 'POST', body });
    const data = await res.json();
    document.getElementById('q3-output').innerText = "Odd Numbers: " + data.data.join(', ');
}

async function fetchSortedNumbers() {
    const input = document.getElementById('q4i-numbers').value;
    const numbersArray = input.split(',').map(n => parseFloat(n.trim())).filter(n => !isNaN(n));
    const body = new URLSearchParams({ action: 'sort_numbers', numbers: JSON.stringify(numbersArray) });
    const res = await fetch('api/process.php', { method: 'POST', body });
    const data = await res.json();
    document.getElementById('q4i-output').innerText = "Sorted: " + data.data.join(', ');
}

async function fetchAnimalNames() {
    const n = document.getElementById('q4ii-n').value;
    const body = new URLSearchParams({ action: 'animal_names', n });
    const res = await fetch('api/process.php', { method: 'POST', body });
    const data = await res.json();
    document.getElementById('q4ii-output').innerText = "Animals: " + data.data.join(', ');
}

document.getElementById('feedback-form').addEventListener('submit', async function (e) {
    e.preventDefault();
    const formData = new FormData(this);
    formData.append('action', 'form_feedback');

    const res = await fetch('api/process.php', { method: 'POST', body: formData });
    const data = await res.json();

    let outputHtml = "<strong>Server Feedback Response:</strong><ul>";
    for (const [key, val] of Object.entries(data.data)) {
        outputHtml += `<li><strong>${key}:</strong> ${val}</li>`;
    }
    outputHtml += "</ul>";
    document.getElementById('q5-output').innerHTML = outputHtml;
});

async function fetchAnimalImages() {
    const n = document.getElementById('q6-n').value;
    const body = new URLSearchParams({ action: 'animal_images', n });
    const res = await fetch('api/process.php', { method: 'POST', body });
    const data = await res.json();

    const galleryDiv = document.getElementById('q6-output');
    galleryDiv.innerHTML = '';
    data.data.forEach(img => {
        const item = document.createElement('div');
        item.style.textAlign = 'center';
        item.innerHTML = `<img src="${img.url}" alt="${img.name}" style="width:120px; height:120px; object-fit:cover; border-radius:8px;"><p>${img.name}</p>`;
        galleryDiv.appendChild(item);
    });
}

async function fetchDatabaseData() {
    const res = await fetch('api/process.php?action=db_query');
    const data = await res.json();
    document.getElementById('q7-output').innerText = JSON.stringify(data, null, 2);
}

async function fetchSubjectMarks() {
    const marksObj = {
        Math: parseFloat(document.getElementById('q8-math').value || 0),
        Physics: parseFloat(document.getElementById('q8-physics').value || 0),
        CS: parseFloat(document.getElementById('q8-cs').value || 0)
    };

    const body = new URLSearchParams({ action: 'subject_marks', subject_marks: JSON.stringify(marksObj) });
    const res = await fetch('api/process.php', { method: 'POST', body });
    const data = await res.json();

    const result = data.data;
    document.getElementById('q8-output').innerHTML = `
        <p><strong>Total Marks:</strong> ${result.total}</p>
        <p><strong>Average:</strong> ${result.average}</p>
        <p><strong>Overall Grade:</strong> ${result.overall_grade}</p>
    `;
}
