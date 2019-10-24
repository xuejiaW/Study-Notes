create table if not exists SALES_TABLE
(
REPORT_CODE int,
EXPORT_DATE varchar(10),
EXPORT_DESTINATION_CODE int,

primary key(REPORT_CODE) 
);

create table if not exists PRODUCT_TABLE
(
PRODUCT_CODE int,
PRODUCT_NAME varchar(255),
UNIT_PRICE int,

primary key(PRODUCT_CODE)
);

create table if not exists sales_statement_table
(
REPORT_CODE int,
PRODUCT_CODE int,
QUANTITY int,

primary key(REPORT_CODE,PRODUCT_CODE)
);

create table if not exists export_destination_table
(
EXPORT_DESTINATION_CODE int,
EXPORT_DESTINATION_NAME varchar(255),

primary key(EXPORT_DESTINATION_CODE)
);