-- Q1: Constraint violation attempts 
-- PRIMARY KEY violation
INSERT INTO
  depts (deptcode, deptname)
VALUES
  ('CSE', 'Duplicate Dept');

-- CHECK violation: bdate >= '1997-01-01'
INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    99999999,
    'Test Student',
    '1998-05-10',
    'CSE',
    1,
    100000.0
  );

-- CHECK violation: hostel >= 10
INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    99999998,
    'Test Student 2',
    '1995-01-01',
    'CSE',
    15,
    100000.0
  );

-- FOREIGN KEY violation: deptcode
INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    99999997,
    'Test Student 3',
    '1995-01-01',
    'XYZ',
    1,
    100000.0
  );

-- Q2: Delete deptcode='CSE' (cascades to students)
SELECT
  rollno,
  name
FROM
  students
WHERE
  TRIM(deptcode) = 'CSE';

DELETE FROM crs_regd
WHERE
  crs_cd IN (
    SELECT
      crs_code
    FROM
      crs_offrd
    WHERE
      crs_fac_cd IN (
        SELECT
          fac_code
        FROM
          faculty
        WHERE
          TRIM(fac_dept) = 'CSE'
      )
  );

DELETE FROM crs_regd
WHERE
  crs_rollno IN (
    SELECT
      rollno
    FROM
      students
    WHERE
      TRIM(deptcode) = 'CSE'
  );

DELETE FROM crs_offrd
WHERE
  crs_fac_cd IN (
    SELECT
      fac_code
    FROM
      faculty
    WHERE
      TRIM(fac_dept) = 'CSE'
  );

DELETE FROM faculty
WHERE
  TRIM(fac_dept) = 'CSE';

DELETE FROM depts
WHERE
  TRIM(deptcode) = 'CSE';

SELECT
  rollno,
  name
FROM
  students
WHERE
  TRIM(deptcode) = 'CSE';

-- Q3: Courses offered by faculty 'dbp' and 'nls'
SELECT
  crs_code,
  crs_name
FROM
  crs_offrd
WHERE
  TRIM(crs_fac_cd) IN ('dbp', 'nls');

-- Q4: Courses with full details offered by 'dbp'
SELECT
  co.crs_code,
  co.crs_name,
  co.crs_credits,
  f.fac_name,
  f.fac_dept
FROM
  crs_offrd co
  JOIN faculty f ON co.crs_fac_cd = f.fac_code
WHERE
  TRIM(co.crs_fac_cd) = 'dbp';

-- Q5: Courses with credits between 4.0 and 6.0
SELECT
  crs_code,
  crs_name,
  crs_credits
FROM
  crs_offrd
WHERE
  crs_credits BETWEEN 4.0 AND 6.0;

-- Q6: Courses with credits > 6.5
SELECT
  crs_code,
  crs_name,
  crs_credits
FROM
  crs_offrd
WHERE
  crs_credits > 6.5;
