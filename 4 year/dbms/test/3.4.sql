UPDATE
    Runs
SET
    Accepted = 1
WHERE
    RunId IN (
        SELECT
            RunId
        FROM
            Runs NATURAL
            JOIN (
                SELECT
                    SessionId,
                    MAX(SubmitTime) AS SubmitTime
                FROM
                    Runs
                WHERE
                    Accepted = 0
                GROUP BY
                    SessionId
            ) as A
    );