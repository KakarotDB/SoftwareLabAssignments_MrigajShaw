import random
import csv 

random.seed(22)

regions = [1,2,3,4]
salesmen = [1,2,3,4,5,6]
products = ['A1010000','B2000000','C3000000','D4000000','E5000000','F6000000','G7000000','H8000000']

n = 1500

rows = []

for _ in range(n):
    region = random.choice(regions)
    salesman = random.choice(salesmen)
    product = random.choice(products)

    units = random.choice(
            [random.randint(1, 10)] * 6 + [random.randint(11,20)] * 3 + 
            [random.randint(21,35)] * 1
    )

    rows.append((region, salesman, product, units)) 

random.shuffle(rows)

with open('sales_data.csv', 'w') as f:
    writer = csv.writer(f)
    writer.writerow(['Region no','Salesman no','Product Code','Units Sold'])
    writer.writerows(rows);
