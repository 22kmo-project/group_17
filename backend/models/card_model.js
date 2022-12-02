const db = require('../database');

const card = {
  getById: function(id, callback) {
    return db.query('select * from card where id_card=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(add_card, callback) {
    return db.query(
      'insert into card (card_number,pin_code,card_access) values(?,?,?)',
      [add_card.card_number, add_card.pin_code, add_card.card_access],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from card where id_card=?', [id], callback);
  },
  update: function(id, update_card, callback) {
    return db.query(
      'update card set card_number=?,pin_code=?, card_access=? where id_card=?',
      [update_card.card_number, update_card.pin_code, update_card.card_access, id],
      callback
    );
  }
};
module.exports = card;