CREATE OR REPLACE FUNCTION FlightsStatistics(IN UID INT, IN Pass VARCHAR(50))
RETURNS TABLE (
    CanBook INT,
    CanBuy INT,
    Free INT,
    Reserved INT,
    Sold INT
) LANGUAGE plpgsql SECURITY definer AS $$
DECLARE
    allPossibleSeats INT;

boughtSeats INT;

reservedSeats INT;

freeSeats INT;

reservedByUser INT;

BEGIN
    IF NOT CheckUser(UID, Pass) THEN RETURN;

END IF;

allPossibleSeats := (
    SELECT
        COUNT(*)
    FROM
        AllSeats
    WHERE
        FlightTime > now()
);

SELECT
    COUNT(
        CASE
            WHEN IsBought
            AND FlightTime > now() THEN 1
        END
    ) AS bought,
    COUNT(
        CASE
            WHEN NOT IsBought
            AND Expires > now()
            AND FlightTime > now() THEN 1
        END
    ) AS booked,
    COUNT(
        CASE
            WHEN NOT IsBought
            AND UserId = UID
            AND Expires > now()
            AND FlightTime > now() THEN 1
        END
    ) AS bookedByUser INTO boughtSeats,
    reservedSeats,
    reservedByUser
FROM
    Booking NATURAL
    JOIN AllSeats;

freeSeats := allPossibleSeats - boughtSeats - reservedSeats;

RETURN query
SELECT
    *
FROM
    (
        VALUES
            (
                freeSeats,
                freeSeats + reservedByUser,
                freeSeats,
                reservedSeats,
                boughtSeats
            )
    ) AS t (CanBook, CanBuy, Free, Reserved, Sold);

END $$;