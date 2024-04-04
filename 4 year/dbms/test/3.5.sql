UPDATE
    Runs
SET
    Accepted = 0
WHERE
    RunId IN (
        SELECT
            RunId
        FROM
            Runs NATURAL
            JOIN (
                SELECT
                    SessionId,
                    Letter,
                    MIN(SubmitTime) SubmitTime
                FROM
                    Runs
                GROUP BY
                    SessionId,
                    Letter
            ) as A
    );