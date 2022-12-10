var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

var transactionRouter = require('./routes/transaction');
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var userRouter = require('./routes/user');
var account_rightRouter = require('./routes/account_right');
var card_rightRouter = require('./routes/card_right');
var loginRouter = require('./routes/login');
var account_informationRouter = require('./routes/account_information');

var app = express();
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter);
app.use(authenticateToken);
app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/transaction', transactionRouter);
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use('/user', userRouter);
app.use('/account_right', account_rightRouter);
app.use('/card_right', card_rightRouter);
app.use('/account_information', account_informationRouter);

module.exports = app;
