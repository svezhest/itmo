merge into
    Marks M
using
    NewMarks nm
on
    M.StudentId = NM.StudentId 
    and M.CourseId = NM.CourseId
when matched and NM.Mark > M.Mark then
    update set
        Mark = NM.Mark
when not matched then
  insert
    (StudentId, CourseId, Mark)
  values
    (NM.StudentId, NM.CourseId, NM.Mark)
;
