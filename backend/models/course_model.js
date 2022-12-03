const db = require('../database');


const course = {
    getById: function (id, callback) {
        return db.query('select * from course where id_course=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from course', callback);
    },
    add: function (add_data, callback) {
        return db.query(
            'insert into course (name,ects) values(?,?)',
            [add_data.name, add_data.ects],
            callback);
    },
    delete: function (id, callback) {
        return db.query('delete from course where id_course=?', [id], callback);
    },
    update: function (id, update_data, callback) {
            return db.query(
                'update course set name=?,ects=? where id_course=?',
                [update_data.name, update_data.ects, id],
                callback);
    }
};
module.exports = course;