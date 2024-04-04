DELETE FROM
    Runs
WHERE
    Runs.SessionId IN (
        SELECT
            SessionId
        FROM
            Sessions
        WHERE
            TeamId = :TeamId
    );