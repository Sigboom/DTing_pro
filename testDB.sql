PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE first (
name text,
age smallint,
sex varchar(4),
score int
);
INSERT INTO first VALUES('xjh',109,'man',100);
COMMIT;
