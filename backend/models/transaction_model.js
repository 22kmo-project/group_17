const db = require('../database');

const transaction = {
  getById: function(id, callback) {
    return db.query('select * from transaction where id_account=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from transaction', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into transaction (transaction_date,transaction_type,sum) values(?,?,?)',
      [add_data.transaction_date, add_data.transaction_type, add_data.sum],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transaction where id_transaction=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update transaction set transaction_date=?, transaction_type=?, sum=? where id_transaction=?',
      [update_data.transaction_date, update_data.transaction_type, update_data.sum, id],
      callback
    );
  }
};
module.exports = transaction;
