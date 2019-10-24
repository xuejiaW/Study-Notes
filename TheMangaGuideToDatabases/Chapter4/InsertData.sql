-- insert into
-- 	export_destination_table(EXPORT_DESTINATION_CODE,EXPORT_DESTINATION_NAME)
-- values
-- 	(12,'THE KINGDOM OF MINANMI'),
-- 	(23,'ALPHA EMPIRE'),
--     (25,'THE KINGDOM OF RITOL');


-- insert into
-- 	sales_table(REPORT_CODE,EXPORT_DATE,EXPORT_DESTINATION_CODE)
-- values
-- 	(1101,'2019-03-05',12),
--     (1102,'2019-03-07',23),
--     (1103,'2019-03-08',25),
--     (1104,'2019-03-10',12),
--     (1105,'2019-03-12',25);
    
-- insert into
-- 	sales_statement_table(REPORT_CODE,PRODUCT_CODE,QUANTITY)
-- values
-- 	(1101,101,1100),
--     (1101,102,300),
--     (1102,103,1700),
--     (1103,104,500),
--     (1104,101,2500),
--     (1105,103,2000),
--     (1105,104,700);
    

-- insert into
-- 	product_table(PRODUCT_CODE,PRODUCT_NAME,UNIT_PRICE)
-- values
-- 	(101,'MELON',800),
--     (102,'STRAWBERRY',150),
--     (103,'APPLE',120),
--     (104,'LEMON',200);
    

-- delete from product_table
-- where PRODUCT_CODE=101;

-- alter table product_table
-- add column `DISTRICT`  VARCHAR(45) null
-- after `UNIT_PRICE`;

-- update product_table set DISTRICT='South Sea' where PRODUCT_CODE=101 or PRODUCT_CODE=104;
-- update product_table set DISTRICT='Middle' where PRODUCT_CODE=102;
-- update product_table set DISTRICT='North Sea' where PRODUCT_CODE=103;

-- insert into 
-- 	product_table(PRODUCT_CODE,PRODUCT_NAME,UNIT_PRICE,DISTRICT)
-- value
-- 	(201,'Chestnut',100,'North Sea'),
--     (202,'Persimmon',160,'Middle'),
--     (301,'Peach',130,'South Sea'),
--     (302,'Kiwi',200,'South Sea');

select * from export_destination_table;
select * from product_table;
select * from sales_table;
select * from sales_statement_table;
