import express from 'express';
import bodyParser from 'body-parser';
import morgan from 'morgan';
import { exec } from 'child_process';

import * as constants from './constants';

const app = express();

// enable json message body for posting data to API
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// enable/disable http request logging
app.use(morgan('dev'));

app.get('/', (req, res) => {
  var cmdToLaunch = "../sudoku create";
  exec(cmdToLaunch, (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      return;
    }
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
  });
  res.send("Welcome to the Team Rocket sudoku backend!");
});

app.get('/create', (req, res) => {
  res.send("Create!");
});

app.get('/solve', (req, res) => {
  res.send("Solve!");
});

app.listen(constants.PORT || 9090);

console.log(`listening on: ${constants.PORT}`);
