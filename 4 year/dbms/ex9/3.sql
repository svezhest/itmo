CREATE
OR REPLACE FUNCTION ExtendReservation(
    IN UID INT,
    IN Pass VARCHAR(50),
    IN FID INT,
    IN seatNumber VARCHAR(4)
) RETURNS BOOLEAN LANGUAGE plpgsql SECURITY definer AS $$ BEGIN
    IF NOT EXISTS (
        SELECT
            FlightId
        FROM
            Flights
        WHERE
            FlightId = FID
    ) OR NOT CheckUser(UID, Pass) THEN RETURN FALSE;

END IF;

IF EXISTS (
    SELECT
        FlightId
    FROM
        Booking
    WHERE
        FlightId = FID
        AND SeatNo = seatNumber
        AND NOT IsBought
        AND Expires > now()
) THEN
UPDATE
    Booking
SET
    Expires = now() + INTERVAL '3 day'
WHERE
    FlightId = FID
    AND SeatNo = seatNumber;

RETURN TRUE;

END IF;

RETURN FALSE;

END $$;