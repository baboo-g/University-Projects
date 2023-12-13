const express = require('express');
router = express.Router()

const service = require('../Services/user-services')
const admin = require('../Services/admin-services')

//Get credentials
router.post('/submit', async(req, res) =>{
    const cred = await service.check_credentials(req.body)
    if(cred == undefined){
        res.status(404).json("reject")
    }
    else if(req.body.password == cred.password){
        res.status(201).json("accept")
    }
    else{
        res.status(250).json("pass")
    }
})

router.post('/admin', async(req, res) =>{
    const cred = await admin.check_credentials(req.body)
    if(cred == undefined){
        res.status(404).json("reject")
    }
    else if(req.body.password == cred.password){
        res.status(201).json("accept")
    }
    else{
        res.status(250).json("pass")
    }
})

router.post('/add-f', async(req, res) =>{
    const cred = await admin.insert_flight(req.body)
    if(cred > 0){
        res.status(404).json("accept")
    }
    else{
        res.status(201).json("reject")
    }
})










router.post('/book', async(req, res) =>{
    const requirements = await service.book_flight(req.body)
    if(requirements == undefined){
        res.status(404).send("There are No flights in operation with these Requirements")
        // res.send(requirements)
    }
    else if(req.body.departure_city == requirements.departure_city && req.body.arrival_city == requirements.arrival_city){
        res.send(requirements)
    }
})

router.post('/confirm', async(req, res) =>{
    const affectedRows = await service.confirm_booking(req.body)
    if(affectedRows > 0){
        // next();
        //const check = await admin.reduce_seats(req.body.flight_id)
        //console.log(check)
        //if(check > 0){
        res.status(201).send("BOOKED")
        
    }
    else{
        res.status(404).send("Error! Cannot confirm")
    }
    
})

//check this
router.put('/reduce', async(req, res) =>{
        const affectedRows = await admin.reduce_seats(req.body)
        if(affectedRows > 0){
            res.send("ASD")
        }
        else{
            res.send("ASD");
        }
    })

router.post('/Admin', async(req, res) =>{
    const cred = await admin.check_credentials(req.body)
    if(cred == undefined){
        res.status(404).send("Wrong Credentials")
    }
    else if(req.body.password == cred.password){
        res.send("Logged In")
    }
    else{
        res.status(404).send("Incorrect Password. Please Try again.")
    }  
})

router.post('/Admin', async(req, res) =>{
    const cred = await admin.check_credentials(req.body)
    if(cred == undefined){
        res.status(404).send("Wrong Credentials")
    }
    else if(req.body.password == cred.password){
        res.send("Logged In")
    }
    else{
        res.status(404).send("Incorrect Password. Please Try again.")
    }  
})

router.post('/add-flight', async(req, res) =>{
    const row = await admin.insert_flight(req.body)

    if(row > 0){
        res.status(201).send("Added Successfully.")
    }
})

router.put('/update-flight/:id', async(req, res) =>{
    const c = await admin.insert_flight(req.body, req.params.id)
    if(c > 0){
        res.status(201).send("Updated Successfully.")
    }   
    else{
        res.status(404).send("Record does not exist in the database.")
    } 
})

router.post('/add-airport', async(req, res) =>{
    const row = await admin.insert_airport(req.body)

    if(row > 0){
        res.status(201).json("accept")
    }
})

router.put('/update-airport/:id', async(req, res) =>{
    const c = await admin.insert_airport(req.body, req.params.id)
    if(c > 0){
        res.status(201).send("Updated Successfully.")
    }   
    else{
        res.status(404).send("Record does not exist in the database.")
    } 
})

router.post('/add-airline', async(req, res) =>{
    const affectedRows = await admin.insert_airline(req.body)
    if(affectedRows > 0){
        res.status(201).json("Seccessfull")
    }
    else{
        res.status(404).json("Error! Cannot confirm")
    }
    
})

router.get('/get-booking/:id', async (req, res) => {
    const employee = await service.get_booking_details(req.params.id)
    if(employee == undefined){
        res.status(404).json('No Record Found')
    }
    else{
        res.send(employee)
    }
})

router.delete('/delete-airport/:id', async (req, res) => {
    const count = await admin.delete_airport(req.params.id)
    if(count == 0){
        res.status(404).json("No Record of any Aiport exists with id " +[req.params.id])
    }
    else{
        res.send("Airport deleted Successfully!")
    }
})

router.delete('/delete_airline/:id', async (req, res) => {
    const count = await admin.delete_airline(req.params.id)
    if(count == 0){
        res.status(404).json("No Airline exists with this id " +[req.params.id])
    }
    else{
        res.send("Airline deleted Successfully!")
    }
})

router.delete('/delete_flight', async (req, res) => {
    const count = await admin.delete_airline(req.body)
    if(count == 0){
        res.status(404).json("No Flight exists with this id ")
    }
    else{
        res.json("deleted")
    }
})

// router.get('/example', service.firstMiddleware, service.secondMiddleware, async(req, res) => {
//     console.log('Route handler');
//     res.send('Hello World!');
// });


router.post('/book-tickets', async(req, res) =>{
    const affectedRows = await service.book_tickets(req.body)
    if(affectedRows > 0){
        res.status(201).send("Seccessfull")
    }
    else{
        res.status(404).send("Error! Cannot confirm")
    }
    
})

router.post('/signup', async(req, res) =>{
    const row = await service.create_user(req.body)

    if(row > 0){
        res.status(201).json("accept")
    }
    else{
        res.json("reject")
    }
})

module.exports = router;


