INSERT INTO
  depts (deptcode, deptname)
VALUES
  ('CSE', 'Computer Science & Engineering'),
  ('ELE', 'Electronics Engineering'),
  ('CST', 'Computer Science & Technology'),
  ('EE ', 'Electrical Engineering'),
  ('ETC', 'Electronics & Telecomm'),
  ('CE ', 'Civil Engineering'),
  ('IT ', 'Information Technology'),
  ('AEM', 'Aerospace & Applied Mechanics'),
  ('MME', 'Materials and Metallurgy');

INSERT INTO
  faculty (fac_code, fac_name, fac_dept)
VALUES
  ('dbp     ', 'Dr. D.B. Phatak', 'CSE'),
  ('nls     ', 'Dr. N.L. Sarda', 'CSE'),
  ('skg     ', 'Dr. S.K. Gupta', 'ELE'),
  ('avm     ', 'Dr. A.V. Mohanty', 'ETC'),
  ('rkj     ', 'Dr. R.K. Joshi', 'CST'),
  ('pks     ', 'Dr. P.K. Sharma', 'EE '),
  ('mns     ', 'Dr. M.N. Singh', 'IT '),
  ('vkr     ', 'Dr. V.K. Rao', 'CE ');

INSERT INTO
  crs_offrd (crs_code, crs_name, crs_credits, crs_fac_cd)
VALUES
  ('CS101', 'DBMS', 4.0, 'dbp     '),
  ('CS102', 'OS', 5.0, 'dbp     '),
  ('CS103', 'Software Engg.', 6.0, 'dbp     '),
  ('CS104', 'MIS', 4.5, 'nls     '),
  ('EE101', 'Circuit Theory', 5.5, 'skg     '),
  ('EE102', 'Signal Processing', 7.0, 'skg     '),
  ('CH103', 'Chemistry', 3.0, 'avm     '),
  ('PH106', 'Physics', 8.0, 'pks     '),
  ('ME101', 'Thermodynamics', 7.5, 'vkr     '),
  ('IT101', 'Data Structures', 4.0, 'mns     '),
  ('CS105', 'Advanced Algorithms', 4.0, 'rkj     ');

INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    92005001,
    'Riddhi Agarwal',
    '1995-03-15',
    'CSE',
    1,
    500000.0
  ),
  (
    92005002,
    'Priya Verma',
    '1996-07-22',
    'CSE',
    2,
    750000.0
  ),
  (
    92005003,
    'Rahul Das',
    '1995-11-10',
    'CSE',
    1,
    300000.0
  ),
  (
    92005004,
    'Sneha Gupta',
    '1996-01-05',
    'CSE',
    3,
    600000.0
  ),
  (
    92005010,
    'Ravi Kumar',
    '1995-06-18',
    'ELE',
    2,
    450000.0
  ),
  (
    92005011,
    'Neha Patil',
    '1996-09-30',
    'ELE',
    4,
    900000.0
  ),
  (
    92005012,
    'Vikram Singh',
    '1995-12-25',
    'ELE',
    5,
    350000.0
  ),
  (
    92005013,
    'Ananya Roy',
    '1996-04-14',
    'ELE',
    4,
    550000.0
  ),
  (
    92005100,
    'Suresh Nair',
    '1995-08-08',
    'CST',
    6,
    800000.0
  ),
  (
    92005101,
    'Kavita Jain',
    '1996-02-28',
    'CST',
    7,
    650000.0
  ),
  (
    92005102,
    'Deepak Mehta',
    '1995-05-20',
    'ETC',
    3,
    400000.0
  ),
  (
    92005103,
    'Pooja Reddy',
    '1996-10-12',
    'EE ',
    8,
    700000.0
  ),
  (
    92005104,
    'Arun Bhat',
    '1995-01-30',
    'IT ',
    6,
    250000.0
  ),
  (
    92005105,
    'Meera Iyer',
    '1996-06-05',
    'CE ',
    9,
    550000.0
  ),
  (
    92005106,
    'Kiran Desai',
    '1995-09-17',
    'MME',
    7,
    480000.0
  );

INSERT INTO
  crs_regd (crs_rollno, crs_cd, marks)
