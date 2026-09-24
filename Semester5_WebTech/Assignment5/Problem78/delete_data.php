<?php
header('Content-Type: application/json');

function loadEnv($path) {
    foreach (file($path) as $line) {
        $line = trim($line);
        if ($line === '' || $line[0] === '#') continue;
        [$key, $value] = explode('=', $line, 2);
        $_ENV[trim($key)] = trim($value);
    }
}
loadEnv(__DIR__ . '/.env');

$conn = pg_connect("host={$_ENV['DB_HOST']} port={$_ENV['DB_PORT']} dbname={$_ENV['DB_NAME']} user={$_ENV['DB_USER']} password={$_ENV['DB_PASSWORD']}");

if (!$conn) {
    echo json_encode(["success" => false, "message" => "Connection failed"]);
    exit;
}

$id = $_POST['expense_id'] ?? '';

if ($id === '') {
    echo json_encode(["success" => false, "message" => "Missing expense_id"]);
    exit;
}

$result = pg_query_params($conn, 'DELETE FROM "2024CSB041" WHERE expense_id = $1', [$id]);

echo $result
    ? json_encode(["success" => true, "message" => "Record deleted"])
    : json_encode(["success" => false, "message" => "Delete failed: " . pg_last_error($conn)]);

pg_close($conn);
?>
