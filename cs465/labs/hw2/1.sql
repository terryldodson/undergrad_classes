# I created two views, one titled AllRooms which contains ALL rooms (unoccupied ones too) 
# and the guestNames contained all the guests that was currently staying at one of the 
# hotels. My plan was to LEFT JOIN these togther that way it would've made the rooms 
# that was unoccupied NULL. I ran into trouble with LEFT JOIN. I couldn't get it to work
# but that was my plan. Hopefully my explanation will receive some partial credit

CREATE VIEW AllRooms (roomNo, hotelNo, type, price) AS SELECT r.roomNo, r.hotelNo, r.type, r.price FROM Room r;


CREATE VIEW guestNames (guestName) AS SELECT g.guestName FROM Guest g, Booking b, Hotel h, Room r WHERE h.hotelNo = r.hotelNo AND r.roomNo = b.roomNo AND b.guestNo = g.guestNo AND CURDATE() BETWEEN b.dateFrom and b.dateTo;
