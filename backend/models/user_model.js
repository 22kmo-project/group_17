const db = require('../database');

const user = {
  getById: function(id, callback) {
    return db.query('select * from user where id_user=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from user', callback);
  },
  add: function(add_user, callback) {
    return db.query(
      'insert into user (username,user_fname,user_lname) values(?,?,?)',
      [add_user.username, add_user.user_fname, add_user.user_lname],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from user where id_user=?', [id], callback);
  },
  update: function(id, update_user, callback) {
    return db.query(
      'update user set username=?,user_fname=?, user_lname=? where id_user=?',
      [update_user.username, update_user.user_fname, update_user.user_lname, id],
      callback
    );
  }
};
module.exports = user;