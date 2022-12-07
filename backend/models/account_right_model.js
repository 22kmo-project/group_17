const db = require('../database');

const account_right = {
  getById: function(id, callback) {
    return db.query('select * from account_right where account_right=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account_right', callback);
  },
  add: function(add_data, callback) {
    return db.query(
    'insert into account_right (id_account,id_card) values(?,?)',
      [add_data.id_account,add_data.id_card],
      callback
      );
  },
  delete: function(id, callback) {
    return db.query('delete from account_right where id_account_right=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update account_right set id_account=?,id_card=? where id_account_right=?',
      [update_data.id_account, update_data.id_card, id],
      callback
    );
  }
};
module.exports = account_right;