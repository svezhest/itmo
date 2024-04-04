update
    Students
set
    Marks = (
        select
            Count(distinct CourseId)
        from
            Marks
        where
            StudentId = Students.StudentId
            and Mark is not null
    )
where
    True
;
