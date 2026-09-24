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

$result = pg_query($conn, 'SELECT * FROM "2024CSB041" ORDER BY expense_id');
$rows = pg_fetch_all($result);
$rows = $rows === false ? [] : $rows;

function calculateStats($rows) {
    $total = 0;
    foreach ($rows as $row) {
        $total += (float) $row['amount'];
    }
    $count = count($rows);
    $average = $count > 0 ? $total / $count : 0;

    foreach ($rows as &$row) {
        $amt = (float) $row['amount'];
        if ($amt > 1000) $row['grade'] = 'A';
        elseif ($amt > 500) $row['grade'] = 'B';
        else $row['grade'] = 'C';
    }

    return [
        "rows" => $rows,
        "total" => round($total, 2),
        "average" => round($average, 2)
    ];
}

echo json_encode(calculateStats($rows));

pg_close($conn);
?>
