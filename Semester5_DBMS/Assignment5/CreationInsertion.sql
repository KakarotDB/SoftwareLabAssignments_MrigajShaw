CREATE TABLE circles (
  radius NUMERIC(10, 2),
  circumference NUMERIC(10, 2)
);

CREATE TABLE cust_acct (
  cust_id INT PRIMARY KEY,
  cust_name VARCHAR(50) NOT NULL,
  balance NUMERIC(12, 2)
);

CREATE TABLE employees (
  emp_id INT PRIMARY KEY,
  emp_name VARCHAR(50) NOT NULL,
  dept VARCHAR(30),
  salary NUMERIC(10, 2)
);

CREATE TABLE item_mstr (
  item_id INT PRIMARY KEY,
  item_name VARCHAR(50),
  balance INT NOT NULL DEFAULT 0
);

CREATE TABLE item_tr (
  tr_id SERIAL PRIMARY KEY,
  item_id INT NOT NULL,
  quantity INT NOT NULL,
  tr_date DATE DEFAULT CURRENT_DATE
);

INSERT INTO
  cust_acct
VALUES
  (1, 'Asha', 5000),
  (2, 'Ravi', 800),
  (3, 'Mita', 1000),
  (4, 'Dev', 2500);

INSERT INTO
  employees
VALUES
  (101, 'Anil', 'IT', 40000),
  (102, 'Bela', 'HR', 30000),
  (103, 'Chirag', 'IT', NULL),
  (104, 'Disha', 'Ops', 25000);

INSERT INTO
  item_mstr
VALUES
  (1, 'Pen', 100),
  (2, 'Book', 50);
