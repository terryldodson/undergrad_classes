select SUM(price) FROM Hotel h, Room r, Booking b WHERE h.hotelName = 'Grosvenor Hotel' AND h.hotelNo = r.hotelNo AND r.roomNo = b.roomNo AND CURDATE() BETWEEN b.dateFrom and b.dateTo;
