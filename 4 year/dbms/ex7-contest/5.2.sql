create view AllMarks as
    select
        StudentId,
        ((select count(Mark) from Marks where StudentId = Students.StudentId)
	        + (select count(Mark) from NewMarks where StudentId = Students.StudentId)) as Marks
    from Students
;
