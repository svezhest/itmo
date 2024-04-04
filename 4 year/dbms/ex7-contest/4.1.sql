insert into Marks
    (StudentId, CourseId, Mark)
select
    StudentId, CourseId, Mark
from
    NewMarks
where
    CourseId not in (
        select
            CourseId
        from
            Marks
        where
            StudentId = NewMarks.StudentId
    )
;
