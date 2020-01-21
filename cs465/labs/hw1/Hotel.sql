drop table if exists Hotel;
drop table if exists Room;
drop table if exists Booking;
drop table if exists Guest;

create table Hotel(
    hotelNo int(7),
    hotelName varchar(30),
    city varchar(20));

create table Room(
       roomNo int(3),
       hotelNo int(4),
       type varchar(9),
       price dec(5,2));

create table Booking(
       hotelNo int(4),
       guestNo int(7),
       dateFrom date,
       dateTo date,
       roomNo int(3));

create table Guest(
       guestNo int(7),
       guestName varchar(30),
       guestAddress varchar(50));

insert into Hotel values(1, 'Grosvenor Hotel', 'London');
insert into Hotel values(2, 'Holiday Inn', 'Knoxville');
insert into Hotel values(3, 'Hilton', 'Knoxville');
insert into Hotel values(4, 'Marriott', 'Memphis');
insert into Hotel values(5, 'Wyndham', 'London');
insert into Hotel values(6, 'Super 8', 'Memphis');
insert into Hotel values(7, 'Days Inn', 'London');

insert into Room values(100, 1, 'double', 89.99);
insert into Room values(200, 1, 'family', 109.99);
insert into Room values(300, 1, 'king', 135.50);
insert into Room values(500, 2, 'king', 205);
insert into Room values(100, 2, 'penthouse', 249.99);
insert into Room values(200, 2, 'double', 99.99);
insert into Room values(300, 2, 'double', 109.99);
insert into Room values(400, 2, 'family', 149.99);
insert into Room values(400, 1, 'penthouse', 899.99);
insert into Room values(450, 2, 'double', 27.95);
insert into Room values(250, 2, 'family', 32.50);
insert into Room values(110, 1, 'double', 35.00);
insert into Room values(105, 1, 'king', 200.00);
insert into Room values(235, 3, 'family', 39.00);
insert into Room values(211, 3, 'penthouse', 200.00);
insert into Room values(205, 3, 'double', 60.00);
insert into Room values(315, 4, 'family', 39.00);
insert into Room values(401, 4, 'double', 70.00);
insert into Room values(210, 4, 'double', 60.00);
insert into Room values(209, 5, 'family', 45.00);
insert into Room values(711, 5, 'double', 39.00);
insert into Room values(805, 5, 'penthouse', 320.00);
insert into Room values(123, 6, 'double', 50.00);
insert into Room values(368, 6, 'family', 60.00);
insert into Room values(362, 6, 'penthouse', 250.00);
insert into Room values(274, 7, 'double', 32.99);
insert into Room values(236, 7, 'family', 39.99);
insert into Room values(582, 7, 'penthouse', 200.00);

insert into Booking values(1, 33, '2020-01-11', '2020-02-1', 100);
insert into Booking values(1, 31, '2020-01-21', '2020-01-30', 200);
insert into Booking values(1, 20, '2020-01-30', '2020-02-03', 200);
insert into Booking values(1, 20, '2020-02-11', '2020-02-14', 100);
insert into Booking values(1, 21, '2020-02-18', '2020-02-19', 100);
insert into Booking values(1, 22, '2020-02-23', '2018-10-28', 100);
insert into Booking values(1, 21, '2020-02-2', '2018-10-01', 100);

insert into Booking values(1, 30, '2020-02-11', '2020-02-14', 200);
insert into Booking values(1, 31, '2020-02-15', '2020-02-20', 200);
insert into Booking values(1, 32, '2020-02-27', '2020-02-30', 200);
insert into Booking values(1, 33, '2020-02-1', '2020-02-02', 200);

insert into Booking values(1, 41, '2020-02-05', '2020-02-06', 300);
insert into Booking values(1, 42, '2020-02-15', '2020-02-20', 300);
insert into Booking values(1, 33, '2020-02-20', '2020-02-25', 300);
insert into Booking values(1, 21, '2020-02-25', '2018-10-02', 300);
insert into Booking values(1, 33, '2020-02-06', '2020-02-10', 300);

insert into Booking values(2, 21, '2020-02-18', '2020-02-25', 100);
insert into Booking values(2, 42, '2020-02-05', '2020-02-28', 500);
insert into Booking values(2, 31, '2020-02-09', '2018-12-11', 300);
insert into Booking values(2, 31, '2020-02-11', '2020-02-12', 300);

insert into Guest values(20, 'Brad Vander Zanden', 'Knoxville, TN');
insert into Guest values(21, 'Minnie Mouse', 'Orlando, FL');
insert into Guest values(22, 'Wily Coyote', 'Phoenix, AZ');

insert into Guest values(30, 'Daffy Duck', 'Knoxville, TN');
insert into Guest values(31, 'Winnie The Pooh', 'Phoenix, AZ');
insert into Guest values(32, 'Pluto', 'Phoenix, AZ');
insert into Guest values(33, 'Snow White', 'Orlando, FL');

insert into Guest values(40, 'Bugs Bunny', 'Ithaca, NY');
insert into Guest values(41, 'Quickdraw McGraw', 'Townsend, TN');
insert into Guest values(42, 'Cinderella', 'Orlando, FL');
