update
    Students
set
    Debts = (
        select
            Count(distinct CourseId)
        from
            Plan
            natural join Students as S
        where
            S.StudentId = Students.StudentId
            and not exists (
                select
                    Mark
                from
                    Marks
                where
                    StudentId = Students.StudentId
                    and CourseId = Plan.CourseId
            )
    )
where
    GroupId = (
        select
            GroupId
        from
            Groups
        where
            GroupName = :GroupName
    )
;
