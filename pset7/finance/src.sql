--DDL

create table portfolio(
id_portfolio integer primary key autoincrement,
name text not null,
shares integer not null,
price float not null,
total float not null,
symbol text not null,
user_id integer not null,
foreign key(user_id) references users(id)
);

create table history(
id_histories INTEGER
constraint history_pk
primary key autoincrement,
symbol text not null,
price float not null,
transact_date datetime default current_timestamp,
user_id integer not null,
foreign key(user_id) references users(id)
);