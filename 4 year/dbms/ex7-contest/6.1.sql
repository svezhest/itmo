create assertion
  assert
check (
  not exists (
  select
    StudentId, CourseId
  from
    Marks
  where
    CourseId not in (
      select
        CourseId
      from
        Plan
        natural join Students
      where
        StudentId = Marks.StudentId
    )
    select
      StudentId, CourseId
    from
      Plan
      natural join Students
  )
)
;
CREATE ASSERTION NoExtraMarks CHECK (
  NOT EXISTS (
    SELECT *
    FROM Marks
    WHERE CourseId NOT IN (
      SELECT CourseId
      FROM Plan NATURAL JOIN Students
      WHERE StudentId = Marks.StudentId
    )
  )
);