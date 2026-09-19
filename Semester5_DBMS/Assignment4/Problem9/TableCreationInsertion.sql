DROP TABLE IF EXISTS EMP CASCADE;

DROP TABLE IF EXISTS DEPT CASCADE;

CREATE TABLE IF NOT EXISTS dept (
  deptno VARCHAR(10) PRIMARY KEY CHECK (DEPTNO LIKE 'D%'),
  dname VARCHAR(20) CHECK (
    dname IN ('Accounting', 'Sales', 'Research', 'Operations')
  ),
  loc VARCHAR(30)
);

CREATE TABLE IF NOT EXISTS emp (
  empno INTEGER PRIMARY KEY CHECK (
    empno >= 7000
    AND empno <= 8000
  ),
  ename VARCHAR(10),
  job VARCHAR(15) CHECK (
    job in (
      'Clerk',
      'Salesman',
      'Manager',
      'Analyst',
      'President'
    )
  ),
  mgr INTEGER REFERENCES EMP (empno) ON DELETE SET NULL,
  hiredate DATE,
  sal NUMERIC(10, 2),
  comm NUMERIC(10, 2) DEFAULT 0 CHECK (comm < 1500),
  deptno VARCHAR(10) REFERENCES DEPT (DEPTNO)
);

INSERT INTO
  DEPT (DEPTNO, DNAME, LOC)
VALUES
  ('D10', 'Accounting', 'NEW YORK'),
  ('D20', 'Research', 'DALLAS'),
  ('D30', 'Sales', 'CHICAGO'),
  ('D40', 'Operations', 'BOSTON');

INSERT INTO
  EMP (
    EMPNO,
    ENAME,
    JOB,
    MGR,
    HIREDATE,
    SAL,
    COMM,
    DEPTNO
  )
VALUES
  -- 1. President (Top Level Manager - MGR is NULL)
  (
    7839,
    'Andrew',
    'President',
    NULL,
    '2019-11-17',
    5000.00,
    0,
    'D10'
  ),
  -- 2. Managers (Reporting to andrew)
  (
    7566,
    'JONES',
    'Manager',
    7839,
    '2020-04-02',
    2975.00,
    0,
    'D20'
  ),
  (
    7698,
    'BLAKE',
    'Manager',
    7839,
    '2019-05-01',
    2850.00,
    0,
    'D30'
  ),
  (
    7782,
    'CLARK',
    'Manager',
    7839,
    '2020-06-09',
    2450.00,
    0,
    'D10'
  ),
  -- 3. Analysts & Salesmen (Reporting to Managers)
  (
    7788,
    'SCOTT',
    'Analyst',
    7566,
    '2020-12-09',
    3000.00,
    0,
    'D20'
  ),
  (
    7902,
    'FORD',
    'Analyst',
    7566,
    '2020-12-03',
    3000.00,
    0,
    'D20'
  ),
  (
    7499,
    'ALLEN',
    'Salesman',
    7698,
    '2020-02-20',
    1600.00,
    300,
    'D30'
  ),
  (
    7521,
    'WARD',
    'Salesman',
    7698,
    '2021-02-22',
    1250.00,
    500,
    'D30'
  ),
  (
    7654,
    'MARTIN',
    'Salesman',
    7698,
    '2020-09-28',
    1250.00,
    1400,
    'D30'
  ),
  -- 4. Clerks (Reporting to various Managers/Analysts)
  (
    7369,
    'SMITH',
    'Clerk',
    7902,
    '2020-12-17',
    800.00,
    0,
    'D20'
  ),
  (
    7876,
    'ADAMS',
    'Clerk',
    7788,
    '2021-05-23',
    1100.00,
    0,
    'D20'
  ),
  (
    7900,
    'JAMES',
    'Clerk',
    7698,
    '2020-12-03',
    950.00,
    0,
    'D30'
  ),
  (
    7934,
    'MILLER',
    'Clerk',
    7782,
    '2022-01-23',
    1300.00,
    0,
    'D10'
  );
