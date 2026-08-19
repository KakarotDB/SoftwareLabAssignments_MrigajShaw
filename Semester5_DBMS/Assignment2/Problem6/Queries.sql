-- Q1: Display the highest parent incomes, in descending order, for each department excluding ‘ARCH’ such that only those highest parent incomes will appear that are below 12,000.
SELECT
  s1.rollno,
  s1.name,
  s1.deptcode,
  s1.parent_inc
FROM
  students s1
WHERE
  deptcode != 'ARC'
  AND parent_inc < 12000
  AND s1.parent_inc = (
    SELECT
      MAX(s2.parent_inc)
    FROM
      students s2
    WHERE
      s1.deptcode = s2.deptcode
      AND s2.deptcode != 'ARC'
      AND s2.parent_inc < 12000
  )
ORDER BY
  s1.parent_inc DESC;

-- Q2: Retrieve the 5th largest parental income for hostel no. 5 
SELECT
  s1.rollno,
  s1.name,
  s1.parent_inc
FROM
  students s1
WHERE
  4 = (
    SELECT
      COUNT(DISTINCT s2.parent_inc)
    FROM
      students s2
    WHERE
      s2.parent_inc > s1.parent_inc
  );

-- Q3: Find the roll number of the students from each department who obtained highest total marks in their own department.
SELECT
  s1.name,
  s1.rollno,
  s1.deptcode,
  SUM(cr1.marks) as total_marks
FROM
  students s1
  JOIN crs_regd cr1 ON cr1.crs_rollno = s1.rollno
GROUP BY
  s1.name,
  s1.rollno,
  s1.deptcode
HAVING
  SUM(cr1.marks) = (
    SELECT
      (MAX(dept_totals.total))
    FROM
      (
        SELECT
          s2.deptcode,
          SUM(cr2.marks) as total
        FROM
          students s2
          JOIN crs_regd cr2 ON cr2.crs_rollno = s2.rollno
        GROUP BY
          s2.rollno,
          s2.deptcode
      ) as dept_totals
    WHERE
      dept_totals.deptcode = s1.deptcode
  )
ORDER BY
  total_marks;
