update
    Students
set
    Debts = (
        select
            Count(distinct CourseId)
        from
            Plan
            natural join Students
        where
            StudentId = :StudentId
            and not exists (
                select
                    Mark
                from
                    Marks
                where
                    StudentId = :StudentId
                    and CourseId = Plan.CourseId
            )
    )
where
    StudentId = :StudentId
;

