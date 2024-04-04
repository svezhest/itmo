-- запрос: перевести всех сотрудников из одной в другую локацию
-- рекомендуемая изоляция: Serializable
CREATE OR REPLACE PROCEDURE MoveEmployees(_location_id_1 int, _location_id_2 int)
AS
$$
BEGIN
    UPDATE 
        EmployeeLocation 
    SET 
        location_id = _location_id_2 
    WHERE 
        location_id = _location_id_1 
        AND NOT EXISTS (SELECT employee_id FROM EmployeeLocation AS A WHERE A.employee_id = employee_id and A.location_id = _location_id_2) 
    ;

    DELETE FROM 
        EmployeeLocation
    WHERE
        location_id = _location_id_1
    ;
END;
$$ LANGUAGE plpgsql;

select count(*) from EmployeeLocation where location_id = 4;
call MoveEmployees(4, 100);
select count(*) from EmployeeLocation where location_id = 4;

-- запрос: научить всех сотрудников на локации всему, что умеют их коллеги с такой же должностью
-- побочный эффект: стоит учесть, что сотрудники работают не только на одной локации
-- рекомендуемая изоляция: Read Commited.
CREATE OR REPLACE PROCEDURE AutoCompetentions(_location_id int)
AS
$$
BEGIN
    INSERT INTO
        EmployeeWorkType (employee_id, type_id)
    SELECT DISTINCT
        employee_id, target_type_id
    FROM
        Employees
        NATURAL JOIN Professions
        NATURAL JOIN EmployeeLocation
        NATURAL JOIN (SELECT DISTINCT type_id AS target_type_id, profession_id, location_id FROM ViewAll)
    WHERE location_id = 1
    ON CONFLICT (employee_id, type_id) DO NOTHING
    ;
END;
$$ LANGUAGE plpgsql;

select count(*) from (EmployeeLocation natural join EmployeeWorkType)  where location_id = 1;
call AutoCompetentions(1);
select count(*) from (EmployeeLocation natural join EmployeeWorkType)  where location_id = 1;

-- запрос: удалить из всех локаций сотрудников, у которых is_active = false
-- рекомендуемая изоляция: Read Uncommited. 
CREATE OR REPLACE PROCEDURE CleanUpEmployeeLocation()
AS
$$
BEGIN
    DELETE FROM 
        EmployeeLocation
    WHERE
        employee_id IN (SELECT employee_id FROM Employees WHERE NOT is_active)
    ;
END;
$$ LANGUAGE plpgsql;

select count(*) from EmployeeLocation where employee_id = 5;
call CleanUpEmployeeLocation();
select count(*) from EmployeeLocation where employee_id = 5;