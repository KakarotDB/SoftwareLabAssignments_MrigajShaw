-- Q1 : Retrieve the name of the student(s) who obtained second highest marks in ‘DBMS’.
SELECT
  s1.name
FROM
  crs_regd cr1
  JOIN students s1 ON s1.rollno = cr1.crs_rollno
  JOIN crs_offrd co ON co.crs_code = cr1.crs_cd
WHERE
  TRIM(co.crs_name) = 'DBMS'
  AND 1 = (
    SELECT
      COUNT(DISTINCT cr2.marks)
    FROM
      crs_regd cr2
      JOIN crs_offrd co2 ON co2.crs_code = cr2.crs_cd
    WHERE
      TRIM(co2.crs_name) = 'DBMS'
      AND cr2.marks > cr1.marks
  );

-- Q2: Find out the differences between the highest and lowest marks obtained in each subject 
SELECT
  co.crs_name,
  MAX(marks) - MIN(marks) as marks_Difference
FROM
  crs_offrd co
  JOIN crs_regd cr ON cr.crs_cd = co.crs_code
GROUP BY
  crs_name;

-- Q3 : Assuming the existance of several interdepartmental courses, retrieve the name of the student(s) who is(are) studing under at least one faculty from each department.
SELECT
  name,
  rollno
FROM
  students
  JOIN crs_regd ON crs_regd.crs_rollno = students.rollno
  JOIN crs_offrd ON crs_regd.crs_cd = crs_offrd.crs_code
  JOIN faculty on faculty.fac_code = crs_offrd.crs_fac_cd
GROUP BY
  name,
  rollno
HAVING
  COUNT(DISTINCT TRIM(faculty.fac_dept)) = (
    SELECT
      COUNT(DISTINCT TRIM(deptcode))
    FROM
      depts
  );

-- Q4: Assuming the existance of several interdepartmental courses, retrieve the name of the student(s) who is(are) studing under the faculties only from his(their) own department.
SELECT
  name,
  rollno
FROM
  students
  JOIN crs_regd ON crs_regd.crs_rollno = students.rollno
  JOIN crs_offrd ON crs_regd.crs_cd = crs_offrd.crs_code
  JOIN faculty on TRIM(faculty.fac_code) = TRIM(crs_offrd.crs_fac_cd)
GROUP BY
  name,
  rollno,
  deptcode
HAVING
  COUNT(DISTINCT TRIM(faculty.fac_dept)) = 1
  AND MAX(TRIM(faculty.fac_dept)) = TRIM(students.deptcode)
  AND COUNT(DISTINCT TRIM(faculty.fac_code)) = (
    SELECT
      COUNT(DISTINCT TRIM(faculty.fac_code))
    FROM
      faculty
    WHERE
      TRIM(fac_dept) = TRIM(deptcode)
  );
