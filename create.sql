drop table system;
drop table user;
drop table template;
drop table minutia;

create table system(id integer not null, falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, mode int, primary key (id));
create table user(id integer not null, idSystem int not null, name varchar(40), rg varchar(15), cpf varchar(11), nusp varchar(10), email varchar(50), falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, minimumScore int, primary key (id), foreign key (idSystem) references system(id));
create table template(id integer not null, idUser int not null, registerDate text, quality int, type int, primary key (id), foreign key (idUser) references system(id));
create table minutia(id integer not null, idTemplate int not null, x int, y int, theta int, quality int, primary key (id), foreign key (idTemplate) references user(id));

insert into system (falseRejection, falseAcceptance, trueRejection, trueAcceptance, mode) values(0,0,0,0,0);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'Priscila','','','','',0,0,0,0,60);
insert into template (idUser, registerDate, quality, type) values(1,'',0,0);
