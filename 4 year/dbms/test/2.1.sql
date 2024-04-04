SELECT
    TeamId
FROM
    Sessions
WHERE
    ContestId = :ContestId
    AND SessionId IN (
        SELECT
            SessionId
        FROM
            Runs
        WHERE
            Letter = :Letter
            AND Accepted = 0
    );