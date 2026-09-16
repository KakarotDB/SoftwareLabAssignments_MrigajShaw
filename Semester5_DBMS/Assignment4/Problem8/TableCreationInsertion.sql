-- DDL and insertion of data
CREATE TABLE IF NOT EXISTS Customer (
  cust_id INTEGER PRIMARY KEY CHECK (
    cust_id >= 100
    AND cust_id <= 10000
  ),
  cust_name VARCHAR(30),
  annual_revenue NUMERIC(10, 2),
  cust_type VARCHAR(30) CHECK (
    cust_type IN ('MANUFACTURER', 'WHOLESALER', 'RETAILER')
  )
);

CREATE TABLE IF NOT EXISTS Truck (
  truck_no INTEGER PRIMARY KEY,
  driver_name VARCHAR(30)
);

CREATE TABLE IF NOT EXISTS City (
  city_name VARCHAR(30) PRIMARY KEY,
  population INTEGER
);

CREATE TABLE IF NOT EXISTS Shipment (
  shipment_no INTEGER PRIMARY KEY,
  cust_id INTEGER REFERENCES Customer (cust_id) ON DELETE CASCADE,
  weight INTEGER CHECK (weight < 1000),
  truck_no INTEGER REFERENCES Truck (truck_no) ON DELETE SET NULL,
  destination VARCHAR(30) REFERENCES City (city_name)
);

INSERT INTO
  City (city_name, population)
VALUES
  ('Mumbai', 12000000),
  ('Kolkata', 4500000),
  ('Chennai', 7000000),
  ('Pune', 800000),
  ('Delhi', 11000000),
  ('Bangalore', 8000000),
  ('Hyderabad', 6900000),
  ('Jaipur', 3000000),
  ('Surat', 4400000),
  ('Kochi', 600000);

INSERT INTO
  Truck (truck_no, driver_name)
VALUES
  (1, 'IQBAL'),
  (2, 'SAM'),
  (3, 'RAJ'),
  (4, 'AMIT'),
  (5, 'JOHN'),
  (6, 'VIKAS'),
  (7, 'ROHIT'),
  (8, 'ALI'),
  (9, 'MANISH'),
  (10, 'DEV');

INSERT INTO
  Customer (cust_id, cust_name, annual_revenue, cust_type)
VALUES
  (101, 'Acme Corp', 500000.00, 'MANUFACTURER'),
  (102, 'Beta Goods', 300000.00, 'WHOLESALER'),
  (103, 'Charlie Retail', 150000.00, 'RETAILER'),
  (104, 'Delta Dynamics', 750000.00, 'MANUFACTURER'),
  (105, 'Echo Supplies', 200000.00, 'WHOLESALER'),
  (106, 'Foxtrot Mart', 100000.00, 'RETAILER'),
  (107, 'Gamma Traders', 450000.00, 'WHOLESALER'),
  (108, 'Halo Tech', 900000.00, 'MANUFACTURER'),
  (109, 'Indus Retail', 350000.00, 'RETAILER'),
  (110, 'Jupiter Mills', 600000.00, 'MANUFACTURER');

INSERT INTO
  Shipment (
    shipment_no,
    cust_id,
    weight,
    truck_no,
    destination
  )
VALUES
  (1001, 101, 150, 2, 'Mumbai'),
  (1002, 101, 150, 2, 'Kolkata'),
  (1003, 101, 150, 2, 'Chennai'),
  (1004, 101, 150, 2, 'Pune'),
  (1005, 102, 150, 2, 'Delhi'),
  (1006, 102, 150, 2, 'Bangalore'),
  (1007, 103, 150, 2, 'Hyderabad'),
  (1008, 103, 150, 2, 'Jaipur'),
  (1009, 104, 150, 2, 'Surat'),
  (1010, 104, 150, 2, 'Kochi'),
  (1011, 102, 300, 1, 'Pune'),
  (1012, 103, 50, 3, 'Pune'),
  (1013, 104, 60, 4, 'Pune'),
  (1014, 105, 70, 5, 'Pune'),
  (1015, 106, 80, 6, 'Pune'),
  (1016, 107, 90, 7, 'Pune'),
  (1017, 108, 95, 8, 'Pune'),
  (1018, 109, 210, 9, 'Pune'),
  (1019, 110, 500, 10, 'Pune'),
  (1020, 105, 100, 1, 'Mumbai'),
  (1021, 105, 250, 3, 'Chennai'),
  (1022, 105, 300, 4, 'Kolkata'),
  (1023, 107, 999, 1, 'Delhi'),
  (1024, 108, 10, 3, 'Mumbai'),
  (1025, 110, 750, 1, 'Kochi');
