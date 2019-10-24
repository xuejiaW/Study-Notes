-- 按地区显示评价单价
select DISTRICT,AVG(UNIT_PRICE),UNIT_PRICE
from product_table
group by DISTRICT;

-- 找水果平均单价大于300的地区
select DISTRICT,AVG(UNIT_PRICE),UNIT_PRICE
from product_table
group by DISTRICT
having AVG(UNIT_PRICE)>=200;

-- 找至少包含了三种水果的地区
select DISTRICT,COUNT(*)
from product_table
group by DISTRICT
having count(*)>=3;

