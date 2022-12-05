const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;

const card = {
  getById: function(id, callback) {
    return db.query('select * from card where id_card=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(add_card, callback) {
    bcrypt.hash(add_card.pin_code, saltRounds, function(err, hashed_pin_code){
    return db.query(
      'insert into card (id_user,card_number,pin_code,card_access) values(?,?,?,?)',
      [add_card.id_user, add_card.card_number, hashed_pin_code, add_card.card_access],
      callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from card where id_card=?', [id], callback);
  },
  update: function(id, update_card, callback) {
    bcrypt.hash(update_card.pin_code, saltRounds, function(err, hashed_pin_code){
    return db.query(
      'update card set id_user=?, card_number=?,pin_code=?, card_access=? where id_card=?',
      [update_card.id_user, update_card.card_number, hashed_pin_code, update_card.card_access, id],
      callback);
    });
  }
};
module.exports = card;