drop table system;
drop table user;
drop table template;

create table system(id integer not null, primary key (id));
create table mode(id integer not null, idSystem int not null, falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, primary key (id), foreign key (idSystem));
create table user(id integer not null, idSystem int not null, name varchar(40), rg varchar(15), cpf varchar(11), nusp varchar(10), email varchar(50), falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, minimumScore int, primary key (id, idSystem), foreign key (idSystem) references system(id));
create table template(id integer not null, idUser int not null, registerDate text, quality int, type int, minutiae clob, primary key (id), foreign key (idUser) references user(id));

insert into system (id) values(1);
insert into system (id) values(2);
insert into system (id) values(31);
insert into system (id) values(32);
insert into system (id) values(33);

insert into mode (idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance) values (1,0,0,0,0);
insert into mode (idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance) values (2,0,0,0,0);
insert into mode (idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance) values (3,0,0,0,0);
insert into mode (idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance) values (3,0,0,0,0);
insert into mode (idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance) values (3,0,0,0,0);

insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,'','','','','',0,0,0,0,60);

insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,'','','','','',0,0,0,0,60);

insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(31,'','','','','',0,0,0,0,60);

insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(32,'','','','','',0,0,0,0,60);

insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
insert into user (idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(33,'','','','','',0,0,0,0,60);
