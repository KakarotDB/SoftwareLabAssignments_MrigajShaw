-- Q1: Give names of customer who have sent packages (shipments) to Kolkata, Chennai and Mumbai.
SELECT
  cust_name
FROM
  customer
  JOIN shipment ON customer.cust_id = shipment.cust_id
WHERE
  destination in ('Kolkata', 'Chennai', 'Mumbai');

-- Q2: List the names of the driver who have delivered shipments weighing over 200 pounds.
SELECT
  driver_name,
  weight
FROM
  truck
  JOIN shipment on truck.truck_no = shipment.truck_no
WHERE
  shipment.weight > 200;

-- Q3: Retrieve the maximum and minimum weights of the shipments. Rename the output as Max_Weight and Min_Weight respectively.
SELECT
  MAX(weight) as Max_Weight,
  MIN(weight) as Min_Weight
FROM
  shipment;

-- Q4: For each customer, what is the average weight of package sent by the customer? 
SELECT
  cust_name,
  ROUND(AVG(weight), 2)
FROM
  customer
  JOIN shipment on customer.cust_id = shipment.cust_id
GROUP BY
  customer.cust_id
ORDER BY
  AVG(weight) DESC;

-- Q5: List the names and populations of cities that have received a shipment weighing over 100 pounds.
SELECT
  city_name,
  population,
  weight
FROM
  city
  JOIN shipment ON shipment.destination = city.city_name
WHERE
  weight > 100
ORDER BY
  weight ASC;

-- Q6: List cities that have received shipments from every customer.
SELECT
  city.city_name
FROM
  city
  JOIN shipment on shipment.destination = city.city_name
GROUP BY
  city.city_name
HAVING
  COUNT(DISTINCT shipment.cust_id) = (
    SELECT
      COUNT(cust_id)
    FROM
      customer
  );

-- Q7: For each city, what is the maximum weight of a package sent to that city?
SELECT
  city.city_name,
  MAX(shipment.weight)
FROM
  city
  JOIN shipment on city.city_name = shipment.destination
GROUP BY
  city.city_name;

-- Q8: List the name and annual revenue of customers whose shipments have been delivered by truck driver ‘IQBAL’.
SELECT DISTINCT
  customer.cust_name,
  customer.annual_revenue
FROM
  customer
  JOIN shipment on customer.cust_id = shipment.cust_id
  JOIN truck on shipment.truck_no = truck.truck_no
WHERE
  driver_name = 'IQBAL';

-- Q9: List drivers who have delivered shipments to every city.
SELECT
  truck.driver_name
FROM
  truck
  JOIN shipment on shipment.truck_no = truck.truck_no
GROUP BY
  truck.truck_no
HAVING
  COUNT(DISTINCT shipment.destination) = (
    SELECT
      COUNT(city_name)
    FROM
      city
  );

-- Q10: For each city, with population over 1 million, what is the minimum weight of a package sent to that city.
SELECT
  city.city_name,
  MIN(shipment.weight)
FROM
  city
  JOIN shipment on shipment.destination = city.city_name
WHERE
  city.population > 1000000
GROUP BY
  city.city_name
