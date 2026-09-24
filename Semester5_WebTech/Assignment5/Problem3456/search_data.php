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
    echo json_encode(["error" => "Connection failed"]);
    exit;
}

$search = $_GET['q'] ?? '';
$pattern = '%' . $search . '%';

// ILIKE = case-insensitive LIKE (Postgres-specific)
$result = pg_query_params(
    $conn,
    'SELECT * FROM "2024CSB041" WHERE item_name ILIKE $1 OR category ILIKE $1 ORDER BY expense_id',
    [$pattern]
);

if (!$result) {
    echo json_encode(["error" => "Query failed: " . pg_last_error($conn)]);
    exit;
}

$rows = pg_fetch_all($result);
echo json_encode($rows === false ? [] : $rows);

pg_close($conn);
?>
