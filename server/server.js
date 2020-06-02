import express from 'express';
import bodyParser from 'body-parser';
import morgan from 'morgan';
import cors from 'cors';

import * as constants from './constants';
import boardRouter from './routers/boardRouter';

const app = express();

// enable json message body for posting data to API
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Enable CORS
app.use(cors());

// enable/disable http request logging
app.use(morgan('dev'));

app.use('/board', boardRouter);

app.get('/', (req, res) => {
  return res.json({ message: 'Welcome to the Team Rocket sudoku backend!' });
});

app.listen(constants.PORT || 9000);

console.log(`listening on: ${constants.PORT}`);
