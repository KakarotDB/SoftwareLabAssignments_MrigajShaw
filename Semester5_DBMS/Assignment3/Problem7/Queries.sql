CREATE VIEW cse_stud AS
SELECT
  rollno,
  name,
  hostel
FROM
  students
WHERE
  TRIM(deptcode) = 'CSE';

UPDATE students
SET
  parent_inc = parent_inc + 5000
DROP VIEW cse_stud;

CREATE VIEW mech_engineers AS
SELECT
  rollno,
  name,
  hostel
FROM
  students
WHERE
  TRIM(deptcode) = 'MEC';

INSERT INTO
  students (rollno, name, deptcode, bdate, hostel, parent_inc)
VALUES
  (
    '92005504',
    'Tamanna Jana',
    'MEC',
    '1996-01-12',
    5,
    100000
  );

-- updating the view directly leads to check constraints being violated -> thus we insert directly into the new table to see if the view updates 
DELETE FROM mech_engineers
WHERE
  name = 'Tamanna Jana';

-- Even though we deleted only from the view, it deletes from the main table as well - Showing views are purely virtual tables 
UPDATE students
SET
  deptcode = 'MEC'
where
  name = 'Riddhi Agarwal';

-- shifts student back to being in CSE
UPDATE students
SET
  deptcode = 'CSE'
where
  name = 'Riddhi Agarwal';

-- this also updates the view for mechanical engineers -> the shift result shows in the views as well
