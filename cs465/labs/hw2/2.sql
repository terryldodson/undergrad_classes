#tried to do create domain and check afterwards but some some reason my create domain was   #giving errors so I didn't know how to fix it. Below was my plan for the whole problem (rest#of the problem) but like I said errors.

CREATE DOMAIN RoomType AS VARCHAR(1) CHECK(VALUE IN('S', 'F', 'D'));

#then I was going to create the table with the domains that I would've created but like I
#said above, I couldn't get that far. The following is what I had in mind. Was going to 
#do the same thing for Booking and Guest. I know I didn't finish the problem but hopefully
#me explaining to you how I would've solved it is worth something

CREATE TABLE Room (type RoomType NOT NULL DEFAULT 'S'........) 
