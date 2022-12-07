const db = require('../database');

const login={
  checkPin_code: function(username, callback) {
      return db.query(
        'SELECT username, pin_code from user inner join card on user.id_user=card.id_user WHERE username = ?'
        ,[username], callback); 
    }
};
          
module.exports = login;