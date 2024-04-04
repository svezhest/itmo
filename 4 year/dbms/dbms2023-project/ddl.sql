CREATE SEQUENCE IF NOT EXISTS profession_id_seq AS int;

CREATE SEQUENCE IF NOT EXISTS employee_id_seq AS int;

CREATE SEQUENCE IF NOT EXISTS type_id_seq AS int;

CREATE TABLE IF NOT EXISTS Professions
(
    profession_id int not null default nextval('profession_id_seq'::regclass) primary key,
    profession_name varchar(50) not null unique,
    coeff double precision not null,
    is_admin boolean not null default false
    constraint coeff_valid check (coeff >= 0 and coeff <= 1)
);

CREATE TABLE IF NOT EXISTS Employees
(
    employee_id int not null default nextval('employee_id_seq'::regclass) primary key,
    full_name varchar(100) not null,
    profession_id int references Professions (profession_id),
    is_active boolean not null default true
);

CREATE TABLE IF NOT EXISTS HoursWorked
(
    employee_id int not null references Employees (employee_id),
    month_worked int not null,
    year_worked int not null,
    primary key (employee_id, month_worked, year_worked),
    amount double precision not null
);

CREATE TABLE IF NOT EXISTS Types
(
    type_id int not null default nextval('type_id_seq'::regclass) primary key,
    type_name varchar(100) not null unique
);

CREATE TABLE IF NOT EXISTS Locations
(
    location_id int not null primary key,
    location_name varchar(50) -- не несет особого значения
);

CREATE TABLE IF NOT EXISTS EmployeeWorkType
(
    employee_id int not null references Employees (employee_id),
    type_id int not null references Types (type_id),
    primary key (employee_id, type_id)
);

CREATE TABLE IF NOT EXISTS EmployeeLocation
(
    employee_id int not null references Employees (employee_id),
    location_id int not null references Locations (location_id),
    primary key (employee_id, location_id)
);

CREATE TABLE IF NOT EXISTS TypesInLocation
(
    type_id int not null references Types (type_id),
    location_id int not null references Locations (location_id),
    primary key (location_id, type_id)
);

CREATE TABLE IF NOT EXISTS BonusProfits
(
    type_id int not null references Types (type_id),
    location_id int not null references Locations (location_id),
    year_accounted int not null,
    primary key (type_id, location_id, year_accounted),
    profit bigint not null
);

-- view, выводящий ключевую информацию по структуре (кто, где, должность, с чем работает)
CREATE OR REPLACE VIEW ViewAll AS 
SELECT 
    employee_id, profession_id, type_id, location_id, is_active
FROM 
    Employees 
    NATURAL JOIN Professions 
    NATURAL JOIN Types 
    NATURAL JOIN Locations
;

-- indexes on foreign keys
CREATE INDEX ON Employees (profession_id);

-- search by the name
CREATE INDEX ON Employees (full_name);
CREATE INDEX ON Professions (profession_name);
CREATE INDEX ON Types (type_name);
