const db = require('../database');

const card_right = {
  getById: function(id, callback) {
    return db.query('select * from card_right where id_card_right=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card_right', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into card_right (id_card,id_account) values(?,?)',
      [add_data.id_card,add_data.id_account],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from card_right where id_card_right=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update card_right set id_card=?,id_account=? where id_card_right=?',
      [update_data.id_card, update_data.id_account, id],
      callback
    );
  }
};
module.exports = card_right;