CREATE OR REPLACE FUNCTION FreeSeats(IN FId INT) 
RETURNS TABLE (SeatNo VARCHAR(4)) LANGUAGE plpgsql SECURITY definer AS $$
DECLARE
    PID INT;

BEGIN
    PID := (
        SELECT
            PlaneId
        FROM
            Flights
        WHERE
            FlightId = FId
    );

RETURN query
SELECT
    s.SeatNo
FROM
    Seats s
WHERE
    PlaneId = PID
    AND s.SeatNo NOT IN (
        SELECT
            TakenSeats.SNo
        FROM
            TakenSeats(FId)
    );

END $$;