const conn = require('../connect')

module.exports.reduce_seats = async (obj)=>{
    const [affectedRows] = await conn.query("update airport.flight set seats_avaliable = seats_avaliable-1 where flight_id = ?;",[obj.flight_id])
        .catch(err => console.log(err))
    return affectedRows
}

module.exports.check_credentials = async (obj)=>{
    const [[data]] = await conn.query("Select * from Airport.admin where username=?",[obj.user])
        .catch(err => console.log(err))
    return data
}

module.exports.insert_flight = async (obj, op=-1)=>{
    const [[[{affectedrows}]]] = await conn.query("call InsertOrUpdate(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", [op, obj.flight_id, obj.departure_time, obj.arrival_time, obj.seats_avaliable, obj.price, obj.aid, obj.arr_id, obj.dep_id, obj.departure_date])
    return affectedrows
}

module.exports.insert_airport = async (obj, op=-1)=>{
    const [[[{affectedrows}]]] = await conn.query("call InsertAirport(?, ?, ?, ?, ?)", [op, obj.Airport_id, obj.Airport_name, obj.city, obj.country])
    return affectedrows
}

module.exports.insert_airline = async (obj)=>{
    const [{affectedRows}] = await conn.query("insert into airport.airline values(?,?)",[obj.airline_id, obj.airline_name])
        .catch(err => console.log(err))
    return affectedRows
}

module.exports.delete_flight = async(obj)=>{
    [{affectedRows}] = await conn.query("Delete from airport.flight where flight_id=?",[obj.flight_id])
    return affectedRows; 
}

module.exports.delete_airport = async(obj)=>{
    [{affectedRows}] = await conn.query("Delete from airport.airport_details where airport_id=?", [obj.airport_id])
    return affectedRows; 
}

module.exports.delete_airline = async(obj)=>{
    [{affectedRows}] = await conn.query("Delete from airport.airline where airline_id=?",[obj. airline_id])
    return affectedRows; 
}
