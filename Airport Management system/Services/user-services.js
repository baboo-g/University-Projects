const conn = require('../connect')

module.exports.check_credentials = async (obj)=>{
    const [[data]] = await conn.query("Select * from Airport.user where email=?",[obj.email])
        .catch(err => console.log(err))
    return data
}

module.exports.book_flight = async (obj)=>{
    const [[data]] = await conn.query("Select * from Airport.flight where arrival_city=? and departure_city=?",[obj.arrival_city, obj.departure_city])
        .catch(err => console.log(err))
    return data
}   

module.exports.confirm_booking = async (obj)=>{
    const [{affectedRows}] = await conn.query("insert into airport.booking values(?,?,?)",[obj.booking_id, obj.flight_id, obj.status])
        .catch(err => console.log(err))
    return affectedRows
}

module.exports.book_tickets = async(obj) => {
    const [{affectedRows}] = await conn.query("insert into airport.tickets values(?,?)",[obj.ticket_id, obj.seat_number])
        // .catch(err => console.log(err))
    return affectedRows;
}

module.exports.book_tickets = async(obj) => {
    const [{affectedRows}] = await conn.query("insert into airport.tickets values(?,?)",[obj.ticket_id, obj.seat_number])
        // .catch(err => console.log(err))
    return affectedRows;
}

module.exports.get_booking_details = async (user_id)=>{
    const [[aff]] = await conn.query("select * from airport.booking where user_id = ?", [user_id])
        .catch(err => console.log(err))
    return aff
}

module.exports.create_user = async (obj, op=-1)=>{
    const [[[{affectedrows}]]] = await conn.query("call CreateUser(?, ?, ?, ?, ?, ?)", [op, obj.user_id, obj.first_name, obj.last_name, obj.email, obj.password])
    return affectedrows
}