-- Q1 : Retrieve the name of students whose start with 'S' and contains 'r' as the second last character 
SELECT
  name
FROM
  students
WHERE
  name LIKE 'S%r_';

-- Q2 : Retrieve the name of the youngest student(s) from the ‘CST’ department along with the total marks obtained by him (them).
SELECT
  s.name,
  cr.marks
FROM
  crs_regd cr
  JOIN students s ON s.rollno = cr.crs_rollno;

-- Q3: Find age of all students  
SELECT
  name,
  rollno,
  AGE (CURRENT_DATE, bdate) as age
FROM
  students;
