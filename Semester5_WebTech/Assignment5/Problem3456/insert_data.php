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

$item_name = $_POST['item_name'] ?? '';
$category = $_POST['category'] ?? '';
$payment_mode = $_POST['payment_mode'] ?? '';
$amount = $_POST['amount'] ?? '';
$expense_date = $_POST['expense_date'] ?? date('Y-m-d');

if ($item_name === '' || $category === '' || $amount === '') {
    echo json_encode(["success" => false, "message" => "Missing required fields"]);
    exit;
}

// pg_query_params binds values safely, avoiding SQL injection
$result = pg_query_params(
    $conn,
    'INSERT INTO "2024CSB041" (item_name, category, amount, expense_date, payment_mode) VALUES ($1, $2, $3, $4, $5)',
    [$item_name, $category, $amount, $expense_date, $payment_mode]
);

echo $result
    ? json_encode(["success" => true, "message" => "Record inserted successfully"])
    : json_encode(["success" => false, "message" => "Insert failed: " . pg_last_error($conn)]);

pg_close($conn);
?>
