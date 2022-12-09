const db = require('../database');

const account_right = {
  getById: function(id, callback) {
    return db.query('select * from account_right where id_account_right=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account_right', callback);
  },
  add: function(add_data, callback) {
    return db.query(
    'insert into account_right (id_account, id_user, account_holder, account_right) values(?,?,?,?)',
      [add_data.id_account,add_data.id_user, add_data.account_holder, add_data.account_right],
      callback
      );
  },
  delete: function(id, callback) {
    return db.query('delete from account_right where id_account_right=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update account_right set id_account=?,id_user=?,account_holder=?,account_right=? where id_account_right=?',
      [update_data.id_account, update_data.id_user, update_data.account_holder, update_data.account_right, id],
      callback
    );
  }
};
module.exports = account_right;