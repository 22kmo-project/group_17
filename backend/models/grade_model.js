const db = require('../database');


const grade = {
    getById: function (id, callback) {
        return db.query('select id_grade, date_format(grade_date,"%d.%m.%Y") as "grade_date",id_student, id_course, grade from grade  where id_grade=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select id_grade, date_format(grade_date,"%d.%m.%Y") as "grade_date",id_student, id_course, grade from grade', callback);
    },
    add: function (add_data, callback) {
        return db.query(
            'insert into grade (grade_date,id_student,id_course,grade) values(?,?,?,?)',
            [add_data.grade_date, add_data.id_student, add_data.id_course, add_data.grade],
            callback);
    },
    delete: function (id, callback) {
        return db.query('delete from grade where id_grade=?', [id], callback);
    },
    update: function (id, update_data, callback) {
            return db.query(
                'update grade set grade_date=?,id_student=?, id_course=?, grade=? where id_grade=?',
                [update_data.grade_date, update_data.id_student, update_data.id_course, update_data.grade, id],
                callback);
    }
};
module.exports = grade;