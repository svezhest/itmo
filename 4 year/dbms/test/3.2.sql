DELETE FROM
    Runs
WHERE
    Runs.SessionId IN (
        SELECT
            SessionId
        FROM
            Sessions NATURAL
            JOIN Contests
        WHERE
            ContestName = :ContestName
    );