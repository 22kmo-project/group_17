const express = require('express');
const router = express.Router();
const card_right = require('../models/card_right_model');

router.get('/',

    function (request, response) {

        card_right.getAll(function (err, dbResult) {

            if (err) {

                response.json(err);

            } else {

                console.log(dbResult);

                response.json(dbResult);

            }

        })

    });



router.get('/:id?',

    function (request, response) {

        card_right.getById(request.params.id, function (err, dbResult) {

            if (err) {

                response.json(err);

            } else {

                response.json(dbResult[0]);

            }

        })

    });


router.post('/', 
function(request, response) {
  console.log(request.body);
  card_right.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  card_right.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  card_right.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;