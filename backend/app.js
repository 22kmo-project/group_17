var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var userRouter = require('./routes/user');

var app = express();

@@ -18,7 +17,6 @@ app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use('/user', userRouter);

module.exports = app;
