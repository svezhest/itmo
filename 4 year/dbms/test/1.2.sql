SELECT
    TeamName
FROM
    Teams
WHERE
    TeamId IN (
        SELECT
            DISTINCT TeamId
        FROM
            Sessions
        WHERE
            ContestId = :ContestId
    );