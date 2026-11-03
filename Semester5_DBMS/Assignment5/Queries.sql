-- Q1: Insert data into a table containing two attributes namely radius & circumference of circles. You may get different values of radius either from keyboard or you may generate different values.
DO $$
DECLARE 
    r NUMERIC(10, 2);
    circ NUMERIC(10, 2);
BEGIN
    FOR r in 1..20 LOOP 
        circ := 2 * pi() * r; 
        
        INSERT INTO circles (radius, circumference)
        VALUES (r, circ);
    END LOOP;
END $$;

-- Q2: Update the balance of each customer from a cust_acct table showing withdrawal of Rs.1000/- as service charge provided that the customer balance shows at least Rs.1000/-.
DO $$
DECLARE c RECORD;
BEGIN 
    FOR c in SELECT cust_id, balance FROM cust_acct LOOP 
        IF c.balance >= 1000 THEN 
            UPDATE cust_acct SET balance = balance - 1000 
            WHERE cust_id = c.cust_id;
        END IF;
    END LOOP;
END $$;

-- Q3: Update the salary of each employee from EMP table by 15% using cursor.
DO $$
DECLARE 
    cur CURSOR FOR SELECT emp_id, salary from employees;
    rec RECORD;
BEGIN 
    OPEN cur;
    LOOP 
        FETCH cur into rec;
        EXIT WHEN NOT FOUND;
        UPDATE employees SET salary = salary * 1.15 WHERE emp_id = rec.emp_id;
    END LOOP;
    CLOSE cur;
END $$;

-- Q4: Update the balance in the ITEM_MSTR table each time a transaction takes place in the
-- ITEM_TR table. If this item_id is already present in the ITEM_MSTR table an update is
-- performed to decrease the balance by the quantity specified in the ITEM_TR table.
-- If the item_id is not present in the ITEM_MSTR table, the tuple is to be inserted.
CREATE OR REPLACE FUNCTION trg_update_item() RETURNS TRIGGER AS $$ 
BEGIN 
    UPDATE item_mstr SET balance = balance - NEW.quantity WHERE item_id = NEW.item_id;
    
    IF NOT FOUND THEN
        INSERT INTO item_mstr (item_id, balance)
        VALUES (NEW.item_id, NEW.quantity);
    END IF;
    RETURN NEW;
END $$ LANGUAGE plpgsql;

CREATE TRIGGER after_item_tr
AFTER INSERT on item_tr 
FOR EACH ROW EXECUTE FUNCTION trg_update_item();

INSERT INTO item_tr (item_id, quantity) VALUES (1, 10);
INSERT INTO item_tr (item_id, quantity) VALUES (9, 7);

-- Q5: Write a PROCEDURE for raising salary of some employee by some amount. The
-- PROCEDURE to be written may carry two parameters emp_id and amt to be raised. Include
-- two exceptions which will be raised when either emp_id is not present or salary is NULL.
CREATE OR REPLACE PROCEDURE raise_salary(p_emp_id INT, amt NUMERIC)
LANGUAGE plpgsql AS $$ 
DECLARE 
    sal employees.salary%type;
BEGIN 
    SELECT salary INTO sal FROM employees WHERE emp_id = p_emp_id;

    IF NOT FOUND THEN   
        RAISE EXCEPTION 'Employee % not found', p_emp_id USING ERRCODE = 'P0002';
    ELSEIF sal IS NULL THEN 
        RAISE EXCEPTION 'Salary is null for employee %', p_emp_id USING ERRCODE = 'P0003';
    END IF;

    UPDATE employees SET salary = salary + amt WHERE emp_id = p_emp_id;
    RAISE NOTICE 'New Salary: %', sal + amt;
EXCEPTION 
    WHEN SQLSTATE 'P0002' THEN RAISE NOTICE 'emp_id is not present';
    WHEN SQLSTATE 'P0003' THEN RAISE NOTICE 'Salary of employee is null';
END $$

CALL raise_salary(101, 5000);
