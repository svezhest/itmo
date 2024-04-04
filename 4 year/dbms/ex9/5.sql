CREATE OR REPLACE FUNCTION BuyReserved(
    IN UID INT,
    IN Pass VARCHAR(50),
    IN FId INT,
    IN SNo VARCHAR(4)
) RETURNS BOOLEAN LANGUAGE plpgsql SECURITY definer AS $$ BEGIN
    IF NOT EXISTS (
        SELECT
            FlightId
        FROM
            Flights
        WHERE
            FlightId = FId
    ) OR NOT CheckUser(UID, Pass) THEN RETURN FALSE;

END IF;

IF EXISTS (
    SELECT
        FlightId
    FROM
        Booking
    WHERE
        FlightId = FId
        AND SeatNo = SNo
        AND NOT IsBought
        AND UserId = UID
        AND Expires > now()
) THEN
UPDATE
    Booking
SET
    IsBought = TRUE,
    UserId = NULL,
    Expires = NULL
WHERE
    FlightId = FId
    AND SeatNo = SNo;

RETURN TRUE;

END IF;

RETURN FALSE;

END $$;