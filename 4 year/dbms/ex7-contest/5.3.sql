create view Debts as
    select
        StudentId, Count(distinct CourseId) as Debts
    from
        Plan
        natural join Students
    where
        not exists (
            select
                Mark
            from
                Marks
            where
                StudentId = Students.StudentId
                and CourseId = Plan.CourseId
        )
    group by
        StudentId
;