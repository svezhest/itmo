CREATE
OR REPLACE FUNCTION Reserve(
    IN UID INT,
    IN Pass VARCHAR(50),
    IN FId INT,
    IN SNo VARCHAR(4)
) returns BOOLEAN LANGUAGE plpgsql SECURITY definer AS $$ BEGIN
    IF NOT EXISTS (
        SELECT
            FlightId
        FROM
            Flights
        WHERE
            FlightId = FId
    )
    OR NOT CheckUser(UID, Pass)
    OR SNo NOT IN (
        SELECT
            SeatNo
        FROM
            AllSeats
        WHERE
            FlightId = FId
    )
    OR SNo IN (
        SELECT
            TakenSeats.SNo
        FROM
            TakenSeats(FId)
    ) THEN RETURN FALSE;

END IF;

INSERT INTO
    Booking (FlightId, SeatNo, IsBought, UserId, Expires)
VALUES
    (FId, SNo, FALSE, UID, now() + INTERVAL '3 day')
ON CONFLICT (FlightId, SeatNo) DO
UPDATE
SET
    UserId = excluded.UserId,
    Expires = now() + INTERVAL '3 day'
WHERE
    NOT Booking.IsBought;

RETURN TRUE;

END $$;