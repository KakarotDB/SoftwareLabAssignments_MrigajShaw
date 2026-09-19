-- Q1: Display the difference between highest and lowest salary of each department in descending order. Label the column as “Difference”.
SELECT
  dname,
  MAX(sal) - MIN(sal) AS Difference
FROM
  dept
  JOIN emp on emp.deptno = dept.deptno
GROUP BY
  dname
ORDER BY
  MAX(sal) - MIN(sal) DESC;

-- Q2: List all the employees’ employee number and name along with their immediate managers’ employee number and name.
SELECT
  e1.empno,
  e1.ename,
  e2.empno as manager_id,
  e2.ename as manager_name
FROM
  emp e1
  LEFT JOIN emp e2 on e1.mgr = e2.empno;

-- Q3: Create a query that will display the total number of employees and the total number of employees who were hired only in 2020. Give the column headings as “TOTAL” and “TOTAL_2020” respectively.
SELECT
  COUNT(*) as TOTAL,
  COUNT(*) FILTER (
    WHERE
      (
        EXTRACT(
          YEAR
          FROM
            hiredate
        ) = 2020
      )
  ) AS TOTAL_2020
FROM
  emp;

-- Q4: Display the manager number and the salary of the lowest paid employee under that manager. Exclude anyone whose manager is not known. Exclude any group where the minimum salaryis less than 1000. Sort the output in descending order of salary.
SELECT
  mgr as manager_id,
  MIN(sal) as min_sal
FROM
  emp
WHERE
  mgr IS NOT NULL
GROUP BY
  mgr
HAVING
  MIN(sal) >= 1000
ORDER BY
  min_sal DESC;

-- Q5: Assume that there are some departments where no employee is assigned. Now, write
-- a query to display the department name, location name, number of employees, and the
-- average salary for all the employees in that department. Label the columns as
-- “DNAME”, “LOCATION”, “NUMBER OF PEOPLE”, and “AVERAGE SALARY”
-- respectively. Round the averge salary to two decimal places. The outcome of the
-- query must include the details of the departments where no employee is assigned and
-- in that case the “AVERAGE SALARY” for that department is to be displayed as 0
-- (zero).
SELECT
  dname,
  loc AS LOCATION,
  COUNT(empno) as "NUMBER OF PEOPLE",
  ROUND(COALESCE(AVG(sal), 0), 2) as "AVERAGE SALARY"
FROM
  dept d
  LEFT JOIN emp e ON d.deptno = e.deptno
GROUP BY
  dname,
  loc
ORDER BY
  "AVERAGE SALARY" DESC;
