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
$item_name = $_POST['item_name'] ?? '';
$category = $_POST['category'] ?? '';
$amount = $_POST['amount'] ?? '';
$expense_date = $_POST['expense_date'] ?? '';

if ($id === '' || $item_name === '' || $amount === '') {
    echo json_encode(["success" => false, "message" => "Missing required fields"]);
    exit;
}

$result = pg_query_params(
    $conn,
    'UPDATE "2024CSB041" SET item_name = $1, category = $2, amount = $3, expense_date = $4 WHERE expense_id = $5',
    [$item_name, $category, $amount, $expense_date, $id]
);

echo $result
    ? json_encode(["success" => true, "message" => "Record updated"])
    : json_encode(["success" => false, "message" => "Update failed: " . pg_last_error($conn)]);

pg_close($conn);
?>
