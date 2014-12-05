drop table system;
drop table operationMode;
drop table user;
drop table template;

create table system(id integer not null, primary key (id));

create table operationMode(id integer not null, idSystem int not null, falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, minimumScore int, avgExecutionTime real, numberOfExecutions int, foreign key (idSystem) references system(id), primary key (id, idSystem));

create table user(id integer not null, idSystem int not null, name varchar(40), rg varchar(15), cpf varchar(11), nusp varchar(10), email varchar(50), falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, minimumScore int, foreign key (idSystem) references system(id), primary key (id, idSystem));

create table template(id integer not null, idUser int not null, idSystem int not null, registerDate text, quality real, type int, minutiae clob, foreign key (idUser) references user(id), foreign key (idSystem) references system(id), primary key (id));

insert into system (id) values(1);
insert into system (id) values(2);
insert into system (id) values(3);

insert into operationMode (id, idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore, avgExecutionTime, numberOfExecutions) values (1,1,0,0,0,0,20,0,0);
insert into operationMode (id, idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore, avgExecutionTime, numberOfExecutions) values (1,2,0,0,0,0,20,0,0);
insert into operationMode (id, idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore, avgExecutionTime, numberOfExecutions) values (1,3,0,0,0,0,20,0,0);
insert into operationMode (id, idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore, avgExecutionTime, numberOfExecutions) values (2,3,0,0,0,0,20,0,0);
insert into operationMode (id, idSystem, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore, avgExecutionTime, numberOfExecutions) values (3,3,0,0,0,0,20,0,0);

insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(3,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(4,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(5,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(6,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(7,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(8,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(9,1,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(10,1,'','','','','',0,0,0,0,60);

insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(3,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(4,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(5,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(6,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(7,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(8,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(9,2,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(10,2,'','','','','',0,0,0,0,60);

insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(3,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(4,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(5,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(6,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(7,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(8,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(9,31,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(10,31,'','','','','',0,0,0,0,60);

insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(3,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(4,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(5,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(6,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(7,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(8,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(9,32,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(10,32,'','','','','',0,0,0,0,60);

insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(1,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(2,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(3,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(4,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(5,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(6,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(7,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(8,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(9,33,'','','','','',0,0,0,0,60);
insert into user (id,idSystem, name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values(10, 33,'','','','','',0,0,0,0,60);
