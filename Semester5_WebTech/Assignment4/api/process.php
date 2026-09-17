<?php
header("Content-Type: application/json; charset=UTF-8");
require_once __DIR__ . '/../includes/functions.php';

$action = $_REQUEST['action'] ?? '';
$response = ['success' => false, 'message' => 'Invalid action'];

switch ($action) {
    case 'hello':
        $response = ['success' => true, 'data' => sayHello()];
        break;

    case 'grade':
        $marks = $_POST['marks'] ?? 0;
        $response = ['success' => true, 'data' => calculateGrade($marks)];
        break;

    case 'odd_numbers':
        $n = $_POST['n'] ?? 0;
        $response = ['success' => true, 'data' => getOddNumbers($n)];
        break;

    case 'sort_numbers':
        $numbers = json_decode($_POST['numbers'] ?? '[]', true);
        $response = ['success' => true, 'data' => sortNumbers($numbers)];
        break;

    case 'animal_names':
        $n = $_POST['n'] ?? 0;
        $response = ['success' => true, 'data' => getAnimalNames($n)];
        break;

    case 'form_feedback':
        $feedback = processFormFeedback($_POST, $_FILES);
        $response = ['success' => true, 'data' => $feedback];
        break;

    case 'animal_images':
        $n = $_POST['n'] ?? 0;
        $response = ['success' => true, 'data' => getAnimalImages($n)];
        break;

    case 'db_query':
        $response = fetchDatabaseData();
        break;

    case 'subject_marks':
        $marks = json_decode($_POST['subject_marks'] ?? '{}', true);
        $response = ['success' => true, 'data' => processSubjectMarks($marks)];
        break;
}

echo json_encode($response);
