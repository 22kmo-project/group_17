const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('select * from account where id_account=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into account (id_account,account_number,balance,bank_name,account_type) values(?,?,?,?,?)',
      [add_data.id_account, add_data.account_number, add_data.balance, add_data.bank_name, add_data.account_type],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where id_account=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update account set account_number=?, balance=?, bank_name=?,account_type=? where id_account=?',
      [update_data.account_number, update_data.balance, update_data.bank_name, update_data.account_type, id],
      callback
    );
  }
};
module.exports = account;