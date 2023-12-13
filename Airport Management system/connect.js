var mysql = require('mysql2/promise');

var conn = mysql.createPool({
    host     : "localhost",
    user     : "root",
    password : "password",
    database : "Airport"
});

module.exports = conn;
