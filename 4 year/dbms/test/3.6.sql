INSERT INTO
    Runs (SubmitTime, Accepted, Letter, SessionId)
SELECT
    SubmitTime + 1,
    1,
    Letter,
    SessionId
FROM
    Runs NATURAL
    JOIN (
        SELECT
            SessionId,
            Letter,
            MAX(SubmitTime) SubmitTime
        FROM
            Runs
        GROUP BY
            SessionId,
            Letter
    ) A NATURAL
    JOIN (
        SELECT
            SessionId,
            Letter
        FROM
            Runs
        EXCEPT
        SELECT
            SessionId,
            Letter
        FROM
            Runs
        WHERE
            Accepted = 1
    ) B;