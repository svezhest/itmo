SELECT
    ContestId,
    Letter
FROM
    Problems
WHERE
    NOT EXISTS (
        SELECT
            SessionId
        FROM
            Sessions
        WHERE
            ContestId = Problems.ContestId
            AND SessionId NOT IN (
                SELECT
                    DISTINCT S.SessionId as SessionId
                FROM
                    Sessions S,
                    Runs R
                WHERE
                    S.SessionId = R.SessionId
                    AND ContestId = Problems.ContestId
                    AND Letter = Problems.Letter
                    AND Accepted = 1
            )
    );