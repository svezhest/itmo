CREATE OR REPLACE PROCEDURE CompressSeats(IN FId INT) LANGUAGE plpgsql SECURITY definer AS $$
DECLARE
    curSeat VARCHAR(4);

DECLARE
    cursorSeats CURSOR FOR
SELECT
    SeatNo
FROM
    AllSeats
WHERE
    FlightId = FId
ORDER BY
    SeatNo FOR READ ONLY;

    cursorBought CURSOR FOR
SELECT
    SeatNo
FROM
    Booking
WHERE
    FlightId = FId
    AND IsBought
ORDER BY
    SeatNo FOR
UPDATE
;

    cursorReserved CURSOR FOR
SELECT
    SeatNo
FROM
    Booking
WHERE
    FlightId = FId
    AND NOT IsBought
ORDER BY
    SeatNo FOR
UPDATE
;

BEGIN
    IF NOT EXISTS (
        SELECT
            FlightId
        FROM
            Flights
        WHERE
            FlightId = FId
    ) THEN RETURN;

END IF;

OPEN cursorSeats;

FOR seatNumber IN cursorBought
LOOP
    FETCH next
FROM
    cursorSeats INTO curSeat;

UPDATE
    Booking
SET
    SeatNo = curSeat
WHERE
    CURRENT OF cursorBought;

END
LOOP
;

FOR seatNumber IN cursorReserved
LOOP
    FETCH next
FROM
    cursorSeats INTO curSeat;

UPDATE
    Booking
SET
    SeatNo = curSeat
WHERE
    CURRENT OF cursorReserved;

END
LOOP
;

CLOSE cursorSeats;

END $$;