var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

var transactionRouter = require('./routes/transaction');
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var userRouter = require('./routes/user');
var account_rightRouter = require('./routes/account_right');
var card_rightRouter = require('./routes/card_right');

var app = express();
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));


app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/transaction', transactionRouter);
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use('/user', userRouter);
app.use('/account_right', account_rightRouter);
app.use('/card_right', card_rightRouter);


module.exports = app;
