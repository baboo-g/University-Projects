const conn = require('../connect')

module.exports.getAllEmployees = async() => {
    const [rows] = await conn.query("Select * from employee.check")
        .catch(err => console.log(err))
    return rows;
}

module.exports.getEmployeebyId = async(id) => {
    const [[ids]] = await conn.query("Select * from employee.check where employee_id =" + id)
        .catch(err => console.log(err)) 
    return ids;
}

//Delete Function
module.exports.deletebyid = async(id)=>{
    [{affectedRows}] = await conn.query("Delete from employee.check where employee_id=?",[id])
    return affectedRows; 
}

//insertorupdate
module.exports.insert = async (obj, op=-1)=>{
    const [[[{affectedrows}]]] = await conn.query("call InsertOrUpdate(?, ?, ?)", [op, obj.flight_id, obj.departure_time, obj.arrival_time, obj.seats_avaliable, obj.price, obj.Operates, obj.Operates, obj.arrival_city, obj.departure_city, obj.departure_date])
    return affectedrows
}

