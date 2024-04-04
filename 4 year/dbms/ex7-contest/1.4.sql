delete from
    Students
where
    StudentId in (
        select
            StudentId
        from
            Marks
        group by
            StudentId
        having Count(StudentId) >= 3
    )
;
