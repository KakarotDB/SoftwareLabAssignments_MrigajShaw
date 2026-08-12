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
