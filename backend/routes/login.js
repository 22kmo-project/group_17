const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.username && request.body.pin_code){
      const login_username = request.body.username;
      const login_pincode = request.body.pin_code;
        login.checkPin_code(login_username, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(login_pincode,dbResult[0].pin_code, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ username: login_username });
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
);

router.get('/:id?',function(request, response){
  const id=request.params.id;
  login.saveIdUser(id,function(err,dbResult){
      if(err){
          response.json(err);
      }
      else{
          response.json(dbResult[0]);
      }
  })
});

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1200s' }); //Token kestää 20 min
}

// Jos tulee ongelma kirjautumisen kanssa, alla olevalla tekee loginin ilman encryptattua pin-koodia. Pitää korvata vaan yllä olevaan, vastaavaan kohtaan.
/*if (dbResult.length > 0) {
  if (login_pincode == 1234) {
    console.log("success");
    const token = generateAccessToken({ username: login_username });
      response.send(token);
  }
  else {
    console.log("ongelma")
  }
 */ 

module.exports=router;