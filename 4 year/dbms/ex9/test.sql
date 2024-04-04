INSERT INTO
    Seats (PlaneId, SeatNo)
VALUES
    (1, 10),
    (2, 20),
    (3, 30),
    (4, 2);

INSERT INTO
    Flights (FlightId, FlightTime, PlaneId)
VALUES
    (1, now() - INTERVAL '1 hour', 1),
    (2, now() + INTERVAL '2 hours', 3),
    (3, now() + INTERVAL '30 minutes', 1),
    (4, now() + INTERVAL '1 minute', 4);

CALL AddUser(1, 'asvsdfvds');

CALL AddUser(2, '21i990e3c21');

INSERT INTO
    Booking (FlightId, SeatNo, IsBought, UserId, Expires)
VALUES
    (1, 2, FALSE, 1, now() + INTERVAL '1 day'),
    (1, 8, FALSE, 2, now() - INTERVAL '2 day'),
    (1, 9, TRUE, 1, now() + INTERVAL '1 day'),
    (2, 18, TRUE, 2, now() + INTERVAL '3 day'),
    (4, 1, FALSE, 1, now() + INTERVAL '1 day');