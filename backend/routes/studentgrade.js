const express = require('express');
const router = express.Router();
const student = require('../models/student_model');

router.get('/',function(request,response){
    student.getAllGrades(function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});

router.get('/:id',function(request, response){
    const id=request.params.id;
    student.getOneStudentGrades(id,function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});

module.exports=router;