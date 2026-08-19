-- Q1 : Retrieve the name of students whose start with 'S' and contains 'r' as the second last character 
SELECT
  name
FROM
  students
WHERE
  name LIKE 'S%r_';

-- Q2 : Retrieve the name of the youngest student(s) from the ‘CST’ department along with the total marks obtained by him (them).
SELECT
  name,
  SUM(marks) total_marks,
  AGE (CURRENT_DATE, bdate) as student_age
FROM
  students
  JOIN crs_regd on crs_regd.crs_rollno = students.rollno
WHERE
  AGE (CURRENT_DATE, bdate) = (
    SELECT
      MIN(AGE (CURRENT_DATE, bdate))
    FROM
      students
  )
GROUP BY
  students.name,
  student_age;

-- Q3: Find age of all students  
SELECT
  name,
  rollno,
  AGE (CURRENT_DATE, bdate) as age
FROM
  students;
