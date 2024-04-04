update
    Students
set
    Marks = (
        select
            Count(Mark)
        from
            Marks
        where
            StudentId = Students.StudentId
    )
where
    True
;
