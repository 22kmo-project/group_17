const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_17',
  password: 'netpass',
  database: 'group_17'
});
module.exports = connection;
