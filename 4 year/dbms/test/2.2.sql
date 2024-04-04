SELECT
    TeamName
FROM
    Teams
WHERE
    NOT EXISTS (
        SELECT TeamId
        FROM
            Runs,
            Sessions
        WHERE
            ContestId = :ContestId
            AND Accepted = 1 
            AND Runs.SessionId = Sessions.SessionId
            AND Letter = :Letter
            AND TeamId = Teams.TeamId
    )