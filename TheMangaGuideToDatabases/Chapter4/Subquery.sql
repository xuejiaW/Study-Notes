select * from product_table
where PRODUCT_CODE IN
(select PRODUCT_CODE from sales_statement_table
where QUANTITY>=1000);

select * from sales_statement_table U
where QUANTITY >
(
	select avg(QUANTITY)
    from sales_statement_table
    where PRODUCT_CODE=U.PRODUCT_CODE
);


