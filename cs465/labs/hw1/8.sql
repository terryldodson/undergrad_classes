select h.hotelName, COUNT(roomno) as count FROM Hotel h, Room r WHERE h.hotelNo = r.hotelNo AND h.city = 'London' GROUP BY h.hotelName ORDER BY h.hotelName, count;
