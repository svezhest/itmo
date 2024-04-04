SELECT
    TeamName
FROM
    Teams NATURAL
    JOIN (
        SELECT
            DISTINCT TeamId
        FROM
            (
                SELECT
                    Teamid,
                    ContestId
                FROM
                    Teams,
                    Contests
                EXCEPT
                SELECT
                    Teamid,
                    ContestId
                FROM
                    Sessions NATURAL
                    JOIN Runs
            ) A
    ) B;