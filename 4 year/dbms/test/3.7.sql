MERGE INTO Runs r USING Sessions s ON r.SessionId = s.SessionId
AND s.ContestId = :ContestId
AND r.Letter = :Letter
AND r.Accepted = 1
WHEN matched THEN
UPDATE
SET
    SubmitTime = 0
    WHEN NOT matched THEN
INSERT
    (SessionId, Letter, SubmitTime, Accepted)
VALUES
    (s.SessionId, :Letter, 0, 1);