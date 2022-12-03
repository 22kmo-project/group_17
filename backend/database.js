const mysql = require('mysql');
const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'group_17',
  password: 'netpass',
  database: 'group_17'

});

module.exports = connection;