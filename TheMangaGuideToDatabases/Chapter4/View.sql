create view expensive_product_table
as select * 
from product_table
where UNIT_PRICE>=200;

select * from expensive_product_table;

-- drop view expensive_product_table; 
