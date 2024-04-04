-- представление отношения HoursWorked в формате работник - год, а не в формате работник - месяц - год.
-- помимо использование для расчетов, будет полезно и для работников
CREATE OR REPLACE VIEW ViewYearCoeff AS
SELECT
    employee_id, coeff, year_worked
FROM 
(
    SELECT
        employee_id, SUM(amount) / 12 AS coeff, year_worked
    FROM
        HoursWorked
    GROUP BY
        employee_id, year_worked
)
WHERE
    NOT coeff = 0
; 


-- получение скорректиированного профессионального коэффициента для руководящих должностей, поскольку
-- премия расчитывается, исходя из обязанностей,
-- а руководители ответственны за всё на подконтрольных им локациям
-- рекомендуемая изоляция: Read Commited.
CREATE OR REPLACE FUNCTION GetAdminCoeff(_employee_id int, _location_id int)
    RETURNS int
AS
$$
DECLARE
    _is_admin boolean = false;
    res int = 1;
BEGIN
    SELECT
        is_admin
    FROM
        (Employees NATURAL JOIN Professions)
    WHERE
        employee_id = _employee_id AND is_active
    INTO
        _is_admin
    ;

    IF _is_admin THEN
        SELECT 
            COUNT(type_id) 
        FROM 
            TypesInLocation
        WHERE 
            location_id = _location_id
        INTO
            res
        ;
    END IF
    ;

    RETURN COALESCE(res, 0)
    ;
END;
$$ LANGUAGE plpgsql;


-- узнать, на скольких локациях работает [за сколько локаций несет ответственность] сотрудник
-- рекомендуемая изоляция: Read Commited.
CREATE OR REPLACE FUNCTION GetNumberOfLocationsOfEmployee(_employee_id int)
    RETURNS int
AS
$$
DECLARE
    res int;
BEGIN
    SELECT
        COUNT(location_id) 
    FROM
        (EmployeeLocation NATURAL JOIN Employees) 
    WHERE
        employee_id = _employee_id 
    GROUP BY
        employee_id
    INTO
        res;
    
    RETURN COALESCE(res, 0)
    ;
END;
$$ LANGUAGE plpgsql;


-- просмотр итогового домножающего коэффициента для одного сотрудника, в зависимости от локации
CREATE OR REPLACE VIEW ViewYearCoeffProportionalToContribution AS
SELECT
    employee_id, location_id, A.coeff * GetAdminCoeff(A.employee_id, A.location_id) / GetNumberOfLocationsOfEmployee(A.employee_id) as coeff, year_worked
FROM
(
    ViewYearCoeff
    NATURAL JOIN EmployeeLocation
    NATURAL JOIN Employees
) AS A
WHERE
    A.is_active
;


-- получить нормированные коэффициенты для локации, сумм(коэфф.) по локации = 1
-- рекомендуемая изоляция: Read Commited.
CREATE OR REPLACE FUNCTION GetScaledCoeffs(_location_id int, _year int)
    RETURNS TABLE
    (
        employee_id int,
        coeff double precision
    )
AS
$$
DECLARE
    coeff_sum double precision = 1;
BEGIN
    SELECT
        SUM(A.coeff)
    FROM
        ViewYearCoeffProportionalToContribution AS A
    WHERE
        A.location_id = _location_id AND A.year_worked = _year
    INTO coeff_sum;

    IF coeff_sum = 0 THEN
        SELECT 1 INTO coeff_sum;
    END IF;

    RETURN QUERY
    SELECT
        A.employee_id, A.coeff / coeff_sum
    FROM 
        ViewYearCoeffProportionalToContribution as A
    WHERE
        A.location_id = _location_id AND A.year_worked = _year
    ;
END;
$$ LANGUAGE plpgsql;


-- расчёт премии сотрудникам за год
-- порядок расчёта: 
-- 1. проф. коэфф. или скорректированный проф. коэфф. для руководителей, - далее проф. коэфф.
-- 2. преревести проф. коэфф. в коэффициенты для локации, с учетом числа сотрудников
-- 3. нормированные коэффициенты для локации, - далее нормированные коэфф.
-- 4. по каждой локации разделить премию на сотрудников, с учётом нормированных коэфф., исходя из
-- результатов торговой деятельности по каждой категории товаров (в таблице BonusProfits
-- находится не прибыль, а специально выделенная под премии её часть)
-- 5. нерасходованный остаток это нормально
-- рекомендуемая изоляция: Read Commited.
CREATE OR REPLACE FUNCTION CalculateBonus(_year int)
    RETURNS TABLE
    (
        _employee_id    int,
        _bonus  bigint
    )
AS
$$
BEGIN
    RETURN QUERY
    SELECT
        employee_id, CAST(SUM(CAST(profit * coeff AS bigint)) AS bigint)
    FROM
    (
        ViewAll
        NATURAL JOIN (SELECT type_id, location_id, profit FROM BonusProfits WHERE year_accounted = _year)
        NATURAL JOIN GetScaledCoeffs(location_id, _year)
    )
    WHERE
        is_active
    GROUP BY
        employee_id
    ;
END;
$$ LANGUAGE plpgsql;

select _employee_id, _bonus from CalculateBonus(2023) order by _bonus desc;
select sum(_bonus) from CalculateBonus(2023);
select sum(profit) from BonusProfits where year_accounted = 2023;