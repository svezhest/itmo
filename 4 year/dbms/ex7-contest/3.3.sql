update
    Students
set
    Marks = Marks + (
        select
            Count(Mark)
        from
            NewMarks
        where
            StudentId = Students.StudentId
    )
where
    True
;
