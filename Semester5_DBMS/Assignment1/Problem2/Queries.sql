-- Q1: Count students in CSE dept
SELECT
  COUNT(*)
FROM
  students
WHERE
  TRIM(deptcode) = 'CSE';

-- Q2: Min, max and average marks of each course
SELECT
  crs_cd,
  MIN(marks) AS min_marks,
  MAX(marks) AS max_marks,
  AVG(marks) AS avg_marks
FROM
  crs_regd
GROUP BY
  crs_cd;

-- Q3: Total credits of courses registered by a student
SELECT
  r.crs_rollno,
  s.name,
  SUM(o.crs_credits) AS total_credits
FROM
  crs_regd r
  JOIN crs_offrd o ON r.crs_cd = o.crs_code
  JOIN students s on r.crs_rollno = s.rollno
GROUP BY
  r.crs_rollno,
  s.name;

-- Q4: Number of students in each hostel whose department is CSE
SELECT
  hostel,
  COUNT(*) AS num_students
FROM
  students
WHERE
  TRIM(deptcode) = 'CSE'
GROUP BY
  hostel;

-- Q5: Hostel, rollno, parent_inc of student with max(parent_inc) in each hostel
SELECT
  hostel,
  rollno,
  parent_inc
FROM
  (
    SELECT
      hostel,
      rollno,
      parent_inc,
      RANK() OVER (
        PARTITION BY
          hostel
        ORDER BY
          parent_inc DESC
      ) as rank
    FROM
      students
    WHERE
      hostel IS NOT NULL
  ) ranked_students
WHERE
  rank = 1;

-- Q6: Name and parent_inc of students with income > rollno 92005010
SELECT
  name,
  parent_inc
FROM
  students
WHERE
  parent_inc > (
    SELECT
      parent_inc
    FROM
      students
    WHERE
      rollno = 92005010
  );

-- Q7: Marks of students who scored more than rollno 92005102 in CH103 and PH106
SELECT
  r.crs_rollno,
  r.crs_cd,
  r.marks
FROM
  crs_regd r
WHERE
  TRIM(r.crs_cd) IN ('CH103', 'PH106')
  AND r.marks > (
    SELECT
      r2.marks
    FROM
      crs_regd r2
    WHERE
      r2.crs_rollno = 92005102
      AND r2.crs_cd = r.crs_cd
  );
