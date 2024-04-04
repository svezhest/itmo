
```
$ sudo systemctl start postgresq

$ createdb project -U postgres

$ psql -d project -U postgres

project=# grant all privileges on database project to postgres;

project=# \i dropall.sql

project=# \i ddl.sql

project=# \i insert.sql

project=# \i select.sql

project=# \i update.sql

```