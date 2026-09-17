<?php

function sayHello() {
    return "Hello PHP";
}

function calculateGrade($marks) {
    if (!is_numeric($marks) || $marks < 0 || $marks > 100) {
        return "Invalid marks! Enter a value between 0 and 100.";
    }
    if ($marks >= 90) return "Grade A+";
    if ($marks >= 80) return "Grade A";
    if ($marks >= 70) return "Grade B";
    if ($marks >= 60) return "Grade C";
    if ($marks >= 50) return "Grade D";
    return "Grade F";
}

function getOddNumbers($n) {
    $n = (int)$n;
    if ($n < 1) return [];
    
    $odds = [];
    for ($i = 1; $i <= $n; $i++) {
        if ($i % 2 !== 0) {
            $odds[] = $i;
        }
    }
    return $odds;
}

function sortNumbers($numberArray) {
    sort($numberArray, SORT_NUMERIC);
    return $numberArray;
}

function getAnimalNames($n) {
    $animals = ["Lion", "Tiger", "Elephant", "Giraffe", "Zebra", "Cheetah", "Kangaroo", "Panda", "Bear", "Wolf"];
    $n = min((int)$n, count($animals));
    return array_slice($animals, 0, $n);
}

function processFormFeedback($postData, $filesData) {
    $uploadedFileName = "No file uploaded";
    
    if (isset($filesData['user_file']) && $filesData['user_file']['error'] === UPLOAD_ERR_OK) {
        $uploadedFileName = basename($filesData['user_file']['name']) . " (Uploaded successfully)";
    }

    return [
        'username' => htmlspecialchars($postData['username'] ?? ''),
        'password' => '•••••••• (' . strlen($postData['password'] ?? '') . ' chars)',
        'gender'   => htmlspecialchars($postData['gender'] ?? 'Not selected'),
        'country'  => htmlspecialchars($postData['country'] ?? 'Not selected'),
        'file'     => $uploadedFileName,
        'token'    => htmlspecialchars($postData['hidden_token'] ?? '')
    ];
}

function getAnimalImages($n) {
    $animalGallery = [
        ["name" => "Lion",     "url" => "https://images.unsplash.com/photo-1614027164847-1b28cfe1df60?w=300"],
        ["name" => "Tiger",    "url" => "https://images.unsplash.com/photo-1534188753412-3e26d0d618d6?w=300"],
        ["name" => "Elephant", "url" => "https://images.unsplash.com/photo-1557050543-4d5f4e07ef46?w=300"],
        ["name" => "Giraffe",  "url" => "https://images.unsplash.com/photo-1547721064-da6cfb341d50?w=300"],
        ["name" => "Zebra",    "url" => "https://images.unsplash.com/photo-1501705388883-4ed8a543392c?w=300"],
        ["name" => "Panda",    "url" => "https://images.unsplash.com/photo-1564349683136-77e08dba1ef9?w=300"]
    ];
    
    $n = min((int)$n, count($animalGallery));
    return array_slice($animalGallery, 0, $n);
}

function fetchDatabaseData() {
    $host = 'localhost';
    $db   = 'webtech_db';
    $user = 'root';
    $pass = '';
    
    try {
        $pdo = new PDO("mysql:host=$host;dbname=$db;charset=utf8", $user, $pass);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $stmt = $pdo->query("SELECT * FROM students");
        return ["status" => "success", "data" => $stmt->fetchAll(PDO::FETCH_ASSOC)];
    } catch (PDOException $e) {
        return ["status" => "error", "message" => "Database connection status: " . $e->getMessage()];
    }
}

function processSubjectMarks($subjectsMarks) {
    $total = array_sum($subjectsMarks);
    $count = count($subjectsMarks);
    $average = $count > 0 ? $total / $count : 0;
    $overallGrade = calculateGrade($average);

    return [
        'subject_marks' => $subjectsMarks,
        'total'         => $total,
        'average'       => round($average, 2),
        'overall_grade' => $overallGrade
    ];
}
