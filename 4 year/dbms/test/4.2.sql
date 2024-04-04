SELECT
    TeamId,
    COUNT (Letter) AS Opened
FROM
    (
        SELECT
            DISTINCT TeamId,
            Letter,
            ContestId
        FROM
            Sessions NATURAL
            JOIN Runs
    ) A
GROUP BY
    TeamId;