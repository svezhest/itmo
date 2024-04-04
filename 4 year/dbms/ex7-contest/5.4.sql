create view StudentDebts as
    select
        StudentId, (
            select
                count(distinct CourseId) 
            from 
                Students S
                natural join Plan 
            where
                Students.StudentId = S.StudentId
                and not exists (
                    select
                        Mark
                    from
                        Marks
                    where
                        StudentId = S.StudentId
                        and CourseId = Plan.CourseId
                )
        ) as Debts 
    from
        Students
;
