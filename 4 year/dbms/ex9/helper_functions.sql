CREATE EXTENSION IF NOT EXISTS pgcrypto;

-- generate salt for password
CREATE OR REPLACE FUNCTION GenSalt()
RETURNS VARCHAR(32) LANGUAGE plpgsql SECURITY DEFINER AS $$
DECLARE
    chars VARCHAR(62) := 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    salt VARCHAR(32) := '';
    i INT := 1;
BEGIN
    WHILE i <= 32 LOOP
        salt := salt || substr(chars, ((random() * 61) + 1)::integer, 1);
        i := i + 1;
    END LOOP;
    RETURN salt;
END;
$$;

-- add an user with UID, generate salt and store hash(password + salt), salt
CREATE OR REPLACE PROCEDURE AddUser(IN UID INT, IN Pass VARCHAR)
LANGUAGE plpgsql SECURITY DEFINER AS $$
DECLARE
    salt VARCHAR(32) := GenSalt();
BEGIN
    INSERT INTO Users (UserId, PasswordHash, Salt)
    VALUES (UID, ENCODE(DIGEST(Pass || salt::VARCHAR, 'sha512'), 'hex')::BYTEA, salt);
END;
$$;

-- check is user exists and the password is correct
CREATE OR REPLACE FUNCTION CheckUser(IN UID INT, IN Pass VARCHAR)
RETURNS BOOLEAN LANGUAGE plpgsql SECURITY DEFINER AS $$
BEGIN
    RETURN EXISTS (
        SELECT
            UserId,
            Salt
        FROM
            Users
        WHERE
            UserId = UID
            AND PasswordHash = ENCODE(DIGEST(Pass || Salt, 'sha512'), 'hex')::BYTEA
    );
END;
$$;

-- find seats that are 1) unavailable 2) bought 3) reserved
CREATE OR REPLACE FUNCTION TakenSeats(IN FId INT)
RETURNS TABLE (SNo VARCHAR(4)) LANGUAGE plpgsql SECURITY DEFINER AS $$
BEGIN
    RETURN QUERY
    SELECT
        SeatNo
    FROM
        Booking
    WHERE
        FlightId = FId
        AND Expires > NOW()
        OR IsBought
    UNION
    SELECT
        SeatNo
    FROM
        AllSeats
    WHERE
        FlightId = FId
        AND FlightTime < NOW();

END;
$$;
