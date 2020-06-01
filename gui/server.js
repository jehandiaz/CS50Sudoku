// Reference: https://www.digitalocean.com/community/tutorials/react-server-side-rendering

import express from "express";
import compression from "compression";
import createRoute from "./routes/createRoute";
import solveRoute from "./routes/solveRoute";
const app = express();

app.use(compression());
app.use(express.static("public"));

app.use("/create", createRoute);
app.use("/solve", solveRoute);

const port = process.env.PORT || 3030;
app.listen(port, function listenHandler() {
  console.info(`Running on ${port}...`);
});

// const express = require('express');
// const path = require('path');
// const fs = require('fs');
// const exec = require('child_process').exec;

// const ReactDOMServer = require('react-dom/server');
// const App = require('./src/App');

// const listAll = 'ls -a -l';

// exec(listAll, (error, stdout, stderr) => {
//   if (error) {
//     console.error(`exec error: ${error}`);
//     return;
//   }
//   console.log('stdout: ' + stdout);
//   console.log('stderr: ' + stderr);
// });

// const runSudoku = '../sudoku create';

// exec(runSudoku, (error, stdout, stderr) => {
//   if (error) {
//     console.error(`exec error: ${error}`);
//     return;
//   }
//   console.log('stdout: ' + stdout);
//   console.log('stderr: ' + stderr);
// });

// const app = express();

// Serve the static files from the React app
// app.use(express.static(path.join(__dirname, 'build')));

// Basic working server
// app.get('/*', (req, res) => {
//   const app = ReactDOMServer.renderToString(<App />);

//   const indexFile = path.resolve('./build/index.html');
//   fs.readFile(indexFile, 'utf8', (err, data) => {
//     if (err) {
//       console.error('Something went wrong:', err);
//       return res.status(500).send('Oops, better luck next time!');
//     }

//     return res.send(
//       data.replace('<div id="root"></div>', `<div id="root">${app}</div>`)
//     );
//   });
// });

// app.get('/*', (req, res) => {
//   const currentRoute =
//     Routes.find(route => matchPath(req.url, route)) || {};
//   let promise;

//   if (currentRoute.loadData) {
//     promise = currentRoute.loadData();
//   } else {
//     promise = Promise.resolve(null);
//   }

//   promise.then(data => {
//     // Let's add the data to the context
//     const context = { data };

//     const app = ReactDOMServer.renderToString(
//       <StaticRouter location={req.url} context={context}>
//         <App />
//       </StaticRouter>
//     );

//     const indexFile = path.resolve('./build/index.html');
//     fs.readFile(indexFile, 'utf8', (err, indexData) => {
//       if (err) {
//         console.error('Something went wrong:', err);
//         return res.status(500).send('Oops, better luck next time!');
//       }

//       if (context.status === 404) {
//         res.status(404);
//       }
//       if (context.url) {
//         return res.redirect(301, context.url);
//       }

//       return res.send(
//         indexData
//           .replace('<div id="root"></div>', `<div id="root">${app}</div>`)
//           .replace(
//             '</body>',
//             `<script>window.__ROUTE_DATA__ = ${serialize(data)}</script></body>`
//           )
//       );
//     });
//   });
// });

// // app.get('/', (req, res) => {
// //   return res.sendFile(path.join(__dirname+'build/index.html'));
// // });

// // app.get("/create", (req, res) => {
// //   return res.send("Create sudoku board");
// // });

// // app.get("/solve", (req, res) => {
// //   return res.send("Solve sudoku board");
// // });

// // app.get('*', (req, res) => {
// //   return res.send("Page not found");
// // });

// const port = process.env.PORT || 5000;
// app.listen(port);

// console.log('App is listening on port ' + port);
