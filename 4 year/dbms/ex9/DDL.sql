CREATE TABLE Flights (
    FlightId INT NOT NULL primary key,
    FlightTime TIMESTAMP NOT NULL,
    PlaneId INT NOT NULL
);

CREATE TABLE Seats (
    PlaneId INT NOT NULL,
    SeatNo VARCHAR(4) NOT NULL -- 123A
);

-- Table for users and passwords (hash) with salt
CREATE TABLE Users (
    UserId INT NOT NULL primary key,
    PasswordHash BYTEA NOT NULL,
    Salt VARCHAR(32) NOT NULL
);

-- Table for booking status of seats
CREATE TABLE Booking (
    FlightId INT NOT NULL,
    SeatNo VARCHAR(4) NOT NULL,
    IsBought BOOLEAN NOT NULL,
    UserId INT,
    Expires TIMESTAMP,
    primary key (FlightId, SeatNo),
    foreign key (FlightId) references Flights (FlightId),
    foreign key (UserId) references Users (UserId)
);

-- View for all flights and seats
CREATE VIEW AllSeats AS
SELECT
    FlightId,
    FlightTime,
    PlaneId,
    SeatNo
FROM
    Flights NATURAL
    JOIN Seats;