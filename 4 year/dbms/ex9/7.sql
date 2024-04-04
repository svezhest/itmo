CREATE OR REPLACE FUNCTION FlightStat(IN UID INT, IN Pass VARCHAR(50), IN FId INT)
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
    reservedByThisUser INT;

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
        AND FlightId = FId
);

boughtSeats := (
    SELECT
        COUNT(*)
    FROM
        Booking NATURAL
        JOIN AllSeats
    WHERE
        IsBought
        AND FlightTime > now()
        AND FlightId = FId
);

reservedSeats := (
    SELECT
        COUNT(*)
    FROM
        Booking NATURAL
        JOIN AllSeats
    WHERE
        NOT IsBought
        AND Expires > now()
        AND FlightTime > now()
        AND FlightId = FId
);

reservedByThisUser := (
    SELECT
        COUNT(*)
    FROM
        Booking NATURAL
        JOIN AllSeats
    WHERE
        NOT IsBought
        AND UserId = UID
        AND Expires > now()
        AND FlightTime > now()
        AND FlightId = FId
);

freeSeats := allPossibleSeats - boughtSeats - reservedSeats;

RETURN query
SELECT
    *
FROM
    (
        VALUES
            (
                freeSeats,
                freeSeats + reservedByThisUser,
                freeSeats,
                reservedSeats,
                boughtSeats
            )
    ) AS t (CanBook, CanBuy, Free, Reserved, Sold);

END $$;