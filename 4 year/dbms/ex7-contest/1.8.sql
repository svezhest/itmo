delete from
    Students
where
    StudentId not in (
        select
            StudentId
        from
            Plan
            natural join Students
            natural left join Marks
        where Mark is null
        group by StudentId
        having Count(distinct CourseId) > 2
    )
;