VALUES
  (92005001, 'CS105', 88.00),
  (92005001, 'CS101', 85.50),
  (92005001, 'CS102', 72.00),
  (92005001, 'CS103', 68.00),
  (92005001, 'CS104', 91.00),
  (92005001, 'EE101', 77.00),
  (92005001, 'EE102', 60.00),
  (92005001, 'CH103', 88.00),
  (92005001, 'PH106', 74.50),
  (92005001, 'ME101', 65.00),
  (92005001, 'IT101', 82.00),
  (92005002, 'CS101', 45.00),
  (92005002, 'CS102', 78.00),
  (92005003, 'CS101', 38.00),
  (92005004, 'CS101', 92.00),
  (92005004, 'CS102', 88.00),
  (92005010, 'EE101', 70.00),
  (92005010, 'CS101', 55.00),
  (92005011, 'EE101', 82.00),
  (92005011, 'CS101', 42.00),
  (92005012, 'CS101', 48.00),
  (92005012, 'CH103', 65.00),
  (92005100, 'CH103', 75.00),
  (92005100, 'PH106', 80.00),
  (92005100, 'CS101', 67.00),
  (92005100, 'CS102', 73.00),
  (92005101, 'CS101', 30.00),
  (92005102, 'CH103', 60.00),
  (92005102, 'PH106', 55.00),
  (92005102, 'EE101', 72.00),
  (92005103, 'EE102', 85.00),
  (92005103, 'PH106', 90.00),
  (92005104, 'IT101', 76.00),
  (92005104, 'CS101', 58.00),
  (92005106, 'ME101', 71.00);

INSERT INTO
  faculty (fac_code, fac_name, fac_dept)
VALUES
  ('aem1', 'Dr. A.E. Mech', 'AEM'),
  ('mme1', 'Dr. M.M. Engg', 'MME');

INSERT INTO
  crs_offrd (crs_code, crs_name, crs_credits, crs_fac_cd)
VALUES
  ('AE101', 'Aerodynamics', 4.0, 'aem1'),
  ('MM101', 'Metallurgy', 4.0, 'mme1');

INSERT INTO
  crs_regd (crs_rollno, crs_cd, marks)
VALUES
  (92005001, 'AE101', 80.00),
  (92005001, 'MM101', 85.00);

INSERT INTO
  crs_regd (crs_rollno, crs_cd, marks)
VALUES
  (92005002, 'CS104', 82.00);

-- inserting architecture dept 
INSERT INTO
  depts (deptcode, deptname)
VALUES
  ('ARC', 'Architecture');

-- Inserting new students with parent incomes below 12,000
INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    92005201,
    'Aarav Sharma',
    '1996-05-12',
    'CSE',
    1,
    10000.0
  ),
  (
    92005202,
    'Diya Patel',
    '1995-08-20',
    'CSE',
    2,
    11500.0
  ),
  (
    92005203,
    'Kabir Mehta',
    '1996-03-11',
    'ELE',
    3,
    8500.0
  ),
  (
    92005204,
    'Ishita Sen',
    '1995-12-01',
    'ELE',
    4,
    9500.0
  ),
  (
    92005205,
    'Rohan Bose',
    '1996-01-22',
    'IT ',
    5,
    11800.0
  ),
  (
    92005206,
    'Tanya Roy',
    '1995-10-10',
    'ARC',
    6,
    11000.0
  );

INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    92005301,
    'Arjun Singh',
    '1995-02-14',
    'CSE',
    5,
    800000.0
  ),
  (
    92005302,
    'Priya Das',
    '1996-07-09',
    'IT ',
    5,
    750000.0
  ),
  (
    92005303,
    'Karan Sharma',
    '1995-11-20',
    'ELE',
    5,
    600000.0
  ),
  (
    92005304,
    'Anjali Verma',
    '1996-04-05',
    'CST',
    5,
    500000.0
  ),
  (
    92005305,
    'Rahul Gupta',
    '1995-09-12',
    'MME ',
    5,
    450000.0
  ),
  (
    92005306,
    'Sneha Patel',
    '1996-01-25',
    'CE ',
    5,
    400000.0
  ),
  (
    92005307,
    'Vikash Kumar',
    '1995-06-30',
    'EE ',
    5,
    300000.0
  );

INSERT INTO
  students (rollno, name, bdate, deptcode, hostel, parent_inc)
VALUES
  (
    92005405,
    'Swati Mitra',
    '1996-08-14',
    'CSE',
    1,
    450000.0
  );

INSERT INTO
  crs_regd (crs_rollno, crs_cd, marks)
VALUES
  (92005304, 'CS101', 85.00),
  (92005304, 'CS102', 91.00);
