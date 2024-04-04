CREATE OR REPLACE FUNCTION BuyFree(IN FID INT, IN seatNumber VARCHAR(4))
RETURNS BOOLEAN LANGUAGE plpgsql SECURITY definer AS $$ BEGIN
    IF NOT EXISTS (
        SELECT
            FlightId
        FROM
            Flights
        WHERE
            FlightId = FID
    ) THEN RETURN FALSE;

END IF;

IF seatNumber NOT IN (
    SELECT
        SeatNo
    FROM
        AllSeats
    WHERE
        FlightId = FID
) THEN RETURN FALSE;

END IF;

IF seatNumber IN (
    SELECT
        TakenSeats.SNo
    FROM
        TakenSeats(FID)
) THEN RETURN FALSE;

END IF;

INSERT INTO
    Booking (FlightId, SeatNo, IsBought)
VALUES
    (FID, seatNumber, TRUE);

RETURN TRUE;

END $$;