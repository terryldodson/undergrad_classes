DROP TABLE Branch;
DROP TABLE Staff;
DROP TABLE PropertyForRent;
DROP TABLE Client;
DROP TABLE PrivateOwner;
DROP TABLE Viewing;
DROP TABLE Registration;

-- create the tables
CREATE TABLE Branch
(
	branchNo char(4),
	street varchar(15),
	city varchar(10),
	postcode varchar(10)
);

CREATE TABLE Staff
(
	staffNo varchar(4),
	fName varchar(10),
	lName varchar(10),
	position varchar(10),
	sex char(1),
	DOB varchar(10),
	salary int(5),
	branchNo char(4)
);

CREATE TABLE PropertyForRent
(
	propertyNo varchar(4),
	street varchar(15),
	city varchar(10),
	postcode varchar(10),
	propType varchar(5),
	rooms int(1),
	rent int(3),
	ownerNo char(4),
	staffNo varchar(4),
	branchNo varchar(4)
);

CREATE TABLE Client
(
	clientNo varchar(4),
	fName varchar(10),
	lName varchar(10),
	telNo varchar(16),
	prefType varchar(5),
	maxRent int(3),
	eMail varchar(30)
);

CREATE TABLE PrivateOwner
(
	ownerNo char(4),
	fName varchar(10),
	lName varchar(10),
	address varchar(50),
	telNo varchar(16),
	eMail varchar(30),
	password varchar(10)
);

CREATE TABLE Viewing
(
	clientNo varchar(4),
	propertyNo varchar(4),
	viewDate varchar(10),
	_comment varchar(20)
);

CREATE TABLE Registration
(
	clientNo varchar(4),
	branchNo char(4),
	staffNo varchar(4),
	dateJoined varchar(10)
);

-- Insert rows into the Branch table
INSERT INTO Branch VALUES( 'B005', '22 Deer Rd', 'London', 'SW1 4EH' );
INSERT INTO Branch VALUES( 'B007', '16 Argyll St', 'Aberdeen', 'AB2 3SU' );
INSERT INTO Branch VALUES( 'B003', '163 Main St', 'Glasgow', 'G11 9QX' );
INSERT INTO Branch VALUES( 'B004', '32 Manse Rd', 'Bristol', 'BS99 INZ' );
INSERT INTO Branch VALUES( 'B002', '56 Clover Dr', 'London', 'NW10 6EU' );

-- Insert rows into the Staff table
INSERT INTO Staff VALUES( 'SL21', 'John', 'White', 'Manager', 'M', '1-Oct-45', 30000, 'B005' );
INSERT INTO Staff VALUES( 'SG37', 'Ann', 'Beech', 'Assistant', 'F', '10-Nov-60', 12000, 'B003' );
INSERT INTO Staff VALUES( 'SG14', 'David', 'Ford', 'Supervisor', 'M', '24-Mar-58', 18000, 'B003' );
INSERT INTO Staff VALUES( 'SA9', 'Mary', 'Howe', 'Assistant', 'F', '19-Feb-70', 9000, 'B007' );
INSERT INTO Staff VALUES( 'SG5', 'Susan', 'Brand', 'Manager', 'F', '3-Jun-40', 24000, 'B003' );
INSERT INTO Staff VALUES( 'SL41', 'Julie', 'Lee', 'Assistant', 'F', '13-Jun-65', 9000, 'B005' );

-- Insert data into the PropertyForRent table
INSERT INTO PropertyForRent VALUES( 'PA14', '16 Holhead', 'Aberdeen', 'AB7 5SU', 'House', 6, 650, 'CO46', 'SA9', 'B007' );
INSERT INTO PropertyForRent VALUES( 'PL94', '6 Argyll St', 'London', 'NW2', 'Flat', 4, 400, 'CO87', 'SL41', 'B005' );
INSERT INTO PropertyForRent VALUES( 'PG4', '6 Lawrence St', 'Glasgow', 'G11 9QX', 'Flat', 3, 350, 'CO40', ' ', 'B003' );
INSERT INTO PropertyForRent VALUES( 'PG36', '2 Manor Rd', 'Glasgow', 'G32 4QX', 'Flat', 3, 375, 'CO93', 'SG37', 'B003' );
INSERT INTO PropertyForRent VALUES( 'PG21', '18 Dale Rd', 'Glasgow', 'G12', 'House', 5, 600, 'CO87', 'SG37', 'B003' );
INSERT INTO PropertyForRent VALUES( 'PG16', '3 Novar Dr', 'Glasgow', 'G12 9AX', 'Flat', 4, 450, 'CO93', 'SG14', 'B003' );

-- Insert rows into the Client table
INSERT INTO Client VALUES( 'CR76', 'John', 'Kay', '0207-774-5632', 'Flat', 425, 'john.kay@gmail.com' );
INSERT INTO Client VALUES( 'CR56', 'Aline', 'Stewart', '0141-848-1825', 'Flat', 350, 'astewart@hotmail.com' );
INSERT INTO Client VALUES( 'CR74', 'Mike', 'Ritchie', '01475-392178', 'House', 750, 'mritchie@yahoo.co.kr' );
INSERT INTO Client VALUES( 'CR62', 'Mary', 'Tregear', '01224-196720', 'Flat', 600, 'maryt@hotmail.co.uk' );

-- Insert rows into the PrivateOwner table
INSERT INTO PrivateOwner VALUES( 'CO46', 'Joe', 'Keogh', '2 Fergus Dr, Aberdeen AB2 7SX', '01224-861212', 'jkeogh@lhh.com', '********' );
INSERT INTO PrivateOwner VALUES( 'CO87', 'Carol', 'Farrel', '6 Achray St, Glasgow G32 9DX', '0141-357-7419', 'cfarrel@gmail.com', '********' );
INSERT INTO PrivateOwner VALUES( 'CO40', 'Tina', 'Murphy', '63 Well St, Glasgow G42', '0141-943-1728', 'tinam@hotmail.com', '********' );
INSERT INTO PrivateOwner VALUES( 'CO93', 'Tony', 'Shaw', '12 Park Pl, Glasgow G4 0QR', '0141-225-7025', 'tony.shaw@ark.com', '********' );

-- Insert rows into the Viewing table
INSERT INTO Viewing VALUES( 'CR56', 'PA14', '24-May-08', 'too small' );
INSERT INTO Viewing VALUES( 'CR76', 'PG4', '20-Apr-08', 'too remote' );
INSERT INTO Viewing VALUES( 'CR56', 'PG4', '26-May-08', '' );
INSERT INTO Viewing VALUES( 'CR62', 'PA14', '14-May-08', 'no dining room' );
INSERT INTO Viewing VALUES( 'CR56', 'PG36', '28-Apr-08', '' );

-- Insert rows into the Registration table
INSERT INTO Registration VALUES( 'CR76', 'B005', 'SL41', '2-Jan-08' );
INSERT INTO Registration VALUES( 'CR56', 'B003', 'SG37', '11-Apr-07' );
INSERT INTO Registration VALUES( 'CR62', 'B007', 'SA9', '7-Mar-07' );
