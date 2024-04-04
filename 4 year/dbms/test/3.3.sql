INSERT INTO
    Sessions(TeamId, ContestId, START)
SELECT
    TeamId,
    ContestId,
    current_timestamp
FROM
    Sessions
WHERE
    ContestId = :ContestId;
    