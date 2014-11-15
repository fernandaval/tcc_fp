drop table system;
drop table user;
drop table template;

create table system(id integer not null, falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, mode int, primary key (id));
create table user(id integer not null, name varchar(40), rg varchar(15), cpf varchar(11), nusp varchar(10), email varchar(50), falseRejection int, falseAcceptance int, trueRejection int, trueAcceptance int, minimumScore int, primary key (id));
create table template(id integer not null, idUser int not null, registerDate text, quality int, type int, minutiae clob, primary key (id), foreign key (idUser) references system(id));

insert into system (id, falseRejection, falseAcceptance, trueRejection, trueAcceptance, mode) values(1,0,0,0,0,0);
insert into system (id, falseRejection, falseAcceptance, trueRejection, trueAcceptance, mode) values(2,0,0,0,0,0);
insert into system (id, falseRejection, falseAcceptance, trueRejection, trueAcceptance, mode) values(31,0,0,0,0,0);
insert into system (id, falseRejection, falseAcceptance, trueRejection, trueAcceptance, mode) values(32,0,0,0,0,0);
insert into system (id, falseRejection, falseAcceptance, trueRejection, trueAcceptance, mode) values(33,0,0,0,0,0);

insert into user (name, rg, cpf, nusp, email, falseRejection, falseAcceptance, trueRejection, trueAcceptance, minimumScore) values('Priscila','','','','',0,0,0,0,60);

insert into template (idUser, registerDate, quality, type, minutiae) values(1,'',0,0,'46 431 0 91
68 392 0 95
69 446 0 92
69 415 0 45
69 406 0 45
69 361 0 45
70 420 0 44
70 352 0 44
70 346 0 46
70 333 0 46
73 451 11 46
73 365 0 44
74 312 0 94
75 282 0 46
76 459 11 45
78 459 11 46
78 403 169 46
80 322 11 46
80 294 0 46
80 216 0 22
81 413 169 45
83 471 11 8
83 452 11 46
86 262 0 48
');
insert into template (idUser, registerDate, quality, type, minutiae) values(2,'',0,0,'86 155 0 46
86 140 0 46
87 270 0 47
87 228 0 22
87 199 0 22
87 176 0 47
87 129 0 45
87 106 0 48
88 238 0 23
88 188 349 23
89 456 11 22
89 445 191 45
89 371 0 44
90 402 157 46
91 435 11 45
91 379 337 45
92 90 0 46
93 144 0 47
94 169 349 47
96 323 34 45
97 245 0 22
98 366 180 22
100 378 0 21
100 355 11 22
100 336 214 46
105 367 191 22
106 395 349 22
106 276 11 46
109 96 180 46
110 119 180 44
110 90 180 46
111 113 169 45
112 259 191 44
112 165 180 44
113 153 180 44
114 166 180 44
115 178 180 45
117 187 180 8
118 347 0 45
118 321 202 45
118 141 180 44
120 435 0 46
121 471 169 8
121 465 180 20
123 266 180 43
124 333 11 45
124 283 180 43
126 403 180 44
127 430 180 44
127 424 180 43
127 322 191 44
127 192 180 21
128 244 180 22
128 226 180 21
129 436 180 43
130 453 180 43
131 215 180 21
131 165 0 84
132 311 180 88
133 299 180 86
133 161 180 91
134 396 180 46
134 345 180 45
137 379 180 45
137 327 180 92
137 303 180 80
139 158 180 93
139 124 180 91
144 363 180 90
145 413 180 91
145 294 180 91
150 447 180 91
156 208 180 95
');
