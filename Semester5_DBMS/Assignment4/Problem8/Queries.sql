CREATE TABLE IF NOT EXISTS Customer (
  cust_id INTEGER PRIMARY KEY CHECK (
    cust_id >= 100
    AND cust_id <= 1000
  ),
  cust_name VARCHAR(30),
  annual_revenue NUMERIC(10, 2),
  cust_type VARCHAR(30) CHECK (
    cust_type in ('MANUFACTURER', 'WHOLESALER', 'RETAILER')
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
