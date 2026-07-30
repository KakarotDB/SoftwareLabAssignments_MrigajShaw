-- Q1: Students (rollno, name, deptcode) registered for course EE101
SELECT s.rollno, s.name, s.deptcode
FROM students s
JOIN crs_regd cr ON s.rollno = cr.crs_rollno
WHERE TRIM(cr.crs_cd) = 'EE101';

-- Q2: Students (rollno, name) in ELE dept registered for course EE101
SELECT s.rollno, s.name
FROM students s
JOIN crs_regd cr ON s.rollno = cr.crs_rollno
WHERE TRIM(s.deptcode) = 'ELE' AND TRIM(cr.crs_cd) = 'EE101';

-- Q3: Students (rollno, name) in ELE dept NOT registered for course EE101
SELECT rollno, name
FROM students
WHERE TRIM(deptcode) = 'ELE'
AND rollno NOT IN (
    SELECT crs_rollno
    FROM crs_regd
    WHERE TRIM(crs_cd) = 'EE101'
);

-- Q4: Students registered for BOTH 'DBMS' and 'OS'
SELECT s.name
FROM students s
JOIN crs_regd cr1 ON s.rollno = cr1.crs_rollno
JOIN crs_offrd co1 ON cr1.crs_cd = co1.crs_code
JOIN crs_regd cr2 ON s.rollno = cr2.crs_rollno
JOIN crs_offrd co2 ON cr2.crs_cd = co2.crs_code
WHERE TRIM(co1.crs_name) = 'DBMS' AND TRIM(co2.crs_name) = 'OS';

-- Q5: Faculty who offered either 'MIS' or 'Software Engg.'
SELECT f.fac_name
FROM faculty f
JOIN crs_offrd co ON f.fac_code = co.crs_fac_cd
WHERE TRIM(co.crs_name) = 'MIS' OR TRIM(co.crs_name) = 'Software Engg.';

-- Q6: Faculty who offered 'MIS' but NOT 'Software Engg.'
SELECT f.fac_name
FROM faculty f
JOIN crs_offrd co ON f.fac_code = co.crs_fac_cd
WHERE TRIM(co.crs_name) = 'MIS'
AND f.fac_code NOT IN (
    SELECT crs_fac_cd
    FROM crs_offrd
    WHERE TRIM(crs_name) = 'Software Engg.'
);

-- Q7: Students in each hostel not registered for any course
SELECT s.hostel, s.rollno, s.name
FROM students s
WHERE s.rollno NOT IN (
    SELECT crs_rollno
    FROM crs_regd
);

-- Q8: Students in ELE dept OR registered for course CS101
SELECT rollno, name
FROM students
WHERE TRIM(deptcode) = 'ELE'
UNION
SELECT s.rollno, s.name
FROM students s
JOIN crs_regd cr ON s.rollno = cr.crs_rollno
WHERE TRIM(cr.crs_cd) = 'CS101';

-- Q9: Students registered for ALL courses
SELECT s.rollno, s.name
FROM students s
WHERE NOT EXISTS (
    SELECT co.crs_code
    FROM crs_offrd co
    WHERE NOT EXISTS (
        SELECT 1
        FROM crs_regd cr
        WHERE cr.crs_rollno = s.rollno AND cr.crs_cd = co.crs_code
    )
);

-- Q10: Grace Marks +5 in 'DBMS' for students who scored < 50
UPDATE crs_regd
SET marks = marks + 5
WHERE marks < 50
AND crs_cd IN (
    SELECT crs_code
    FROM crs_offrd
    WHERE TRIM(crs_name) = 'DBMS'
);
