/* eslint-disable no-continue */
/* eslint-disable consistent-return */
import express from 'express';

import fs from 'fs';
import { exec, spawn } from 'child_process';

const router = express();

// Create board route
router.post('/create', (req, res) => {
  exec(`../sudoku create ${req.body.difficulty || 3}`, (error, stdout, stderr) => {
    if (error) {
      console.error(`exec error: ${error}`);
      return res.status(500).json(error);
    }
    console.log('stdout:\n', stdout);
    console.log('stderr:\n', stderr);

    const board = parseBoard(stdout);

    return res.json({ message: 'Board created!', difficulty: req.body.difficulty || 3, board });
  });
});

// Solve board route
router.post('/solve', (req, res) => {
  let stdoutString = '';
  let stderrString = '';
  let exitCode = -1;

  const { board } = req.body;

  if (!board) return res.status(400).json({ message: 'Request does not include board in body' });
  // console.log(board);

  const boardFileName = `./tmp/${Date.now()}`;
  const boardString = boardToString(board);
  // console.log("file name", boardFileName, boardString);
  fs.writeFile(boardFileName, boardString, 'utf8', (error) => {
    if (error) {
      return res.status(500).json(error);
    }

    // console.log("File written");

    new Promise((resolve, reject) => {
      const terminal = spawn('bash');

      terminal.stdout.setEncoding('utf8');
      terminal.stderr.setEncoding('utf8');

      // Data handler for stdout
      terminal.stdout.on('data', (data) => {
        stdoutString += data.toString();
        // console.log("stdout", data.toString());
      });

      // Data handler for stdin
      terminal.stderr.on('data', (data) => {
        stderrString += data.toString();
        // console.log("stderr", data.toString());
      });

      // Process exit handler
      terminal.on('exit', (code) => {
        exitCode = code;
        resolve();
      });

      terminal.stdin.write(`cat ${boardFileName} | ../sudoku solve`);
      terminal.stdin.end();
    }).then(() => {
      fs.unlink(boardFileName, (err) => {
        if (err) {
          return res.status(500).json(err);
        }

        return res.json({
          message: 'Board solved!', stdout: stdoutString, stderr: stderrString, exitCode, board: parseBoard(stdoutString),
        });
      });
    }).catch((e) => {
      return res.status(500).json(e);
    });
  });
});

/**
 * Convert a string representation of a board to a double array (array of columns)
 * @param {*} boardString
 */
function parseBoard(boardString) {
  const board = {
    board: [[]],
    dimension: 0,
  };

  // Parse board string to array of arrays
  let row = 0;
  for (let i = 0; i < boardString.length; i += 1) {
    if (boardString[i] === ' ') continue;
    else if (boardString[i] === '\n') { board.board.push([]); row += 1; continue; } else board.board[row].push(parseInt(boardString[i], 10));
  }

  // Filter out any empty arrays
  board.board = board.board.filter((r) => { return r.length > 0; });
  board.dimension = board.board.length;
  return board;
}

/**
 * Takes a board object and convert it into a string
 * @param {*} board
 */
function boardToString(board) {
  let boardString = '';

  // Iterate through entire board and convert to string
  for (let i = 0; i < board.dimension; i += 1) {
    for (let j = 0; j < board.dimension; j += 1) {
      boardString += board.board[i][j].toString();
      boardString += ' ';
    }
    boardString += '\n';
  }

  return boardString;
}

export default router;
