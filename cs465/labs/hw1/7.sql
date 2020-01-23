select h.hotelNo, COUNT(roomno) as count FROM Hotel h, Room r WHERE h.hotelNo = r.hotelNo GROUP BY h.hotelName ORDER BY h.hotelNo, count;
