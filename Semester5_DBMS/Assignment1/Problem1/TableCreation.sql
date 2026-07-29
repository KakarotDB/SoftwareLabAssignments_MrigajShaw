DROP TABLE crs_regd;

DROP TABLE crs_offrd;

DROP TABLE faculty;

DROP TABLE students CASCADE;

DROP TABLE depts;

CREATE TABLE depts (
  deptcode CHAR(3) PRIMARY KEY,
  deptname CHAR(30) NOT NULL
);

CREATE TABLE students (
  rollno NUMERIC(8) PRIMARY KEY,
  name CHAR(30),
  bdate DATE CHECK (bdate < '1997-01-01'),
  deptcode CHAR(3) REFERENCES depts (deptcode) ON DELETE CASCADE,
  hostel NUMERIC CHECK (hostel < 10),
  parent_inc NUMERIC(8, 1)
);

CREATE TABLE faculty (
  fac_code CHAR(8) PRIMARY KEY,
  fac_name CHAR(30) NOT NULL,
  fac_dept CHAR(3) REFERENCES depts (deptcode)
);

CREATE TABLE crs_offrd (
  crs_code CHAR(5) PRIMARY KEY,
  crs_name CHAR(35) NOT NULL,
  crs_credits NUMERIC(2, 1),
  crs_fac_cd CHAR(8) REFERENCES faculty (fac_code)
);

CREATE TABLE crs_regd (
  crs_rollno NUMERIC(8) REFERENCES students (rollno),
  crs_cd CHAR(5) REFERENCES crs_offrd (crs_code),
  marks NUMERIC(5, 2),
  PRIMARY KEY (crs_rollno, crs_cd)
);
