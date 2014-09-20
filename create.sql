drop table system;
drop table user;
drop table template;
drop table minutia;

create table system(id int not null, falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, mode int, primary key (id));
create table user(id int not null, idSystem int not null, name varchar(40), rg varchar(15), cpf varchar(11), nusp varchar(10), email varchar(50), falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, minimumScore int, primary key (id), foreign key (idSystem) references system(id));
create table template(id int not null, idUser int not null, registerDate text, quality int, type int, primary key (id), foreign key (idUser) references system(id));
create table minutia(id int not null, idTemplate int not null, x int, y int, theta int, quality int, primary key (id), foreign key (idTemplate) references user(id));

insert into system values(1,0,0,0,0,0);
insert into user values(1,1,'Priscila','','','','',0,0,0,0,60);
insert into template values(1,1,'',0,0);